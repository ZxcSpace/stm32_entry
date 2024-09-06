#ifndef __ZXC_ST7789_H__
#define __ZXC_ST7789_H__
#include "st7789h2.h"
#include "zxc_spi.h"
#include "zxc_st7789_reg.h"
#include "zxc_sys_tick_clock.h"
#include <string>
#include "zxc_dma.h"
#include "zxc_conf.h"


namespace zxc
{

    enum ScreenMode{
        PORTRAIT,
        PORTRAIT_180,
        LANDSCAPE,
        LANDSCAPE_180
    };

    class ZxcSt7789{

    private:

        static void data_mode();
        static void cmd_mode();
        //向指定地址写入指定长度的数据
        static void write(uint16_t reg, uint8_t *pdata, uint32_t length);
        //向指定地址写入一个字节数据
        static void write(uint16_t reg, uint8_t pdata);
        //写入指定长度数据
        static void write(uint8_t* pdata, uint32_t length);
        //写入地址
        static void write( uint8_t cmd);
        static void read(uint16_t reg, uint8_t *pdata, uint32_t length);
        

        static void reset_hardware();
        static void set_reg_modes(ScreenMode mode);

        //设置写入数据的区域，列起始位，页(一行像素)起始，列结束(包含结束位)，页结束(包含结束位)
        static void set_area(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);

        static uint16_t width;
        static uint16_t height;

    public:
        static void start();
        static void stop();
        
        //获取屏幕宽度，主要是旋屏情况下
        static uint16_t get_width(){
            return width;
        }
        //获取屏幕高度
        static uint16_t get_height(){
            return height;
        }
        //切换屏幕的横竖屏
        static void rotate_screen_mode(ScreenMode mode);

        //初始化
        static void init(uint16_t screen_width, uint16_t screen_height);
        //获取id
        static void get_id(u8* ids);
        //显示反转
        static void display_reverse(bool rev);
        //在指定矩形内画填充颜色
        static void draw_window(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end,u8* colors);


    };
    inline void ZxcSt7789::reset_hardware(){
        //复位
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);
        for_delay_ms(10);
        GPIO_SetBits(GPIOB,GPIO_Pin_14);
        for_delay_ms(20);
    }


    inline void ZxcSt7789::start(){
        GPIOA->BSRR = (uint32_t)GPIO_Pin_4 << 16;
        // GPIO_ResetBits(GPIOA,GPIO_Pin_4);
    }
    inline void ZxcSt7789::stop(){
        GPIOA->BSRR = GPIO_Pin_4;
        // GPIO_SetBits(GPIOA,GPIO_Pin_4);
    }

    inline void ZxcSt7789::data_mode(){
        GPIOB->BSRR = GPIO_Pin_13;
        // GPIO_SetBits(GPIOB,GPIO_Pin_13);
    }
    inline void ZxcSt7789::cmd_mode(){
        GPIOB->BSRR = (uint32_t)GPIO_Pin_13 << 16;
        // GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    }

    
    //为了提高效率，内联，并手动实现，其实这个作用意义不大，每帧只调用一次
    inline void ZxcSt7789::set_area(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end){

        
        start();
        cmd_mode();
        ZxcSpi1::send(ST7789V2_CASET);
        data_mode();
        ZxcSpi1::send(x_start >> 8);
        ZxcSpi1::send(x_start & 0xFF);
        ZxcSpi1::send(x_end >> 8);
        ZxcSpi1::send(x_end & 0xFF);
        cmd_mode();
        ZxcSpi1::send(ST7789V2_RASET);
        data_mode();
        ZxcSpi1::send(y_start >> 8);
        ZxcSpi1::send(y_start & 0xFF);
        ZxcSpi1::send(y_end >> 8);
        ZxcSpi1::send(y_end & 0xFF);
        stop();

        
    }
    //在指定区域画图，供lvgl调用，提高效率内联并手动实现
    inline void ZxcSt7789::draw_window(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end,u8* colors){
        set_area(x_start,y_start,x_end,y_end);
        //len为总字节数，每个像素2个字节
        int len = (x_end-x_start+1) * (y_end - y_start + 1) * 2;

            #if (ZXC_USE_DMA==1)
            
            start();
            cmd_mode();
            
            ZxcSpi1::send(ST7789V2_WRITE_RAM);
            
            data_mode();
            while (len>0)
            {
                if (len > ZXC_DMA_SPI_THREAD)
                {
                    #if (ZXC_DMA_USED_BY_FREERTOS==1)
                    ZxcDma::start_by_rtos((uint32_t)(&SPI1->DR),(uint32_t)colors,(len>65535)?65535:len);
                    ZxcDma::wait_can_dma_rtos();
                    len-=65535;
                    colors+=65535;
                    #else
                    ZxcDma::can_dma_flag=false;           
                    ZxcDma::start((uint32_t)(&SPI1->DR),(uint32_t)colors,(len>65535)?65535:len);
                    len-=65535;
                    colors+=65535;
                    // SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
                    while (!ZxcDma::can_dma_flag);//等待传输完成，完成前不能stop，否则终止
                    #endif

                    

                }
                else{

                    for (int i = 0; i < len; i++)
                    {
                        ZxcSpi1::send(colors[i]);
                    }
                    break;
                } 
                
            }
            
            stop();
        #else
            //直接写入
            start();
            cmd_mode();
            ZxcSpi1::send(ST7789V2_WRITE_RAM);
            data_mode();
            

                DEBUG_INFO("%d_%d",len,len);

                for (int i = 0; i < len; i++)
                {
                    ZxcSpi1::send(colors[i]);
                }
                
           
            stop();
            
        #endif


    }
} // namespace zxc



#endif