#ifndef __ZXC_ST7789_REG_H__
#define __ZXC_ST7789_REG_H__


#define ST7789V2_NOP                          0x00U
#define ST7789V2_SW_RESET                     0x01U
#define ST7789V2_READ_ID                      0x04U
#define ST7789V2_READ_STATUS                  0x09U
#define ST7789V2_READ_POWER_MODE              0x0AU
#define ST7789V2_READ_MADCTL                  0x0BU
#define ST7789V2_READ_PIXEL_FORMAT            0x0CU
#define ST7789V2_READ_IMAGE_MODE              0x0DU
#define ST7789V2_READ_SIGNAL_MODE             0x0EU
#define ST7789V2_READ_SELF_DIAGNOSTIC         0x0FU
#define ST7789V2_SLEEP_IN                     0x10U
#define ST7789V2_SLEEP_OUT                    0x11U
#define ST7789V2_PARTIAL_DISPLAY_OFF           0x12U
#define ST7789V2_NORMAL_DISPLAY_ON           0x13U
#define ST7789V2_DISPLAY_INVERSION_OFF        0x20U
#define ST7789V2_DISPLAY_INVERSION_ON         0x21U
#define ST7789V2_GAMMA_SET                    0x26U
#define ST7789V2_DISPLAY_OFF                  0x28U
#define ST7789V2_DISPLAY_ON                   0x29U
#define ST7789V2_CASET                        0x2AU
#define ST7789V2_RASET                        0x2BU
#define ST7789V2_WRITE_RAM                    0x2CU
#define ST7789V2_READ_RAM                     0x2EU
#define ST7789V2_VSCRDEF                      0x33U 
#define ST7789V2_TE_LINE_OFF                  0x34U
#define ST7789V2_TE_LINE_ON                   0x35U
#define ST7789V2_MADCTL                       0x36U
#define ST7789V2_VSCSAD                       0x37U 
#define ST7789V2_IDLE_MODE_OFF                0x38U
#define ST7789V2_IDLE_MODE_ON                 0x39U
#define ST7789V2_COLOR_MODE                   0x3AU
#define ST7789V2_WRITE_RAM_CONTINUE           0x3CU
#define ST7789V2_READ_RAM_CONTINUE            0x3EU
#define ST7789V2_SET_SCANLINE                 0x44U
#define ST7789V2_GET_SCANLINE                 0x45U
#define ST7789V2_SET_BRIGHTNESS               0x51U
#define ST7789V2_GET_BRIGHTNESS               0x52U
#define ST7789V2_WRITE_CTRL_DISPLAY           0x53U
#define ST7789V2_READ_CTRL_DISPLAY            0x54U
#define ST7789V2_WRITE_CACE                   0x55U
#define ST7789V2_READ_CABC                    0x56U
#define ST7789V2_SET_CABC_MIN_BRIGHTNESS      0x5EU
#define ST7789V2_GET_CABC_MIN_BRIGHTNESS      0x5FU
#define ST7789V2_READ_ABCSDR                  0x68U 
#define ST7789V2_READ_ID1                     0xDAU
#define ST7789V2_READ_ID2                     0xDBU
#define ST7789V2_READ_ID3                     0xDCU
#define ST7789V2_RAM_CTRL                     0xB0U
#define ST7789V2_RGB_INTERFACE_CTRL           0xB1U
#define ST7789V2_PORCH_CTRL                   0xB2U
#define ST7789V2_FRAME_RATE_CTRL1             0xB3U
#define ST7789V2_PARTIAL_CTRL                 0xB5U
#define ST7789V2_GATE_CTRL                    0xB7U
#define ST7789V2_GATE_TIMING_ADJUSTMENT       0xB8U
#define ST7789V2_DIGITAL_GAMMA_ENABLE         0xBAU
#define ST7789V2_VCOM_SET                     0xBBU
#define ST7789V2_PWR_SAVING_MODE              0xBCU
#define ST7789V2_DISPLAY_OFF_PWR_SAVE         0xBDU
#define ST7789V2_LCM_CTRL                     0xC0U
#define ST7789V2_ID_CODE_SETTING              0xC1U
#define ST7789V2_VDV_VRH_EN                   0xC2U
#define ST7789V2_VRH_SET                      0xC3U
#define ST7789V2_VDV_SET                      0xC4U
#define ST7789V2_VCOMH_OFFSET_SET             0xC5U
#define ST7789V2_FR_CTRL                      0xC6U
#define ST7789V2_CABC_CTRL                    0xC7U
#define ST7789V2_REG_VALUE_SELECTION1         0xC8U
#define ST7789V2_REG_VALUE_SELECTION2         0xCAU
#define ST7789V2_PWM_FREQ_SELECTION           0xCCU
#define ST7789V2_POWER_CTRL                   0xD0U
#define ST7789V2_EN_VAP_VAN_SIGNAL_OUTPUT     0xD2U
#define ST7789V2_COMMAND2_ENABLE              0xDFU
#define ST7789V2_PV_GAMMA_CTRL                0xE0U 
#define ST7789V2_NV_GAMMA_CTRL                0xE1U 
#define ST7789V2_GAMMA_RED_TABLE              0xE2U
#define ST7789V2_GAMMA_BLUE_TABLE             0xE3U
#define ST7789V2_GATE_CTRL2                   0xE4U
#define ST7789V2_SPI2_ENABLE                  0xE7U
#define ST7789V2_PWR_CTRL2                    0xE8U
#define ST7789V2_EQUALIZE_TIME_CTRL           0xE9U
#define ST7789V2_PROGRAM_MODE_CTRL            0xECU
#define ST7789V2_PROGRAM_MODE_ENABLE          0xFAU
#define ST7789V2_NVM_SETTING                  0xFCU
#define ST7789V2_PROGRAM_ACTION               0xFEU
#endif