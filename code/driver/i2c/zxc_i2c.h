#ifndef __ZXC_I2C_H__
#define __ZXC_I2C_H__

#include "stm32f4xx.h"
#include "zxc_utils.h"
#include "zxc_debug.h"
namespace zxc
{
    class ZxcI2c{

    private:
        I2C_TypeDef * _i2c_x;
        GPIO_TypeDef * _gpio_x;
        uint32_t _scl_pin;
        uint32_t _sda_pin;
        
    public:
        ZxcI2c(I2C_TypeDef * i2c_x,GPIO_TypeDef * gpio_x,uint32_t scl_pin,uint32_t sda_pin);
        void init();
        bool start();
        void stop();
        void ack();
        void unack();
        bool send_byte(u8 byte);
        bool send_addr(u8 addr);
        bool read_byte(u8& bt);
    };

    //开始信号
    inline bool ZxcI2c::start(){

        _i2c_x->CR1 |= I2C_CR1_START;

        uint16_t timeout = 50000;
        while (((_i2c_x->SR1 & I2C_SR1_SB) == 0) && timeout)
        {
            timeout--;
        }

        return timeout ? true : false;


    }
    inline bool ZxcI2c::send_addr(u8 addr){
        uint16_t timeout = 50000;

        _i2c_x->DR = addr;

        while (((_i2c_x->SR1 & I2C_SR1_ADDR) == 0) && timeout)
        {
            timeout--;
        }

        if (timeout)
        {
            _i2c_x->SR2;
        }

        return timeout ? true : false;

    }

    inline bool ZxcI2c::send_byte(u8 byte){

        uint16_t timeout = 50000;
        //等待空闲
        while (((_i2c_x->SR1 & I2C_SR1_TXE) == 0) && timeout)
        {
            timeout--;
        }
        // 把要发送的数据写入到数据寄存器
        _i2c_x->DR = byte;

        timeout = 50000;

        while (((_i2c_x->SR1 & I2C_SR1_BTF) == 0) && timeout)
        {
            timeout--;
        }
        return timeout ? true : false;
    }

    inline bool ZxcI2c::read_byte(u8& bt){

        uint16_t timeout = 50000;

        //等待数据寄存器非空，也就是来数据了
        while (((_i2c_x->SR1 & I2C_SR1_RXNE) == 0) && timeout)
        {
            timeout--;
        }
        // 把数据寄存器的值返回
        bt = _i2c_x->DR;
        return timeout ? true : false;
    }
    //结束信号
    inline void ZxcI2c::stop(){

        _i2c_x->CR1 |= I2C_CR1_STOP;
    }

    inline void ZxcI2c::ack(){
        _i2c_x->CR1 |= I2C_CR1_ACK;
    }

    inline void ZxcI2c::unack(){
        _i2c_x->CR1 &= ~I2C_CR1_ACK;
    }

} // namespace zxc

#endif