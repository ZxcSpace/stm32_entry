/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION		1 //启用抢占式调度器
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( ( unsigned long ) 100000000 ) //CPU频率,无默认需定义
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 ) //rtos系统时钟频率,无默认需定义
#define configMAX_PRIORITIES		( 5 ) //最大优先级数, 最大优先级=configMAX_PRIORITIES-1, 无默认需定义
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 32 * 1024 ) )//FreeRTOS堆中可用的RAM总量, 单位: Byte, 无默认需定义
#define configMAX_TASK_NAME_LEN		( 16 )//任务名字长度
#define configUSE_TRACE_FACILITY	0 //使能可视化跟踪调试, 默认: 0
#define configUSE_16_BIT_TICKS		1 //定义系统时钟节拍计数器的数据类型为16位无符号数, 无默认需定义
#define configIDLE_SHOULD_YIELD		1 //使能在抢占式调度下,同优先级的任务能抢占空闲任务, 默认: 1


#define xPortPendSVHandler  PendSV_Handler
#define vPortSVCHandler     SVC_Handler
#define xPortSysTickHandler SysTick_Handler
#define INCLUDE_xTaskGetSchedulerState   1

#define configSUPPORT_DYNAMIC_ALLOCATION 1//开启动态创建任务
#define configUSE_RECURSIVE_MUTEXES 1
// #define configSUPPORT_STATIC_ALLOCATION 1//开启静态创建任务

// #define configUSE_COUNTING_SEMAPHORES 1//开启信号量
/* 软件定时器相关定义 */
#define configUSE_TIMERS 1                                          /* 1: 使能软件定时器, 默认: 0。使能后需指定下面3个 */
#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES - 1)        /* 定义软件定时器任务的优先级 */
#define configTIMER_QUEUE_LENGTH 5                                  /* 定义软件定时器命令队列的长度*/
#define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE * 2) /* 定义软件定时器任务的栈空间大小*/


// #define INCLUDE_vTaskSuspend 1//开启任务挂起功能
// #define INCLUDE_xResumeFromISR 1//开启中断中任务挂起功能
// #define configUSE_MUTEXES 1

// #define configUSE_TRACE_FACILITY 1//获取任务信息需要开启的
// #define INCLUDE_uxTaskGetStackHighWaterMark 1

#define configUSE_QUEUE_SETS 1
#define configUSE_MUTEXES 1




/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY 		255
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	191 /* equivalent to 0xb0, or priority 11. */


/* This is the value being used as per the ST library which permits 16
priority values, 0 to 15.  This must correspond to the
configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15

#endif /* FREERTOS_CONFIG_H */

