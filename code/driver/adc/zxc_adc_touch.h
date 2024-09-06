#ifndef __ZXC_ADC_TOUCH_H__
#define __ZXC_ADC_TOUCH_H__
#include "stm32f4xx.h"

class ZxcAdcTouch{

    private:
    public:

    static void init(){
        // 使能 GPIOA 时钟
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER2); // 清除原有配置
        //高速模式10
        GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 | GPIO_OSPEEDER_OSPEEDR2);
        GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR0_1 | GPIO_OSPEEDER_OSPEEDR2_1);
    }

    static void gpio_x_set(){

        
    //a0 a2输出模式01
    GPIOA->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER2_0);
    //a0 a2推挽0
    GPIOA->OTYPER &= ~(GPIO_OTYPER_ODR_0 | GPIO_OTYPER_ODR_2);
    
    //高电平
    GPIOA->ODR &= ~GPIO_ODR_ODR_0;
    GPIOA->ODR &= ~GPIO_ODR_ODR_2;

    //a3模拟输入
    // 配置 PA3 为模拟11
    GPIOA->MODER |= (GPIO_MODER_MODER3_0 | GPIO_MODER_MODER3_1); // 设置为模拟模式
    //a1为输入模式，防止电平影响

    // //高速模式10
    // GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR1);
    // GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;


    }

};
#endif