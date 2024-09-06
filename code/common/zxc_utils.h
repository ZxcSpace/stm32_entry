#ifndef __ZXC_UTILS_H__
#define __ZXC_UTILS_H__
#define  FILTER_NUM 2
#include "stm32f4xx.h"
#include "zxc_conf.h"
namespace zxc
{
    // template<typename T>
    class ZxcCircleBuffer{

        private:
        //这个不能使用new，会产生内存泄露
        uint32_t buffer[MAX30102_BUFFER_LEN];
        const u16 max_len;
        // u16 data_len;
        // u16 start_ptr;
        // u16 end_ptr;
        public:
        u16 start_ptr;
        u16 end_ptr;
        u16 data_len;
        ZxcCircleBuffer();
        ~ZxcCircleBuffer();
        //向环形缓冲区中添加数据，bool值：true丢弃溢出值，false：覆盖
        void append(const uint32_t data,bool discard_full=true);
        uint32_t take();
        void delete_range(u16 data_len);
        const uint32_t& operator[](const uint32_t index) const;

    };

    class ZxcKalmanFilter {

    private:
        double Q;  // 过程噪声协方差
        double R;  // 测量噪声协方差
        double P;  // 误差协方差
        double X;  // 状态估计
        // 预测步骤
        void predict() {
            // X' = X (这里假设状态转移矩阵为 1，即状态不变)
            P = P + Q;  // 更新误差协方差
        }

        // 更新步骤
        void update(double measurement) {
            // 计算卡尔曼增益
            double K = P / (P + R);
            
            // 更新估计值
            X = X + K * (measurement - X);
            
            // 更新误差协方差
            P = (1 - K) * P;
        }

    public:
        ZxcKalmanFilter(double processNoise, double measurementNoise, double estimatedError, double initialEstimate)
            : Q(processNoise), R(measurementNoise), P(estimatedError), X(initialEstimate) {}

        double filter(double measurement){
            predict();
            update(measurement);
            return X;
        }

    
    };

    class ZxcSecondHighFilter{

        private:

        static const double b[3];
        static const double a[3];
        double x[FILTER_NUM+1];
        double y[FILTER_NUM+1];
        double x_r[FILTER_NUM+1];
        double y_r[FILTER_NUM+1];

        //一个数据的高通滤波
        double zxc_high_filter_one(double input){
            //移位，添加新数据
            for (u16 i = FILTER_NUM; i > 0; i--)
            {
                x[i] = x[i-1];
                y[i] = y[i-1];
            }
            x[0] = input;
            y[0] = b[0] * x[0];

            for (u16 i = 1; i < FILTER_NUM+1; i++)
            {
                y[0] += (b[i] * x[i] - a[i] * y[i]);
            }

            return y[0];
            

        }

        //对一组数据前向滤波
        //注意为节省空间，会修改原数组
        void zxc_high_filter_forward(double* inputs,u16 len){

            for (u16 i = 0; i < len; i++)
            {
                inputs[i] = zxc_high_filter_one(inputs[i]);
            }
            
        }
        //反向滤波。会修改原数组
        void zxc_high_filter_backward(double* inputs,u16 len){

            for (u16 i = len-1; i >= 0; i--)
            {
                inputs[i] = zxc_high_filter_one(inputs[i]);
            }
        }
        public:
        ZxcSecondHighFilter();

        void filter(double* inputs,u16 len);

    };


} // namespace zxc

#endif