#include "zxc_i2c.h"

namespace zxc
{
    ZxcI2c::ZxcI2c(I2C_TypeDef * i2c_x,GPIO_TypeDef * gpio_x,uint32_t scl_pin,uint32_t sda_pin){
        _i2c_x = i2c_x;
        _gpio_x = gpio_x;
        _scl_pin = scl_pin;
        _sda_pin = sda_pin;
    }
    void ZxcI2c::init(){
        if (_i2c_x==I2C1)
        {
            RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        }
        else if(_i2c_x==I2C2){
            RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        }
        
        if (_gpio_x==GPIOA)
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        }
        else if(_gpio_x==GPIOB){
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        }//使能_gpio_x

        _i2c_x->CR1 &= ~I2C_CR1_PE;
        // //最好先清除
        _gpio_x->MODER &= ~((0x3 << (_scl_pin * 2)) | (0x3 << (_sda_pin * 2)));
        _gpio_x->OTYPER &= ~((1 << _scl_pin) | (1 << _sda_pin));
        _gpio_x->OSPEEDR &= ~((0x3 << (_scl_pin * 2)) | (0x3 << (_sda_pin * 2)));
        _gpio_x->PUPDR &= ~((0x3 << (_scl_pin * 2)) | (0x3 << (_sda_pin * 2)));

        _gpio_x->MODER |= ((2 << (_scl_pin * 2)) | (2 << (_sda_pin * 2))); // 设置b6,b7为复用功能10
        _gpio_x->OTYPER |= ((1 << _scl_pin) | (1 << _sda_pin)); // 开漏
        _gpio_x->OSPEEDR |= ((2 << (_scl_pin * 2)) | (2 << (_sda_pin * 2))); // 高速模式
        _gpio_x->PUPDR |= ((0 << (_scl_pin * 2)) | (0 << (_sda_pin * 2))); // 无上拉下拉

        //！！！！！启用复用引脚只能注册一次，如果要出现注册，必须重新配置上面的模式寄存器
        //必须启用复用映射
        //右移三位就是/8，用来确定afr是0还是1
        //&0x07取余8
        _gpio_x->AFR[_scl_pin>>3] |= (4 << ((_scl_pin&0x07) * 4)); // 设置 _gpio_x 为 AF4/i2c

        if (_sda_pin==9&&_i2c_x==I2C2)
        {
            
            GPIO_PinAFConfig(GPIOB, _sda_pin, GPIO_AF9_I2C2);//和下面/上面afr配置等价
        }else{
            _gpio_x->AFR[_sda_pin>>3] |= (4 << ((_sda_pin&0x07) * 4)); // 设置 _gpio_x 为 AF4/i2c
        }
        

        // _i2c_x->CR1 |= I2C_CR1_SWRST;//复位_i2c_x
        _i2c_x->CR1 &= ~I2C_CR1_SMBUS;//使用i2c模式
        _i2c_x->CR2 |= 50;//设置时钟频率为50m，apb1配置的50m时钟
        _i2c_x->CCR &= ~I2C_CCR_FS;//低速模式
        _i2c_x->CCR |= 250;//100k频率的，则需要200k的频率跳变频率(由于包含高低电平)，系统频率为50m，则50m/200k个计数跳变一次50000/200
        _i2c_x->TRISE = 51;
        // 启用 _i2c_x
        _i2c_x->CR1 |= I2C_CR1_PE;

    

    }
    
} // namespace zxc
