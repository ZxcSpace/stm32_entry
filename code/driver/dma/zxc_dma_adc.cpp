
#include "zxc_dma_adc.h"

namespace zxc
{
    u16 ZxcDmaAdc::buffer[ZXC_DMA_ADC_BUFFER_LEN] = {0};
    void ZxcDmaAdc::init(){



        // 使能 DMA2 时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    DMA2_Stream4->CR &= ~DMA_SxCR_EN;//关闭dma
    //等待关闭
    while ((DMA2_Stream4->CR & DMA_SxCR_EN) != 0);
    

    DMA2_Stream4->CR = //CHSEL 000为通道，spi1tx
                       DMA_SxCR_PL_1 |//pl=10，高优先级
                       DMA_SxCR_MSIZE_0 |//msize：01，//内存数据大小16位
                       DMA_SxCR_PSIZE_0 |//psize：01，//外设数据大小16位
                       DMA_SxCR_MINC | //内存地址按msize大小自增
                       //pinc,外设地址不变
                       //DMA_SxCR_DIR_0 | //传输方向内存到外设，dir=00
                    //    DMA_SxCR_HTIE |//传输半完成中断
                    //    DMA_SxCR_TEIE | //传输错误中断
                    //    DMA_SxCR_DMEIE | //直接传输错误中断
                       DMA_SxCR_TCIE; //dma传输完成中断
    //循环模式
    // DMA2_Stream4->CR |= DMA_SxCR_CIRC;
    
    // // DMA2_Stream4->FCR &= ~(DMA_SxFCR_DMDIS);//使用直连模式

    // // DMA2->LIFCR |= (DMA_LIFCR_CFEIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTCIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3);

    
    // // /* 6. 设置中断优先级 */
    NVIC_SetPriority(DMA2_Stream4_IRQn,ZXC_DMA_ADC_PRIORITY);
    NVIC_EnableIRQ(DMA2_Stream4_IRQn);//使能中断
    }
} // namespace zxc
