#ifndef __ZXC_DMA_ADC_H__
#define __ZXC_DMA_ADC_H__

#include "stm32f4xx.h"
#include "zxc_debug.h"
#include "zxc_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "zxc_sys_tick_clock.h"

namespace zxc
{
    class ZxcDmaAdc{

    private:

    public:
        static u16 buffer[ZXC_DMA_ADC_BUFFER_LEN];
        static void init();
        static void start(){

            //关闭dma使能
            DMA2_Stream4->CR &= ~DMA_SxCR_EN;
            DMA2_Stream4->PAR = (uint32_t)(&ADC1->DR);   // 外设地址
            DMA2_Stream4->M0AR = (uint32_t)buffer;      // 内存地址
            DMA2_Stream4->NDTR = ZXC_DMA_ADC_BUFFER_LEN;           // 数据传输量

            //清除状态
            DMA2->HIFCR |= (DMA_HIFCR_CFEIF4 | DMA_HIFCR_CHTIF4 | DMA_HIFCR_CTCIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CDMEIF4);
            DMA2_Stream4->CR |= DMA_SxCR_EN;//使能dm2 stream4

        } 
    };
} // namespace zxc

#endif