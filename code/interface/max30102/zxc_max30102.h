#ifndef __ZXC_MAX30102_H__
#define __ZXC_MAX30102_H__

#include "stm32f4xx.h"
#include "zxc_i2c.h"
#include "zxc_debug.h"
#include "zxc_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "zxc_utils.h"
#include "algorithm.h"

#define MAX_ADDR_W 0XAE
#define MAX_ADDR_R 0XAF


namespace zxc
{

    
    
    class ZxcMax30102{
        private:
        static ZxcI2c i2c;
        static void config_interupt();
        static ZxcCircleBuffer red_buffer;
        static ZxcCircleBuffer ir_buffer;
        public:

        static QueueHandle_t semapor;
        static void init();
        static void write(u8 reg, u8 data);
        static bool read(u8 reg,u8* buffer,u8 len);
        //从fifo中读取数据
        static bool read(u32& red_led_data,u32& ir_led_data);
        static void wait_interrupt_by_rtos();//等待数据中断，使用rtos信号量
        static void append(uint32_t red, uint32_t ir);
        static void get_sp02_and_rate(int* sp02, int* rate,int8_t* spo2_valid,int8_t* rate_valid);


    };

    inline void ZxcMax30102::write(u8 reg, u8 data){

        i2c.start();
        i2c.send_addr(MAX_ADDR_W);
        i2c.send_byte(reg);
        i2c.send_byte(data);
        i2c.stop();

    }

    inline bool ZxcMax30102::read(u8 reg,u8* buffer,u8 len){

        i2c.start();
        bool rs = i2c.send_addr(MAX_ADDR_W);
        rs = i2c.send_byte(reg);
        i2c.start();
        rs = i2c.send_addr(MAX_ADDR_R);
        rs = true;
        for (u8 i = 0; i < len; i++)
        {
            if (i<len-1)
            {
                i2c.ack();
            }
            else{
                i2c.unack();
                i2c.stop();
            }
            rs &= i2c.read_byte(buffer[i]);
            
        }
        return rs;
    }

     inline void ZxcMax30102::wait_interrupt_by_rtos(){
        u8 dump;
        while (!xSemaphoreTake(semapor,300))
        {
            read(0x00,&dump,1);//清除溢出状态
        }
        
        
     }

     inline void ZxcMax30102::append(uint32_t red, uint32_t ir){

        
        
        red_buffer.append(red,false);
        ir_buffer.append(ir,false);

     }
} // namespace zxc

#endif