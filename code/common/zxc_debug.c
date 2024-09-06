#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include <stdio.h>
#include <stdarg.h>
#include "usart.h"

int my_fputc(int c, FILE *file)
    {
        zxc_uart_send_str(c);
        return c;
    }

// 自定义 printf 重定向
int debug_info(const char *format, ...) {
    va_list args;
    char buffer[128];
    int len;

    va_start(args, format);
    len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    for (int i = 0; i < len; i++) {
        my_fputc(buffer[i], NULL);
    }

    return len;
}