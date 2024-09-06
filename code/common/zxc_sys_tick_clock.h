#ifndef __ZXC_SYSCLOCK_H__
#define __ZXC_SYSCLOCK_H__
#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif
void for_delay_ms(uint32_t ms);
void for_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif
#endif