#include "zxc_adc.h"

namespace zxc
{
    ZxcAdc::ZxcAdc()
    {
    }

    ZxcAdc::~ZxcAdc()
    {
    }

    void ZxcAdc::init(){
    ZxcDmaAdc::init();

        // 使能 GPIOB 时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    ADC1->CR2 &= ~ADC_CR2_ADON;

    // 配置 PB1 为模拟模式
    GPIOB->MODER &= ~(GPIO_MODER_MODER1); // 清除 PB1 的模式位
    GPIOB->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER1_1); // 
    
    // 使能 ADC1 时钟
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    //分辨率默认cr1->res，默认12位

    //4分频：01，变为25mhz，因为最大不能超过36mhz

    //改11：8高频
    ADC->CCR |= ADC_CCR_ADCPRE_0;
    ADC->CCR |= ADC_CCR_ADCPRE_1;

    //连续采样
    ADC1->CR2 |= ADC_CR2_CONT;
    //非扫描模式，因为只有一个
    ADC1->CR1 &= ~ADC_CR1_SCAN;
    //数据对其，右对齐
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    //0：最后一次传输后不会发出新的dma请求
    //1：只要转换数据且dma为1就会发送dma请求
    //在dma循环模式下，此项必须开启    
    // ADC1->CR2 |= ADC_CR2_DDS;
    
    // 配置 ADC 采样时间为 480 个周期（针对通道 9） 111
    ADC1->SMPR2 |= ADC_SMPR2_SMP9_0;
    ADC1->SMPR2 |= ADC_SMPR2_SMP9_1;
    ADC1->SMPR2 |= ADC_SMPR2_SMP9_2;

    //配置通道中有1个需要转换000,规则通道中启用了几个转换
    ADC1->SQR1 &= ~ADC_SQR1_L;

    // 配置通道 9 (PB1)为规则通道中第一个
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;//清0
    ADC1->SQR3 |= 9<<0;//设置9

    
    // adc_touch_config();
    
    }

    void ZxcAdc::adc_touch_config(){

        ADC1->JSQR = (0 << 20) | (3 << 15);

        // ADC1->JSQR &= ~ADC_JSQR_JL; // 单注入通道模式
        // ADC1->JSQR |= ADC_JSQR_JSQ4_0; // 选择注入序列4(序列有4个，执行排序是倒过来的，4优先)中为第一个通道1
        ADC1->SMPR2 |= ADC_SMPR2_SMP1_0; // 采样时间15个circle，001

    }
    void ZxcAdc::start_adc_touch(){

        // 启动 ADC
        ADC1->CR2 |= ADC_CR2_ADON;
        ADC1->CR2 |= ADC_CR2_JSWSTART; // 手动触发注入转换
    }


    void ZxcAdc::start(){

        ZxcDmaAdc::start();
        /// 配置 DMA 传输
        ADC1->CR2 |= ADC_CR2_DMA; // 使能 DMA
        // 启动 ADC
        ADC1->CR2 |= ADC_CR2_ADON;
        // 启动 ADC 转换
        ADC1->CR2 |= ADC_CR2_SWSTART;
        
    }
    void ZxcAdc::stop(){

        ADC1->CR2 &= ~ADC_CR2_ADON;
    }
} // namespace zxc
