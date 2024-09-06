#ifndef __USART_H__
#define __USART_H__
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
    extern "C" {
#endif


void zxc_uart_init();
void zxc_uart_send_str(char str);
void zxc_uart_send_strs(const char* str,u16 len);
char zxc_uart_read_char();
void zxc_uart_read_strs(char* buff,u16 len);
u16 zxc_uart_read_str(char* buff);

#ifdef __cplusplus
    }
#endif



#endif