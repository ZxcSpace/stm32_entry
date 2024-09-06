#include "zxc_utils.h"
#include "zxc_debug.h"

namespace zxc
{
    // template<typename T>
    ZxcCircleBuffer::ZxcCircleBuffer():buffer{0},start_ptr(0),end_ptr(0),data_len(0),max_len(MAX30102_BUFFER_LEN){

        
    }
    // template<typename T>
    ZxcCircleBuffer::~ZxcCircleBuffer(){

    }
    // template<typename T>
    void ZxcCircleBuffer::append(const uint32_t data,bool discard_full){

        if ((data_len==max_len))
        {
            if (discard_full)
            {
                return;
            }
            else{
                buffer[end_ptr] = data;
                end_ptr = (end_ptr+1)%max_len;
                start_ptr = (start_ptr+1)%max_len;
            }
             
        }
        else{
            // DEBUG_INFO("data_len:%d",data_len);
            buffer[end_ptr] = data;
            end_ptr = (end_ptr+1)%max_len;
            
            data_len++;
        }
        
        

    }
    // template<typename T>
    uint32_t ZxcCircleBuffer::take(){
        uint32_t data = buffer[start_ptr];
        start_ptr = (start_ptr+1)%max_len;
        data_len--;
        return data;
    }

    // template<typename T>
    void ZxcCircleBuffer::delete_range(u16 dl){
        u16 l = dl > data_len ? data_len : dl;
        start_ptr = (start_ptr + l) % max_len;
        data_len -= l;
        
    }

    // template<typename T>
    const uint32_t& ZxcCircleBuffer::operator[](const uint32_t index) const{

        // DEBUG_INFO("index2:%d",index);

        uint32_t idx = (start_ptr+(index>(data_len - 1) ? (data_len - 1) : index))%max_len;
        
        return buffer[idx];
    }



    const double ZxcSecondHighFilter::b[3] = {0.95654323,-1.91308645,0.95654323};
    const double ZxcSecondHighFilter::a[3] = {1.0,-1.91119707,0.91497583};
    ZxcSecondHighFilter::ZxcSecondHighFilter():x{0},y{0},x_r{0},y_r{0}{

        

    }
    //会修改原数组
    void ZxcSecondHighFilter::filter(double* inputs,u16 len){

        zxc_high_filter_forward(inputs,len);
        zxc_high_filter_backward(inputs,len);
    }
    


    
} // namespace zxc

