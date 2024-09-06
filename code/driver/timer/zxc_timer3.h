#ifndef __ZXC_TIMER3_H__
#define __ZXC_TIMER3_H__
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

namespace zxc
{
    class ZxcTimer3{

    private:
        static void gpio_init_pwm3();

    public:
        static void init_pwm_ch3();
        static void set_pwm_ch3(int16_t v);
    };
} // namespace zxc


#endif