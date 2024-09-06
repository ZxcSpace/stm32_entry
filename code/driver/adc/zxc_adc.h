#ifndef __ZXC_ADC_H__
#define __ZXC_ADC_H__
#include "stm32f4xx.h"
#include "zxc_debug.h"
#include "zxc_sys_tick_clock.h"
#include "zxc_dma_adc.h"
namespace zxc
{
   class ZxcAdc
    {
    private:
        ZxcAdc();
        ~ZxcAdc();
    public:
        static void init();
        static void start();

        static void start_adc_touch();
        ;
        static void stop();

        static void adc_touch_config();
        static u16 get_data(){
            // 等待转换完成
            while (!(ADC1->SR & ADC_SR_EOC));
            // 读取 ADC 转换结果
            return ADC1->DR;
        }
        static u16 get_touch_x(){
            // 等待转换完成
            while (!(ADC1->SR & ADC_SR_JEOC));
            // 读取 ADC 转换结果
            ADC1->SR &= ~ADC_SR_JEOC;
            return ADC1->JDR1;
        }
        
    }; 
} // namespace zxc






#endif