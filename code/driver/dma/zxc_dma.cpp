#include "zxc_dma.h"


namespace zxc{
    bool ZxcDma::can_dma_flag = true;


    void ZxcDma::init(){

        // 使能 DMA2 时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    DMA2_Stream3->CR &= ~DMA_SxCR_EN;//关闭dma
    //等待关闭
    while ((DMA2_Stream3->CR & DMA_SxCR_EN) != 0);
    

    DMA2_Stream3->CR = DMA_SxCR_CHSEL_0 |
                       DMA_SxCR_CHSEL_1 |//CHSEL 011为通道3，spi1tx
                       DMA_SxCR_PL_1 |//pl=10，高优先级
                       //msize：00，内存数据大小8位
                       //psize：00，外设数据大小8位
                       DMA_SxCR_MINC | //内存地址按msize大小自增
                       //pinc,外设地址不变
                       DMA_SxCR_DIR_0 | //传输方向内存到外设，dir=01
                    //    DMA_SxCR_HTIE |//传输半完成中断
                    //    DMA_SxCR_TEIE | //传输错误中断
                    //    DMA_SxCR_DMEIE | //直接传输错误中断
                       DMA_SxCR_TCIE; //dma传输完成中断
    
    // DMA2_Stream3->FCR &= ~(DMA_SxFCR_DMDIS);//使用直连模式

    // DMA2->LIFCR |= (DMA_LIFCR_CFEIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTCIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3);

    
    // /* 6. 设置中断优先级 */
    NVIC_SetPriority(DMA2_Stream3_IRQn,0);
    NVIC_EnableIRQ(DMA2_Stream3_IRQn);

    #if (ZXC_DMA_USED_BY_FREERTOS==1)
    //初始化
        queue = xQueueCreate(2,sizeof(ZxcDmaQueueData));
        semapor = xSemaphoreCreateBinary(); 
        start_dma_task();
    #endif

    }

    #if (ZXC_DMA_USED_BY_FREERTOS==1)

    TaskHandle_t ZxcDma::dma_task_handle;
    QueueHandle_t ZxcDma::queue;
    QueueHandle_t ZxcDma::semapor;
    //创建dma传输任务
    void ZxcDma::start_dma_task(){

        xTaskCreate( (TaskFunction_t)dma_task,
                            "dma_task",
                            512,
                            NULL,
                            ZXC_DMA_TASK_PRIORITY,
                            &dma_task_handle);
    }

    void ZxcDma::dma_task(){
        ZxcDmaQueueData buffer;
        while (1)
        {
            xQueueReceive(queue,&buffer,portMAX_DELAY);//等待数据
            start(buffer.peripheral_addr, buffer.buffer_addr, buffer.data_len);
        }
        
        
        
    }
    #endif



}

