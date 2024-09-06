#include "stm32f4xx.h"
#include "zxc_st7789.h"
#include "zxc_spi.h"
#include "zxc_dma.h"
#include "zxc_debug.h"
#include "zxc_max30102.h"
#include "zxc_rtos.h"



extern "C" void DMA2_Stream3_IRQHandler(void){

    if (DMA2->LISR & DMA_LISR_TCIF3)//传输完成
    {      
        
        
        // DMA2->LIFCR |= (DMA_LIFCR_CFEIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTCIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3);  
        DMA2->LIFCR |= DMA_LIFCR_CTCIF3;//清除传输完成标志位
        DMA2_Stream3->CR &= ~DMA_SxCR_EN;//关闭dm2 stream3 
        //等待关闭
        while((DMA2_Stream3->CR & DMA_SxCR_EN) != RESET);

        #if (ZXC_DMA_USED_BY_FREERTOS==1)
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        //释放传输完成完成信号量
        xSemaphoreGiveFromISR(zxc::ZxcDma::semapor,&xHigherPriorityTaskWoken);
        // 根据返回值确定是否上下文切换
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        #else
        zxc::ZxcDma::can_dma_flag = true;//标识dma可以再次传输
        #endif

        

    }


}

extern "C" void DMA2_Stream4_IRQHandler(void){

    /// 配置 DMA 传输
    //单次使用，从外设到内存，必须在这里关闭dma
    //即外设的使用dma配置必须在dma启动之后，要想再次启用dma，必须先关闭外设dma使能
    ADC1->CR2 &= ~ADC_CR2_DMA; // 关闭 DMA

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    //通知sound任务
    xTaskNotifyFromISR(zxc::ZxcRTOS::sound_handle,0x01,eNoAction,&xHigherPriorityTaskWoken);
    
    //释放传输完成完成信号量
    // xSemaphoreGiveFromISR(zxc::ZxcRTOS::dma_adc_semapor,&xHigherPriorityTaskWoken);
    DMA2->HIFCR |= DMA_HIFCR_CTCIF4;//清除传输完成标志位
    // 根据返回值确定是否上下文切换
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    
    

}


extern "C" void EXTI9_5_IRQHandler(void) {

    //如果中断来自8
    if ((EXTI->PR & EXTI_PR_PR8) != 0) {
        
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        //释放传输完成完成信号量       
        xSemaphoreGiveFromISR(zxc::ZxcMax30102::semapor,&xHigherPriorityTaskWoken);
        // 根据返回值确定是否上下文切换
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        // 清除 8的中断标志
        EXTI->PR |= EXTI_PR_PR8;
    }
}