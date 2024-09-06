#include "zxc_max30102.h"
#include "zxc_sys_tick_clock.h"
// #include "DspFilters/Dsp.h"
#include "arm_math.h"
namespace zxc
{
    ZxcI2c ZxcMax30102::i2c = {I2C2,GPIOB,10,9};
    QueueHandle_t ZxcMax30102::semapor = xSemaphoreCreateBinary();
    ZxcCircleBuffer ZxcMax30102::ir_buffer = ZxcCircleBuffer();
    ZxcCircleBuffer ZxcMax30102::red_buffer = ZxcCircleBuffer();
    void ZxcMax30102::init(){
        u8 tmp;

        i2c.init();
        write(0x09,0x40);//复位
        read(0x00,&tmp,1);
        // for_delay_ms(10);
        write(0x02,0x80);//启用 FIFO Almost Full 
        write(0x03,0x00);//禁用所有其他中断
        write(0x04,0x00);//将FIFO写指针设置为0
        write(0x05,0x00);//将FIFO溢出的次数计数器设置为0
        write(0x06,0x00);//将 FIFO 读指针设置为0
        write(0x08,0x0f);//SMP_AVE：0不平均抽取数据，FIFO_A_FULL:f17个数据时发出中断，此时，还有15个空位
        write(0x09,0x03);//SpO2模式，激活红色和红外 LED
        write(0x0A,0x27);//设置脉冲宽度411(18分辨率，分辨率和积分时间相关)，每秒采样率100hz，adc量程4096nA
        write(0x0C,0x24);//led电流7.2mA
        write(0x0D,0x24);//led电流7.2mA
        write(0x10,0x7f);
        config_interupt();
    }

    void ZxcMax30102::config_interupt(){

        GPIO_InitTypeDef gpio_b8;

        // 使能 GPIOB 时钟
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        // 配置 GPIOB 引脚 B8 为输入模式
        gpio_b8.GPIO_Pin = GPIO_Pin_8;
        gpio_b8.GPIO_Mode = GPIO_Mode_IN; // 输入模式
        gpio_b8.GPIO_PuPd = GPIO_PuPd_UP; // 无上拉下拉
        GPIO_Init(GPIOB, &gpio_b8);

        EXTI_InitTypeDef exit_b8;
        NVIC_InitTypeDef nvic_b8;

        // 使能 SYSCFG 时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

        // 连接 外部中断8 到 GPIOB
        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);

        // 配置 EXTI Line8
        exit_b8.EXTI_Line = EXTI_Line8;
        exit_b8.EXTI_Mode = EXTI_Mode_Interrupt; // 中断模式
        exit_b8.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
        exit_b8.EXTI_LineCmd = ENABLE;
        EXTI_Init(&exit_b8);

        // 配置 NVIC 中断
        nvic_b8.NVIC_IRQChannel = EXTI9_5_IRQn; // EXTI Line 8 中断
        nvic_b8.NVIC_IRQChannelPreemptionPriority = MAX30102_INTERRUPT_PRIORITY;
        nvic_b8.NVIC_IRQChannelSubPriority = 0;
        nvic_b8.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&nvic_b8);
    }

    bool ZxcMax30102::read(u32& red_led_data,u32& ir_led_data){

        u8 tmp[6];

        bool rs = true;
        //读取寄存器清除状态
        // read(0x00,tmp,1);
        // rs |= read(0x01,tmp,1);

        //从fifo中读取一条数据6个字节
        rs |= read(0x07,tmp,6);
        red_led_data = (((u32)tmp[0])<<16) + (((u32)tmp[1])<<8) + (u32)tmp[2];
        ir_led_data = (((u32)tmp[3])<<16) + (((u32)tmp[4])<<8) + (u32)tmp[5];

        red_led_data &= 0x03FFFF;
        ir_led_data &= 0x03FFFF;
        return rs;

    }

    #define NUM_STAGES 1
    #define BLOCK_SIZE 32

    float32_t coeffs[5 * NUM_STAGES] = {
        // 例如：滤波器系数
        // 0.019238573667911894, 0.038477147335823789, 0.019238573667911894, 1.5711024401904012, -0.64805673486204896
        1, -2, 1 ,1.9111970663070679, -0.9149758219718933
    };

    float32_t state[4 * NUM_STAGES];
    arm_biquad_casd_df1_inst_f32 S;
    float32_t tmp_buffer[500];
    float32_t out_buffer[500];
    void get_sp02_and_rate_z(ZxcCircleBuffer input, float32_t *output){
        for (int i = 0; i < 500; i++)
        {
            tmp_buffer[i] = (float32_t)input[i];
        }
         
        arm_biquad_casd_df1_inst_f32 S;

        arm_biquad_cascade_df1_init_f32(&S, NUM_STAGES, coeffs, state);
        

        arm_biquad_cascade_df1_f32(&S, tmp_buffer, output,500);
        
    }
    void ZxcMax30102::get_sp02_and_rate(int* sp02, int* rate,int8_t* spo2_valid,int8_t* rate_valid){

        uint32_t red_d;
        uint32_t ir_d;
        // int8_t spo2_valid;
        // int8_t rate_valid;
        int count = 0;
        u8 dump;

        
        for (u16 i = 0; i < 6; i++)
        {

            if ((GPIOB->IDR & GPIO_IDR_IDR_8)!=0)
            {

                if(!xSemaphoreTake(semapor,500)){
                    return;
                }
            }
            
            //读取17条数据
            for (u8 i = 0; i < 17; i++)
            {
                ZxcMax30102::read(red_d,ir_d);
                count++;
                append(red_d,ir_d);
                // DEBUG_INFO("%d_%d",red_d,ir_d);
            }          
            // DEBUG_INFO("_count:%d",count);
            read(0x00,&dump,1);//清除溢出状态
            //不能等待，有可能在清除后，又满了，又会产生中断，会导致卡住
            // while ((GPIOB->IDR & GPIO_IDR_IDR_8)==0);//等待高电平

        }

        // get_sp02_and_rate_z(red_buffer,out_buffer);
        // for (int i = 0; i < 500; i++)
        // {
        //     DEBUG_INFO("%f",out_buffer[i]);
        // }
        
        maxim_heart_rate_and_oxygen_saturation(ir_buffer,MAX30102_BUFFER_LEN,red_buffer,sp02,spo2_valid,rate,rate_valid);
    

    }
} // namespace zxc
