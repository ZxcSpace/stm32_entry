
#include "usart.h"
#include <stdio.h>

void zxc_uart_init(){
    // //开启gpioa的时钟
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

//启用uart1时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//配置a9复用推挽，a10浮空输入
GPIO_InitTypeDef gpioa_init_structure;


gpioa_init_structure.GPIO_Pin = GPIO_Pin_9;
gpioa_init_structure.GPIO_Mode = GPIO_Mode_AF;//复用功能
gpioa_init_structure.GPIO_OType = GPIO_OType_PP;//推挽输出
gpioa_init_structure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
gpioa_init_structure.GPIO_Speed = GPIO_Speed_50MHz;//输出速度
GPIO_Init(GPIOA,&gpioa_init_structure);

gpioa_init_structure.GPIO_Pin = GPIO_Pin_10;
// gpioa_init_structure.GPIO_Mode = GPIO_Mode_AF;
// gpioa_init_structure.GPIO_OType = GPIO_OType_OD;//浮空
// gpioa_init_structure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA,&gpioa_init_structure);

// 选择 PA9 和 PA10 的复用功能（USART1）
GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

//配置uart1
USART_InitTypeDef uart1;
uart1.USART_BaudRate = 115200;
uart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不用硬件控制流
uart1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//全双工
uart1.USART_Parity = USART_Parity_No;//不要校验
uart1.USART_StopBits = USART_StopBits_1;//停止位1
uart1.USART_WordLength = USART_WordLength_8b;//8位

USART_Init(USART1,&uart1);
//使能
USART_Cmd(USART1,ENABLE);
}

void zxc_uart_send_str(char str){

    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, str);
}

void zxc_uart_send_strs(const char* str,u16 len){

    for(u16 i = 0; i < len; i++){
        // 等待 USART1 数据寄存器空
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, str[i]);
    }

}
char zxc_uart_read_char(){
    // 等待接收数据寄存器非空
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (char)USART_ReceiveData(USART1);
}
void zxc_uart_read_strs(char* buff,u16 len){

    while (len--) {
    *buff++ = zxc_uart_read_char();
}
}
u16 zxc_uart_read_str(char* buff){
    u16 len=0;
    while (1) {
        // 等待接收数据寄存器非空
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){
        // 检查空闲标志,如果空闲则跳出
        if (USART_GetFlagStatus(USART1, USART_FLAG_IDLE) != RESET){
            return len;
        }
    }
    buff[len++] = USART_ReceiveData(USART1);
        
        
    }
}
 


