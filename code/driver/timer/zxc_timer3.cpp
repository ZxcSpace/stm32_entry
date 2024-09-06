#include "zxc_timer3.h"

namespace zxc
{
    void ZxcTimer3::gpio_init_pwm3(){

        GPIO_InitTypeDef GPIO_InitStructure;

        // 配置 PB0 为复用功能（TIM3_CH3）
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        // 选择 TIM3 的复用功能
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
    }
    void ZxcTimer3::init_pwm_ch3(){

        // 启用 TIM3 时钟
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
        // 启用 GPIOB 时钟
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

        //初始化b0
        gpio_init_pwm3();

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        TIM_OCInitTypeDef TIM_OCInitStructure;

        // 计数器配置
        TIM_TimeBaseStructure.TIM_Period = 100-1; // 自动重载寄存器值 (ARR)
        TIM_TimeBaseStructure.TIM_Prescaler = 100-1; // 预分频器值 (PSC)，1000000
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

        // 输出比较配置
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // PWM 模式 1
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse = 0; // 初始占空比 (CCR3)
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OC3Init(TIM3, &TIM_OCInitStructure);

        // 启用 TIM3
        TIM_Cmd(TIM3, ENABLE);

        // 启用通道3输出比较使能
        TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    }

    void ZxcTimer3::set_pwm_ch3(int16_t v){
        // 确保占空比在 0% 到 100% 之间
        if (v > 100) v = 100;
        // 计算 CCR3 值
        uint16_t ccrValue = (v * (TIM3->ARR + 1)) / 100;
        TIM_SetCompare3(TIM3,ccrValue);
    }
} // namespace zxc
