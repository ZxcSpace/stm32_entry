#ifndef __ZXC_HTU21D_H__
#define __ZXC_HTU21D_H__

#define ADDR_W 0x80
#define ADDR_R 0x81

#include "stm32f4xx.h"
#include "zxc_i2c.h"
#include "zxc_conf.h"
#include "zxc_utils.h"
namespace zxc
{

    
    class ZxcHtu21d{

        private:
        static u16 get_data();
        static ZxcI2c i2c;

        public:

        static void init();

        static float get_temp();//获取温度

        static float get_hum();//获取湿度
    };

    inline u16 ZxcHtu21d::get_data(){

        u8 buffer[3]={0};
        for (u8 i = 0; i < 2; i++)
        {
            i2c.ack();//硬件实现，必须先配置ack/unack
            i2c.read_byte(buffer[i]);
        }
        i2c.unack();
        i2c.read_byte(buffer[2]);

        u16 d = (((u16)buffer[0])<<8)|buffer[1];
        d &= 0xfffc;//清除状态位
        return d;
    }
} // namespace zxc

#endif