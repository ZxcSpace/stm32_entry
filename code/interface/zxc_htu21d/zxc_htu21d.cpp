#include "zxc_htu21d.h"
#include "zxc_debug.h"

namespace zxc
{
    ZxcI2c ZxcHtu21d::i2c = {I2C1,GPIOB,6,7};
    void ZxcHtu21d::init(){
        i2c.init();
    }
    float ZxcHtu21d::get_temp(){

        bool rs = i2c.start();
       
        rs = i2c.send_addr(ADDR_W);
        rs = i2c.send_byte(0xf3);
        DELAY_MS(50);
        u8 count = HTU21D_MAX_TRY;
        u16 d = 0;
        while (count--)
        {
            i2c.start();
            rs=i2c.send_addr(ADDR_R);
            if (rs){
                d = get_data();
                break;
            }
            DELAY_MS(10);           
        }
        
        return  -46.85 + (175.72 * d) / 65536.0;

    }

    float ZxcHtu21d::get_hum(){

        bool rs = i2c.start();
       
        rs = i2c.send_addr(ADDR_W);
        rs = i2c.send_byte(0xf5);
        DELAY_MS(20);
        u8 count = HTU21D_MAX_TRY;
        u16 d = 0;
        while (count--)
        {
            i2c.start();
            rs=i2c.send_addr(ADDR_R);
            if (rs){
                d = get_data();
                break;
            }
            DELAY_MS(10);           
        }
        
        return  -6.0 + (125.0 * d) / 65536.0;
    }
} // namespace zxc
