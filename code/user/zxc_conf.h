#ifndef __ZXC_CONF_H__
#define __ZXC_CONF_H__

#include "FreeRTOS.h"
#include "task.h"

#define ZXC_USE_DMA  1
#define ZXC_DMA_SPI_THREAD 64 //使用spi传输数据的阈值字节数
#define ZXC_DMA_USED_BY_FREERTOS 1// 使用rtos来控制dma传输到spi，以释放cpu

#if (ZXC_DMA_USED_BY_FREERTOS==1)

    #define ZXC_DMA_TASK_PRIORITY 3 //dma任务优先级，应该设置较高优先级，防止屏幕刷新被卡
#endif

#define DELAY_MS(ms) vTaskDelay(ms)//指定延时函数
#define HTU21D_MAX_TRY 4//

#define MAX30102_INTERRUPT_PRIORITY 4//中断优先级

#define MAX30102_BUFFER_LEN 500//缓冲区长度
#define MAX30102_UPDATE_DATA_LEN 100//每次更新的数据量

#define ZXC_DMA_ADC_PRIORITY 10//dma传输adc数据传输完成中断优先级
#define ZXC_DMA_ADC_BUFFER_LEN 1000//dma传输adc数据缓冲区长度(16位)

#endif  