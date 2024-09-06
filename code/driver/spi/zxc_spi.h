#ifndef __ZXC_SPI_H__
#define __ZXC_SPI_H__
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "zxc_conf.h"

namespace zxc{

    class ZxcSpi1{

    public:
        static void init();
        static void send(u8 d);
        static u8 recv();
        static void enable_dma_tx();
        static void disable_dma_tx();
    };

    inline void ZxcSpi1::send(u8 d){

        while ((SPI1->SR & SPI_SR_TXE) == 0); // 等待发送寄存器空
        // SPI_I2S_SendData(SPI1, d); // 发送数据
        SPI1->DR = d;
        while ((SPI1->SR & SPI_SR_RXNE) == 0); // 等待接收寄存器非空
        (void)(SPI1->DR & 0xff); // 读取接收到的数据以清除 RXNE 标志
    }

    inline u8 ZxcSpi1::recv(){

        while ((SPI1->SR & SPI_SR_TXE) == 0); // 等待发送寄存器空
        SPI1->DR = 0xff; // 发送 dummy byte
        while ((SPI1->SR & SPI_SR_RXNE) == 0); // 等待接收寄存器非空

        return (uint8_t)(SPI1->DR & 0xff);
    }

    inline void ZxcSpi1::enable_dma_tx(){
        SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    }

    inline void ZxcSpi1::disable_dma_tx(){
        SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, DISABLE);
    }

}
#endif