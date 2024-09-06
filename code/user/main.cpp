#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "usart.h"
#include <stdio.h>
#include "zxc_debug.h"
// #include "zxc_spi.h"
// #include "zxc_st7789.h"
// #include "st7789h2.h"
#include "zxc_timer3.h"
#include "FreeRTOS.h"
#include "task.h"
// #include "semphr.h"
// #include "lvgl.h"
// #include "lv_port_disp.h"
// #include "zxc_htu21d.h"
#include "zxc_rtos.h"
// #include "zxc_max30102.h"
// #include "zxc_adc.h"
#include "zxc_dma_adc.h"
#include "zxc_tflm.h"

using namespace zxc;


int main(void){

    //系统时钟配置，晶振非25mhz，所以必须的
    zxc_sys_clock_config();
    //使用中断需要配置
    // NVIC_SetPriorityGrouping(3);//配置优先级组0-15

    zxc_uart_init();

    DEBUG_INFO("start");

    ZxcTimer3::init_pwm_ch3();
    ZxcTimer3::set_pwm_ch3(60);

    ZxcModel::init();

    u8 d = ZxcModel::inturrupt();
    DEBUG_INFO("index:%d",d);

    ZxcRTOS::init();
    vTaskStartScheduler();

    while (1)
    {
        // DEBUG_INFO("start");
    }
    

}