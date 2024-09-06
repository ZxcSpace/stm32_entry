#ifndef __ZXC_RTOS_H__
#define __ZXC_RTOS_H__
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "zxc_htu21d.h"
#include "zxc_debug.h"
#include "zxc_max30102.h"
#include "zxc_st7789.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "zxc_adc.h"
#include "zxc_adc_touch.h"
#include "zxc_lvgl.h"
#include "math.h"
#include "zxc_tflm.h"
#include "timers.h"

namespace zxc
{

    

    class ZxcRTOS{

        private:

        static double temp;
        static int hum;
        static int rate;
        static int spo2;

        static void htu21d_task();
        static void max30102_task();
        static void lv_timer_task();
        static void lv_draw_task();
        static void sound_task();
        static void touch_task();

        public:
        static QueueHandle_t lvgl_lock_semapor;
        static QueueHandle_t max_lock_semapor;
        static TaskHandle_t htu21d_handle;
        static TaskHandle_t max30102_handle;
        static TaskHandle_t lv_timer_handle;
        static TaskHandle_t draw_handle;
        static TaskHandle_t sound_handle;
        static TaskHandle_t touch_handle;
        static void init();
    };
} // namespace zxc

#endif