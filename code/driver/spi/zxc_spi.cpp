#include "zxc_spi.h"
#include "zxc_debug.h"

namespace zxc
{
    
    void ZxcSpi1::init(){
        SPI_InitTypeDef SPI_InitStructure;
        GPIO_InitTypeDef GPIO_InitStructure;

        // 使能 SPI1 和 GPIOA 时钟
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

        // 配置 GPIOA 的 SPI1 引脚
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; // SCK, MISO, MOSI
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 复用功能
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 上拉/下拉电阻
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        // 设置引脚为 SPI 功能
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1); // SCK
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1); // MISO
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1); // MOSI

        // 配置 SPI1
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // 全双工模式
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // 主设备模式
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // 数据位宽
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; // 时钟极性
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // 时钟相位
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // 软件管理模式
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // 波特率预分频
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // 数据位顺序
        SPI_InitStructure.SPI_CRCPolynomial = 10; // CRC 多项式
        SPI_Init(SPI1, &SPI_InitStructure);

        #if (ZXC_USE_DMA == 1)
        SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);//只要空闲状态，就会产生dma请求
        #endif
        // 使能 SPI1
        SPI_Cmd(SPI1, ENABLE);

        


    }

    
} // namespace zxc
