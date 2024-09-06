

#ifndef __ZXC_DMA_H__
#define __ZXC_DMA_H__
#include "stm32f4xx.h"
#include "zxc_debug.h"
#include "zxc_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

namespace zxc
{
    #if (ZXC_DMA_USED_BY_FREERTOS==1)
    struct ZxcDmaQueueData
    {
        uint32_t peripheral_addr; 
        uint32_t buffer_addr; 
        uint16_t data_len;
    };
    #endif
    
    class ZxcDma{

        private:
     
        

        public:

        static bool can_dma_flag;

       
        static void init();
        //外设地址，内存地址//数据长度(16位，最大65535)
        static void start(uint32_t peripheral_addr, uint32_t buffer_addr, uint16_t data_len);

        #if (ZXC_DMA_USED_BY_FREERTOS==1)
            static TaskHandle_t dma_task_handle;
            static QueueHandle_t queue;//用来传递刷新的图像数据
            static QueueHandle_t semapor;//用来通知dma传输完成，可以继续
            static void start_dma_task();
            static void start_by_rtos(uint32_t peripheral_addr, uint32_t buffer_addr, uint16_t data_len);
            static void dma_task();
            static void wait_can_dma_rtos();
        #endif

        
    };

    inline void ZxcDma::start(uint32_t peripheral_addr, uint32_t buffer_addr, uint16_t data_len){

    
        //关闭dma使能，已在传输完成中断中关闭
        DMA2_Stream3->CR &= ~DMA_SxCR_EN;

        DMA2_Stream3->PAR = peripheral_addr;   // 外设地址
        DMA2_Stream3->M0AR = buffer_addr;      // 内存地址
        DMA2_Stream3->NDTR = data_len;           // 数据传输量

        
        //清除状态，已在传输完成中断中清除
        DMA2->LIFCR |= (DMA_LIFCR_CFEIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTCIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3);
        DMA2_Stream3->CR |= DMA_SxCR_EN;//使能dm2 stream3

    }
    #if (ZXC_DMA_USED_BY_FREERTOS==1)
    //启用dma，向dma发送数据，开始传输
    inline void ZxcDma::start_by_rtos(uint32_t peripheral_addr, uint32_t buffer_addr, uint16_t data_len){
        ZxcDmaQueueData data = {
                                peripheral_addr,
                                buffer_addr,
                                data_len,
                                };
        xQueueSend(queue,&data,portMAX_DELAY);
    }

    inline void ZxcDma::wait_can_dma_rtos(){

        xSemaphoreTake(semapor,portMAX_DELAY);//等待完成
    }
    #endif

 
} // namespace zxc

#endif