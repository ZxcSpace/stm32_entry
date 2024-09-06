#ifndef __ZXC_DEBUG_H__
#define __ZXC_DEBUG_H__
#include "usart.h"
#include <string.h>

#ifdef __cplusplus
    extern "C" {
#endif
int debug_info(const char *format, ...);

#ifdef __cplusplus
    }
#endif
#define ZXC_DEBUG 1//置为0关闭debug
#if ZXC_DEBUG
#define FILE_NAME strrchr(__FILE__,'\\') ? strrchr(__FILE__,'\\')+1:__FILE__
#define DEBUG_INFO(format,...) debug_info(("[%s:%d]- -" format "\r\n"),FILE_NAME ,__LINE__,##__VA_ARGS__)

#else
#define FILE_NAME
#define DEBUG_INFO(format,...)

#endif
#endif