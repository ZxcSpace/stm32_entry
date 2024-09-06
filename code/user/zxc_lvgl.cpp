#include "zxc_lvgl.h"
namespace zxc
{


    lv_obj_t * ZxcLvClock::second_hand;
    lv_obj_t * ZxcLvClock::minute_hand;
    lv_obj_t * ZxcLvClock::hour_hand;

    ZxcLvClock::ZxcLvClock(u16 w,u16 h){
        _w = w;
        _h = h;
        hour = 4;
        minute = 10;
        second = 0;


    }
    ZxcLvClock::~ZxcLvClock(){
        
    }
    

    
    void ZxcLvClock::create(){

        scale = lv_scale_create(ZxcMain::main_bg);

        lv_obj_set_size(scale, _w, _h);//设置大小
        lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_INNER);//刻度显示圆的内部
        lv_obj_set_style_bg_opa(scale, LV_OPA_40, 0);//背景透明的60%
        lv_obj_set_style_bg_color(scale, lv_color_black(), 0);//背景黑色
        lv_obj_set_style_radius(scale, LV_RADIUS_CIRCLE, 0);//圆角半径设置很大，就是圆
        lv_obj_align(scale, LV_ALIGN_CENTER, 0, -30);//从中心向上偏移

        lv_scale_set_label_show(scale, true);//显示scale标签

        lv_scale_set_total_tick_count(scale, 61);//设置总刻度数61
        lv_scale_set_major_tick_every(scale, 5);//每5个刻度一个大刻度

        static const char * hour_ticks[] = {"12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", NULL};
        lv_scale_set_text_src(scale, hour_ticks);//设置主要刻度标签

        lv_scale_set_range(scale, 0, 60);

        lv_scale_set_angle_range(scale, 360);
        lv_scale_set_rotation(scale, 270);

        static lv_style_t indicator_style;
        lv_style_init(&indicator_style);

        /* Label style properties */
        lv_style_set_text_font(&indicator_style, LV_FONT_DEFAULT);
        lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
        lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
        lv_style_set_length(&indicator_style, 8); /* tick length */
        lv_style_set_line_width(&indicator_style, 2); /* tick width */
        
        lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

        static lv_style_t minor_ticks_style;
        lv_style_init(&minor_ticks_style);
        lv_style_set_line_color(&minor_ticks_style, lv_color_hex(0x00469b));//刻度颜色
        lv_style_set_length(&minor_ticks_style, 6); /* tick length */
        lv_style_set_line_width(&minor_ticks_style, 2); /* tick width */

        lv_obj_add_style(scale, &minor_ticks_style, LV_PART_ITEMS);

        /* Main line properties */
        static lv_style_t main_line_style;
        lv_style_init(&main_line_style);
        lv_style_set_arc_color(&main_line_style, lv_color_hex(0x2e83f6));//设置圆弧颜色
        lv_style_set_arc_width(&main_line_style, 4);

        lv_style_set_border_color(&main_line_style, lv_color_hex(0x1f426e));//设置边框颜色
        lv_style_set_border_width(&main_line_style, 4);//边框宽度
        lv_style_set_border_opa(&main_line_style, LV_OPA_50);
        lv_style_set_border_side(&main_line_style, LV_BORDER_SIDE_FULL);
        lv_obj_add_style(scale, &main_line_style, LV_PART_MAIN);

        
        hour_hand = lv_line_create(scale);

        lv_obj_set_style_line_width(hour_hand, 5, 0);
        
        lv_obj_set_style_line_rounded(hour_hand, true, 0);
        lv_obj_set_style_line_color(hour_hand, lv_palette_main(LV_PALETTE_LIGHT_BLUE), 0);
        
        minute_hand = lv_line_create(scale);

        lv_obj_set_style_line_width(minute_hand, 3, 0);
        lv_obj_set_style_line_rounded(minute_hand, false, 0);
        lv_obj_set_style_line_color(minute_hand, lv_palette_main(LV_PALETTE_TEAL), 0);
        
        second_hand = lv_line_create(scale);
        lv_obj_set_style_line_width(second_hand, 1, 0);
        lv_obj_set_style_line_rounded(second_hand, false, 0);
        lv_obj_set_style_line_color(second_hand, lv_palette_main(LV_PALETTE_GREY), 0);

        
        

        
        
    }

    void ZxcLvClock::updata_by_s(){

        if (++second>=60)
        {
            second=0;
            minute++;
            if (minute>=60)
            {
                minute=0;
                hour++;
                if (hour>=12)
                {
                    hour=0;
                }
                
            }
        }
        zxc_lv_scale_set_line_needle_value(scale, second_hand, 40, second,-5,-2);
        zxc_lv_scale_set_line_needle_value(scale, minute_hand, 28, minute,-5,-2);
        zxc_lv_scale_set_line_needle_value(scale, hour_hand, 16, hour*5,-5,-2);
    }

    void ZxcLvClock::set_minute_value(void * obj, int32_t v){
        lv_scale_set_line_needle_value((lv_obj_t *)obj, minute_hand, 50, v);
    }
    
 
    lv_obj_t* ZxcMain::main_bg;
    void ZxcMain::set_bg(){

        main_bg = lv_obj_create(NULL);
        lv_obj_set_size(main_bg, 320, 240);
        // 对象位置对齐到屏幕的左上角
        lv_obj_align(main_bg, LV_ALIGN_TOP_LEFT, 0, 0);
        lv_obj_remove_style(main_bg, NULL, LV_PART_SCROLLBAR);//去掉滚动条

        /* 创建一个样式 */
        static lv_style_t style;
        lv_style_init(&style);

        /* 设置渐变背景的颜色 */
        lv_style_set_bg_color(&style, lv_color_hex(0x0f0f0f));   // 起始颜色：蓝色
        lv_style_set_border_width(&style, 0);  // 设置边框宽度为0

        lv_style_set_pad_all(&style,0);

        lv_style_set_radius(&style,0);


        /* 应用样式到屏幕 */
        lv_obj_add_style(main_bg, &style, 0);

    }
    void ZxcMain::create(){
        set_bg();
    }



lv_style_t ZxcTemp::main_line_style;
lv_style_t ZxcTemp::style_indic;
lv_obj_t * ZxcTemp::scale;
lv_obj_t * ZxcTemp::label;
lv_style_t ZxcTemp::label_style;
const char * ZxcTemp::custom_labels[6] = {" -40", "" ,"" ,"", " +60", NULL};
    void ZxcTemp::create(){
    scale = lv_scale_create(ZxcMain::main_bg);
    lv_obj_set_size(scale, 50, 150);//尺寸
    lv_scale_set_label_show(scale, true);//显示标签
    lv_scale_set_mode(scale, LV_SCALE_MODE_VERTICAL_RIGHT);//垂直模式
    lv_obj_align(scale,LV_ALIGN_CENTER,-120,-30);//对齐

    lv_scale_set_total_tick_count(scale, 21);//总的刻度数
    lv_scale_set_major_tick_every(scale, 5);//主刻度数

    lv_obj_set_style_length(scale, 5, LV_PART_ITEMS);//次刻度数
    lv_scale_set_range(scale, -40, 60);

    
    lv_scale_set_text_src(scale, custom_labels);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);
    //设置主刻度
    lv_style_set_length(&indicator_style,8);//长度
    lv_style_set_text_font(&indicator_style, &lv_font_montserrat_10);//字体大小
    lv_style_set_text_color(&indicator_style, lv_palette_darken(LV_PALETTE_BLUE, 3));//字体颜色
    lv_style_set_line_color(&indicator_style, lv_palette_darken(LV_PALETTE_BLUE, 3));//线条颜色
    lv_style_set_line_width(&indicator_style, 1U);  //宽度
    lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

    //小刻度设置
    static lv_style_t minor_ticks_style;
    lv_style_init(&minor_ticks_style);
    lv_style_set_line_color(&minor_ticks_style, lv_palette_lighten(LV_PALETTE_BLUE, 2));
    lv_style_set_line_width(&minor_ticks_style, 1U);    //宽度
    lv_obj_add_style(scale, &minor_ticks_style, LV_PART_ITEMS);


    //设置背景
    
    lv_style_init(&main_line_style);
    /* Main line properties */
    lv_style_set_line_color(&main_line_style, lv_palette_darken(LV_PALETTE_BLUE, 3));
    lv_style_set_line_width(&main_line_style, 2U);
    lv_style_set_arc_color(&main_line_style, lv_color_hex(0x2e83f6));//设置圆弧颜色
    lv_style_set_bg_color(&main_line_style, lv_color_hex(0xFF0000));
    lv_style_set_bg_grad_color(&main_line_style, lv_color_hex(0x0000FF));
    lv_style_set_bg_grad_dir(&main_line_style, LV_GRAD_DIR_VER);
    lv_obj_add_style(scale, &main_line_style, LV_PART_MAIN);

    lv_obj_set_style_bg_opa(scale, LV_OPA_30, 0);//透明度
    lv_obj_set_style_pad_left(scale, 6, 0);//左内边距
    lv_obj_set_style_radius(scale, 8, 0);//圆角半径
    lv_obj_set_style_pad_ver(scale, 10, 0);//上下内边距

    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.font = LV_FONT_DEFAULT;

    //指针标签
    label = lv_label_create(scale);

    lv_style_init(&label_style);

    lv_style_set_text_font(&label_style, &lv_font_montserrat_12); // 修改字体
    lv_style_set_text_color(&label_style, lv_palette_darken(LV_PALETTE_LIGHT_GREEN, 3)); // 修改颜色
    // lv_style_set_size(&label_style,36,16);
    lv_style_set_radius(&label_style,4);
    // 2. 设置背景颜色属性
    lv_style_set_bg_color(&label_style, lv_palette_darken(LV_PALETTE_LAST, 3));  // 设置背景颜色
    lv_style_set_bg_opa(&label_style, LV_OPA_COVER);  // 设置背景不透明
    lv_style_set_pad_all(&label_style, 1);
    lv_style_set_height(&label_style,16);
    lv_style_set_text_align(&label_style,LV_TEXT_ALIGN_LEFT);
    lv_style_set_align(&label_style,LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_style(label,&label_style,LV_PART_MAIN); // 应用样式到标签

    // lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 6, -122); // 设置标签位置//最低是6，最高是-122
    
    
    set_value(0);
    // lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0); // 将标签居中对齐
        
    }

    void ZxcTemp::set_value(double t)
    {
        char buf[16];
        int temp_1 = (int)t;
        int temp_2 = (int)((t - temp_1)*10);
        lv_snprintf(buf, 16, "%s%d.%d",LV_SYMBOL_LEFT,temp_1,temp_2);
        
        //最低温度时pos6，最高温度时-122
        lv_obj_set_pos(label,6,6-(t+40)/100 * 128);

        lv_label_set_text(label, buf);

    }


    lv_obj_t* ZxcHum::label;
    lv_obj_t* ZxcHum::arc;
    lv_style_t ZxcHum::arc_style;
    lv_style_t ZxcHum::style_arc_indic;
    
    void ZxcHum::create(){

        arc = lv_arc_create(ZxcMain::main_bg);
        label = lv_label_create(arc);

        lv_obj_center(label);
        lv_obj_set_style_text_color(label,lv_color_hex(0x2e83f6),0);

        lv_obj_set_size(arc, 60, 60);//大小
        lv_obj_set_pos(arc,245,20);
        lv_arc_set_rotation(arc, 135);
        lv_arc_set_bg_angles(arc, 0, 270);//起始和结束角
        lv_arc_set_value(arc, 0);//当前值
        //去掉指示器
        lv_obj_remove_style(arc, NULL, LV_PART_KNOB);


        // 创建并初始化样式对象
        lv_style_init(&arc_style);
        lv_style_init(&style_arc_indic);

        lv_style_set_arc_color(&arc_style,lv_color_hex(0x191970));
        lv_style_set_arc_opa(&arc_style,LV_OPA_60);
        lv_style_set_arc_width(&arc_style,10);

        lv_style_set_arc_color(&style_arc_indic,lv_color_hex(0x2e83f6));
        lv_style_set_arc_width(&style_arc_indic,4);
        lv_style_set_pad_top(&style_arc_indic,3);

        // 将样式应用到圆弧对象
        lv_obj_add_style(arc, &arc_style, LV_PART_MAIN);
        lv_obj_add_style(arc, &style_arc_indic, LV_PART_INDICATOR);

        lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_send_event(arc, LV_EVENT_VALUE_CHANGED, NULL);//手动发送事件更新

    }

    void ZxcHum::value_changed_event_cb(lv_event_t * e)
    {

        lv_label_set_text_fmt(label, "%" LV_PRId32 "%%", lv_arc_get_value(arc));
    }

    void ZxcHum::set_value(int v){

        lv_arc_set_value(arc, v);//当前值
        lv_obj_send_event(arc, LV_EVENT_VALUE_CHANGED, NULL);//手动发送事件更新
    }


    extern "C" const lv_image_dsc_t zxc_o2;
    lv_obj_t* ZxcMaxChart::chart;
    lv_chart_series_t* ZxcMaxChart::ser;
    lv_obj_t * ZxcMaxChart::scale_bottom;
    lv_obj_t* ZxcMaxChart::scale_left;
    const char * ZxcMaxChart::tn[] = {"60","", "", "", "0",NULL};
    const char * ZxcMaxChart::tn2[] = {"50", "80","110",NULL};
    lv_obj_t* ZxcMaxChart::label;
    lv_obj_t* ZxcMaxChart::o2_label;
    void ZxcMaxChart::create(){

        chart = lv_chart_create(ZxcMain::main_bg);//创建chart
        lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);//数据从右向左
        lv_obj_remove_style(chart, NULL, LV_PART_INDICATOR);//去掉点
        lv_obj_remove_style(chart, NULL, LV_PART_SCROLLBAR);//去掉滚动条
        // lv_obj_set_style_border_width(chart, 0, LV_PART_MAIN);
        lv_chart_set_div_line_count(chart, 0, 0);//不要分割线
        lv_obj_set_size(chart, 120, 60);//大小
        lv_obj_align(chart,LV_ALIGN_BOTTOM_MID,0,-10);//对齐
        lv_chart_set_range(chart,LV_CHART_AXIS_PRIMARY_Y,50,110);
        lv_chart_set_point_count(chart, 60);
        lv_obj_set_style_bg_color(chart,lv_color_hex(0x191970),0);
        lv_obj_set_style_opa(chart,LV_OPA_60,0);
        ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
        

        lv_obj_set_style_pad_left(chart,8,0);
        lv_obj_set_style_pad_right(chart,8,0);
        lv_obj_set_style_pad_top(chart,4,0);
        lv_obj_set_style_pad_bottom(chart,4,0);

        //横向刻度
        scale_bottom = lv_scale_create(chart);
        lv_scale_set_mode(scale_bottom, LV_SCALE_MODE_HORIZONTAL_TOP);
        lv_obj_set_size(scale_bottom, 100, 10);
        lv_scale_set_total_tick_count(scale_bottom, 5);
        lv_scale_set_major_tick_every(scale_bottom, 1);
        lv_obj_align(scale_bottom,LV_ALIGN_CENTER,0,0);
        lv_obj_set_style_text_font(scale_bottom,&lv_font_montserrat_10,0);
        lv_obj_set_style_length(scale_bottom,4,LV_PART_INDICATOR);
        lv_scale_set_text_src(scale_bottom, tn);
        lv_obj_set_style_line_width(scale_bottom,1,LV_PART_INDICATOR);

        lv_obj_set_style_line_color(scale_bottom,lv_color_hex(0x2e83f6),0);//设置刻度条颜色
        lv_obj_set_style_line_color(scale_bottom,lv_color_hex(0x2e83f6),LV_PART_INDICATOR);//设置刻度条颜色
        lv_obj_set_style_text_color(scale_bottom,lv_color_hex(0x2e83f6),LV_PART_INDICATOR);
        // lv_style_set_text_color(&indicator_style, lv_palette_darken(LV_PALETTE_BLUE, 3));//字体颜色
        // lv_style_set_arc_color(&style_arc_indic,lv_color_hex(0x2e83f6));

        //竖线刻度
        scale_left = lv_scale_create(chart);
        lv_scale_set_mode(scale_left, LV_SCALE_MODE_VERTICAL_RIGHT);
        lv_obj_set_size(scale_left, 10, 50);
        lv_scale_set_total_tick_count(scale_left, 3);
        lv_scale_set_major_tick_every(scale_left, 1);
        lv_obj_align(scale_left,LV_ALIGN_CENTER,0,0);
        lv_obj_set_style_text_font(scale_left,&lv_font_montserrat_10,0);
        lv_obj_set_style_length(scale_left,4,LV_PART_INDICATOR);
        lv_scale_set_text_src(scale_left, tn2);
        lv_obj_set_style_line_width(scale_left,1,LV_PART_INDICATOR);
        lv_obj_set_style_line_color(scale_left,lv_color_hex(0x2e83f6),0);//设置刻度条颜色
        lv_obj_set_style_line_color(scale_left,lv_color_hex(0x2e83f6),LV_PART_INDICATOR);//设置刻度条颜色
        lv_obj_set_style_text_color(scale_left,lv_color_hex(0x2e83f6),LV_PART_INDICATOR);

        ///文本显示
        label = lv_label_create(chart);
        lv_obj_align(label,LV_ALIGN_TOP_RIGHT,0,0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_12,0);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_LIGHT_GREEN, 3),0);
        lv_obj_set_style_bg_color(label,lv_palette_darken(LV_PALETTE_LAST, 3),0);
        lv_obj_set_style_bg_opa(label,LV_OPA_100,0);
        lv_obj_set_style_text_align(label,LV_TEXT_ALIGN_CENTER,0);
        lv_label_set_text(label,"0");

        ///////////血样浓度
        lv_obj_t * img1 = lv_image_create(ZxcMain::main_bg);
        lv_image_set_src(img1, &zxc_o2);
        lv_obj_align(img1, LV_ALIGN_BOTTOM_RIGHT, -30, -60);
        o2_label = lv_label_create(img1);
        lv_obj_align(o2_label,LV_ALIGN_CENTER,-6,4);
        lv_obj_set_style_text_font(o2_label,&lv_font_montserrat_12,0);
        lv_label_set_text_fmt(o2_label, "%" LV_PRId32, 0);
        lv_obj_set_style_text_align(o2_label,LV_TEXT_ALIGN_CENTER,0);
        lv_obj_set_style_text_color(o2_label,lv_color_hex(0x9ecdff),0);

    }

    void ZxcMaxChart::set_rate(int32_t v){

        // for(u8 i = 0; i < 60; i++) {
            lv_chart_set_next_value(chart, ser, v);
            lv_label_set_text_fmt(label, "%" LV_PRId32, v);
        // }
    }

    void ZxcMaxChart::set_spo2(int32_t v){
        lv_label_set_text_fmt(o2_label, "%" LV_PRId32, v);
    }

    lv_obj_t  * ZxcCal::calendar;
    void ZxcCal::create(){
        calendar = lv_calendar_create(NULL);
        // lv_obj_set_size(calendar, 185, 230);
        lv_obj_align(calendar, LV_ALIGN_CENTER, 0, 27);
        // lv_obj_add_event_cb(calendar, event_handler, LV_EVENT_ALL, NULL);

        lv_calendar_set_today_date(calendar, 2024, 8, 23);
        lv_calendar_set_showed_date(calendar, 2024, 8);

        /*Highlight a few days*/
        // static lv_calendar_date_t highlighted_days[3];       /*Only its pointer will be saved so should be static*/
        // highlighted_days[0].year = 2021;
        // highlighted_days[0].month = 02;
        // highlighted_days[0].day = 6;

        // highlighted_days[1].year = 2021;
        // highlighted_days[1].month = 02;
        // highlighted_days[1].day = 11;

        // highlighted_days[2].year = 2022;
        // highlighted_days[2].month = 02;
        // highlighted_days[2].day = 22;

        // lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);

        
    }

} // namespace zxc
