#ifndef __ZXC_LVGL_H__
#define __ZXC_LVGL_H__
#include "lvgl.h"
#include "stm32f4xx.h"
#include "zxc_debug.h"

namespace zxc
{

    class ZxcLvClock{

        private:
        lv_obj_t* scale;
        static lv_obj_t * second_hand;
        static lv_obj_t * minute_hand;
        static lv_obj_t * hour_hand;

        u16 _h;
        u16 _w;
        u32 hour;
        u32 minute;
        u32 second;

        static void set_minute_value(void * obj, int32_t v);
        public:
        lv_obj_t* line1;
        ZxcLvClock(u16 w,u16 h);
        void updata_by_s();
        void create();
        ~ZxcLvClock();
        
    };

    class ZxcMain{

        private:
        static void set_bg();
        public:
        static lv_obj_t* main_bg;
        static void create();
    };

    class ZxcTemp{
        private:
        static const char * custom_labels[6];
        
        static lv_style_t main_line_style;
        static lv_style_t style_indic;
        static lv_obj_t * scale;
        static lv_obj_t * label;
        static lv_style_t label_style;

        public:
        
        static void create();
        static void set_value(double t);
    };
    
    class ZxcHum{

        private:

        static lv_obj_t* label;
        static lv_obj_t* arc;

        static lv_style_t arc_style;
        static lv_style_t style_arc_indic;
        static void value_changed_event_cb(lv_event_t * e);

        public:
        static void create();
        static void set_value(int v);
    };

    class ZxcMaxChart{

        private:

        static lv_obj_t* chart;
        static lv_chart_series_t* ser;
        static lv_obj_t* scale_bottom;
        static lv_obj_t* scale_left;
        static const char* tn[];
        static const char* tn2[];
        static lv_obj_t* label;
        static lv_obj_t* o2_label;

        public:

        static void create();

        static void set_rate(int32_t v);
        static void set_spo2(int32_t v);
    };

    class ZxcCal{

        public:
        static lv_obj_t  * calendar;
        static void create();
    };
} // namespace zxc

#endif