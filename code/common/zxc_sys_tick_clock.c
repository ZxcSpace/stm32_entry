#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "FreeRTOS.h"
#include "task.h"
#include "zxc_debug.h"

//freertos需要的函数
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // 用户定义的栈溢出处理代码
    // 例如，触发一个断言，停止系统，或通过某种方式通知用户
    DEBUG_INFO("error,stack overflow");
    for (;;) {
        // 可能使用 LED 闪烁、串口输出错误信息等
    }
}

void zxc_init_NVIC_Priorities(){
    //设置0-15
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);


}



void for_delay_ms(uint32_t ms)
{
    uint32_t Delay = ms * 10000; /* 晶振频率 */
    do
    {
        __NOP(); /* 空指令（NOP）来占用 CPU 时间 */
    } while (Delay--);
}

void for_delay_us(uint32_t us)
{
    uint32_t Delay = us * 10; /* 晶振频率 */
    do
    {
        __NOP(); /* 空指令（NOP）来占用 CPU 时间 */
    } while (Delay--);
}
