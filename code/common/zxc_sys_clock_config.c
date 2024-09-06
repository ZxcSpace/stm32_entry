
#include "zxc_sys_clock_config.h"
#include "stm32f4xx.h"

#define RCC_PLLSOURCE 1//启用hse
#define PLL_M 8
#define PLL_N 200
#define PLL_P 2
#define PLL_Q 4
void zxc_sys_clock_config(){



  RCC_PLLCmd(DISABLE);
    RCC_PLLConfig(RCC_PLLSOURCE,PLL_M,PLL_N,PLL_P,PLL_Q);

    RCC_PLLCmd(ENABLE);
    SystemCoreClockUpdate();
  
}
