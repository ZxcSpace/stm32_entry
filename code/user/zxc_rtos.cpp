#include "zxc_rtos.h"

namespace zxc
{
    // 卡尔曼滤波器的参数
    ZxcKalmanFilter kf_temp(0.00001, 0.0002, 1, 0);
    ZxcKalmanFilter kf_hum(0.00002, 0.06, 1, 0);
    TaskHandle_t ZxcRTOS::htu21d_handle;
    TaskHandle_t ZxcRTOS::max30102_handle;
    TaskHandle_t ZxcRTOS::lv_timer_handle;
    TaskHandle_t ZxcRTOS::draw_handle;
    TaskHandle_t ZxcRTOS::sound_handle;
    TaskHandle_t ZxcRTOS::touch_handle;
    QueueHandle_t ZxcRTOS::lvgl_lock_semapor;
    QueueHandle_t ZxcRTOS::max_lock_semapor;

     double ZxcRTOS::temp;
     int ZxcRTOS::hum;
     int ZxcRTOS::rate;
     int ZxcRTOS::spo2;
     
    void ZxcRTOS::htu21d_task(){
        while (1)
        {
            xSemaphoreTake(max_lock_semapor,portMAX_DELAY);
            temp = kf_temp.filter(ZxcHtu21d::get_temp());
            xSemaphoreGive(max_lock_semapor);
            DELAY_MS(490);
            xSemaphoreTake(max_lock_semapor,portMAX_DELAY);
            hum = (int)round(kf_hum.filter(ZxcHtu21d::get_hum()));
            xSemaphoreGive(max_lock_semapor);
            DELAY_MS(490);
        }
        
        
    }


    void ZxcRTOS::max30102_task(){
        int d1;
        int d2;
        int8_t spo2_valid;
        int8_t rate_valid;
        while (1)
        {
            if (xSemaphoreTake(max_lock_semapor,200))
            {
                ZxcMax30102::get_sp02_and_rate(&d1,&d2,&spo2_valid,&rate_valid); 
                xSemaphoreGive(max_lock_semapor);
                if (rate_valid)
                {          
                    rate = (d2>220) ? 0 : d2;     
                    
                }

                if (spo2_valid && d1 > 90)
                {
                    spo2 = d1;
                }
                else{
                    spo2=0;
                }
            }
            
            DELAY_MS(1000);


            
        }
        
    }



    void ZxcRTOS::lv_timer_task(){

        //线程不安全，需要上锁
        while (1)
        {
            //注意此任务和下面的修改显示任务必须上锁
            //线程不安全的，需要上锁
            xSemaphoreTake(lvgl_lock_semapor,portMAX_DELAY);
            lv_timer_handler();
            xSemaphoreGive(lvgl_lock_semapor);
            vTaskDelay(10);
            
            
        } 
        
    }
    void ZxcRTOS::lv_draw_task(){
        xSemaphoreTake(lvgl_lock_semapor,portMAX_DELAY);
        ZxcMain::create();
        //这种使用对象方式不太方便，应该避免(懒得改了)
        ZxcLvClock cl(140,140);
        cl.create();

        ZxcCal::create();
        ZxcTemp::create();
        ZxcHum::create();
        ZxcMaxChart::create();

        lv_scr_load(ZxcMain::main_bg);
        xSemaphoreGive(lvgl_lock_semapor);

        u8 count = 0;
        TickType_t xLastWakeTime = xTaskGetTickCount();;
        //线程不安全，需要上锁
        while (1)
        {
            vTaskDelayUntil(&xLastWakeTime,200);
            
            
            xSemaphoreTake(lvgl_lock_semapor,portMAX_DELAY);

            switch (count)
            {
            case 0:
                ZxcTemp::set_value(temp);
                count++;
                break;
            case 1:
                ZxcHum::set_value(hum);
                count++;
                break;
            case 2:
            ZxcMaxChart::set_rate(rate);
                count++;
                break;
            case 3:
            ZxcMaxChart::set_spo2(spo2);
                count++;
                break;
            case 4:
                cl.updata_by_s();
                count=0;
                break;
            
            default:
                break;
            }
            
            xSemaphoreGive(lvgl_lock_semapor);
        }
        
        
    }

    void ZxcRTOS::sound_task(){

        int i = 0;
        ZxcAdc::start();

        int sl_count = 0;

        u8 no_count = 0;
        u8 rl_count = 0;
        u8 cd_count = 0;
        bool sl_flag = false;
        bool can_flag = false;
        bool change_flag = false;
        
        u8 prev_rs = 0;
        while (1)
        {   

            ulTaskNotifyTake(pdFALSE,portMAX_DELAY);//等待通知
          ZxcModel::set_input(ZxcDmaAdc::buffer,1000);
            u8 rs = ZxcModel::inturrupt();
            //统计连续个数
            switch (rs)
            {
            case 0:

                sl_count = (prev_rs==0)?(sl_count+1):0;

                break;

            case 1:
                rl_count = (prev_rs==1)?(rl_count+1):0;
                no_count = (prev_rs!=0)?(no_count+1):0;
                break;
            case 2:
                cd_count = (prev_rs==2)?(cd_count+1):0;
                no_count = (prev_rs!=0)?(no_count+1):0;
                break;
            default:
                no_count = (prev_rs!=0)?(no_count+1):0;
                break;
            
            }
            prev_rs = rs;

            if (!can_flag && sl_count>10){//检测静态，连续10次才是静态
                sl_count = 11;
                sl_flag = true;
                
            }


            if (sl_flag && no_count>=2)//检测跳变
            {
                can_flag = true;
                sl_flag = false;//跳变后不再是静态
                sl_count = 0;
            }
            

            if (can_flag)
            {
                
                if (!change_flag)
                {
                    //这里简略了，因为网络对于菜单和日历区分不是很好，老是误判
                    change_flag=!change_flag;
                    xSemaphoreTake(lvgl_lock_semapor,portMAX_DELAY);
                    lv_scr_load(ZxcCal::calendar);
                     xSemaphoreGive(lvgl_lock_semapor);
                }
                else{
                    change_flag=!change_flag;
                    xSemaphoreTake(lvgl_lock_semapor,portMAX_DELAY);
                    lv_scr_load(ZxcMain::main_bg);
                     xSemaphoreGive(lvgl_lock_semapor);
                }
                
                can_flag = false;//失能处理
            }
            DELAY_MS(10);
            
            ZxcDmaAdc::start();
            /// 配置 DMA 传输
            ADC1->CR2 |= ADC_CR2_DMA; // 重新启动DMA

            
    }
        
    }


    void ZxcRTOS::touch_task(){

        while (1)
        {
            u16 d = ZxcAdc::get_touch_x();

        DEBUG_INFO("touch:%d",d);
        ADC1->CR2 |= ADC_CR2_JSWSTART; // 手动触发注入转换
        }
        
        
    }

    void time_callback( TimerHandle_t xTimer){

        vTaskSuspend(ZxcRTOS::sound_handle);


    }

    void ZxcRTOS::init(){

        BaseType_t rs;
        lvgl_lock_semapor = xSemaphoreCreateBinary();//初始化信号量
        max_lock_semapor = xSemaphoreCreateBinary();
        xSemaphoreGive(lvgl_lock_semapor);//先给出一个信号量
        xSemaphoreGive(max_lock_semapor);

        ZxcHtu21d::init();

        ZxcMax30102::init();
        
        ZxcAdc::init();  

        lv_init();
        lv_port_disp_init(); 


        rs = xTaskCreate( (TaskFunction_t)htu21d_task,
                            "htu21d_task",
                            256,
                            NULL,
                            1,
                            &htu21d_handle);
        rs = xTaskCreate( (TaskFunction_t)max30102_task,
                            "max30102_task",
                            1024,
                            NULL,
                            1,
                            &max30102_handle);

        rs = xTaskCreate( (TaskFunction_t)lv_timer_task,
                            "lv_t_task",
                            2*1024,
                            NULL,
                            3,
                            &lv_timer_handle);
        
        rs = xTaskCreate( (TaskFunction_t)lv_draw_task,
                            "draw_task",
                            2*1024,
                            NULL,
                            3,
                            &draw_handle);
       

        rs = xTaskCreate( (TaskFunction_t)sound_task,
                            "sound_task",
                            512,
                            NULL,
                            0,
                            &sound_handle);


        // 创建定时器：定时器到期后调用 vTimerCallback
        TimerHandle_t xTimer = xTimerCreate("Timer", pdMS_TO_TICKS(20000), pdFALSE, (void *)0, time_callback);

        if (xTimer != NULL) {
            // 启动定时器
            xTimerStart(xTimer, 0);
        }

        //电阻屏采样任务，没有触屏，无效任务
        // rs = xTaskCreate( (TaskFunction_t)touch_task,
        //                     "touch_task",
        //                     256,
        //                     NULL,
        //                     3,
        //                     &touch_handle);
    }


} // namespace zxc
