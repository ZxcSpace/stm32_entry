#include "zxc_st7789.h"

namespace zxc{

    uint16_t ZxcSt7789::width;
    uint16_t ZxcSt7789::height;


    void ZxcSt7789::init(uint16_t screen_width, uint16_t screen_height){
        width = screen_width;
        height = screen_height;

        ZxcDma::init();
        ZxcSpi1::init();

        // #if (ZXC_USE_DMA==1)
        
        // #endif

        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

        // 配置 GPIOA 的 cs 引脚
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; // cs
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 上拉/下拉电阻
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        //数据/命令(d/c)引脚
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_Init(GPIOB,&GPIO_InitStructure);
        //复位引脚
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
        GPIO_Init(GPIOB,&GPIO_InitStructure);
        stop();
        
        reset_hardware();
        
        set_reg_modes(LANDSCAPE);
        

    }


    static void change_v_v(uint16_t& v1, uint16_t& v2){

        uint16_t tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    void ZxcSt7789::rotate_screen_mode(ScreenMode mode){

        switch (mode)
        {
        case PORTRAIT:
            write(ST7789V2_MADCTL,0x00);//竖屏模式(默认模式)
            break;
        case PORTRAIT_180:
            write(ST7789V2_MADCTL,0xc0);//竖屏旋转180
            break;

        case LANDSCAPE:
            write(ST7789V2_MADCTL,0x60);//横屏模式
            change_v_v(width,height);
            break;

        case LANDSCAPE_180:
            write(ST7789V2_MADCTL,0xa0);//横屏旋转180
            change_v_v(width,height);
            break;
        
        default:
            write(ST7789V2_MADCTL,0x00);
            break;
        }
    }
    void ZxcSt7789::set_reg_modes(ScreenMode mode){

        u8 datas[16] = {0};
        // 复位
        write(ST7789V2_SW_RESET);
        for_delay_ms(150);
        // // 退出睡眠模式
        write(ST7789V2_SLEEP_OUT);
        for_delay_ms(120);

        rotate_screen_mode(mode);


        write(ST7789V2_GATE_CTRL,0x35);

        write(ST7789V2_VCOM_SET,0x1f);

        write(ST7789V2_LCM_CTRL,0x2c);

        datas[0] = 0x01;
        datas[1] = 0xc3;
        write(ST7789V2_VDV_VRH_EN,datas,2);

        write(ST7789V2_VDV_SET,0x20);

        write(ST7789V2_FR_CTRL,0x0f);

        datas[0] = 0xa4;
        datas[1] = 0xa1;
        write(ST7789H2_POWER_CTRL,datas,2);//电源控制

        datas[0]  = 0xD0;
        datas[0] = 0xd0;
        datas[1]  = 0x08;
        datas[2]  = 0x11;
        datas[3]  = 0x08;
        datas[4]  = 0x0C;
        datas[5] = 0x15;
        datas[6] = 0x39;
        datas[7] = 0x33;
        datas[8] = 0x50;
        datas[9] = 0x36;
        datas[10] = 0x13;
        datas[11] = 0x14;
        datas[12] = 0x29;
        datas[13] = 0x2D;
        write(ST7789V2_PV_GAMMA_CTRL,datas,14);//gamma校准

        datas[0]  = 0xD0;
        datas[1]  = 0x08;
        datas[2]  = 0x10;
        datas[3]  = 0x08;
        datas[4]  = 0x06;
        datas[5] = 0x06;
        datas[6] = 0x39;
        datas[7] = 0x44;
        datas[8] = 0x51;
        datas[9] = 0x0B;
        datas[10] = 0x16;
        datas[11] = 0x14;
        datas[12] = 0x2F;
        datas[13] = 0x31;
        write(ST7789V2_NV_GAMMA_CTRL,datas,14);

        write(ST7789V2_TE_LINE_ON,0x01);

        write(ST7789V2_COLOR_MODE,0x55);//颜色格式：rgb 55k：0x55 rgb 262k：0x66，66是18位，spi写入时需要注意
    
        //显示信号设置
        datas[0] = 0x0C;
        datas[1] = 0x0C;
        datas[2] = 0x00;
        datas[3] = 0x33;
        datas[4] = 0x33;
        write(ST7789V2_PORCH_CTRL,datas,5);

        write(ST7789V2_GATE_CTRL,0x35);
        write(ST7789V2_DISPLAY_INVERSION_OFF);//不反转颜色
        write (ST7789V2_NORMAL_DISPLAY_ON);
        write(ST7789V2_DISPLAY_ON);//开启显示
        // write(ST7789V2_SLEEP_OUT);
        for_delay_ms(50);

        
    }

    //显示反转
    void ZxcSt7789::display_reverse(bool rev){
        if (rev)
        {
            write(ST7789V2_DISPLAY_INVERSION_ON);
        }else{
            write(ST7789V2_DISPLAY_INVERSION_OFF);
        }
        
    }

    

    void ZxcSt7789::write(uint16_t reg, uint8_t *pdata, uint32_t length){

        cmd_mode();
        start();
        ZxcSpi1::send(reg);
        stop();

        data_mode();
        start(); 
        
        for (uint32_t i = 0; i < length; i++)
        {
            
            ZxcSpi1::send(pdata[i]);
            
        }
        stop();
        
    }

    void ZxcSt7789::write(uint16_t reg, uint8_t pdata){

        cmd_mode();
        start();
        ZxcSpi1::send(reg);
        stop();
        data_mode();
        start();
        ZxcSpi1::send(pdata);
        
        stop();
        
    }
    void ZxcSt7789::write(uint8_t* pdata, uint32_t length){

        data_mode();
        start(); 
        
        for (uint32_t i = 0; i < length; i++)
        {
            
            ZxcSpi1::send(pdata[i]);
            
        }
        stop();

    }
    void ZxcSt7789::read(uint16_t reg, uint8_t *pdata, uint32_t length){

        cmd_mode();
        start();
        ZxcSpi1::send(reg);
        // stop();
        data_mode();
        
        for (uint32_t i = 0; i < length; i++)
        {
            // start();
            pdata[i] = ZxcSpi1::recv();
            
        }
        stop();
        
        

    }
    void ZxcSt7789::write(uint8_t reg){
        start();

        cmd_mode();

        ZxcSpi1::send(reg);

        stop();
    }




    void ZxcSt7789::get_id(u8* ids){
        

        read(0x04,ids,3);//需要注意的：获取3个id 0x04 需要一个空跳变，所以使用spi读取会产生右移一位的现象
        // read(ST7789V2_READ_ID2,ids+1,1);
        // read(ST7789V2_READ_ID3,ids+2,1);

    }

}


