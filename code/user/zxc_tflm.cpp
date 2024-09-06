#include "zxc_tflm.h"

namespace zxc
{
    void softmax(float* input, float* output, int n) {
        float maxInput = input[0];
        float sum = 0.0;

        // 找到输入中的最大值
        for (int i = 1; i < n; i++) {
            if (input[i] > maxInput) {
                maxInput = input[i];
            }
        }

        // 计算所有输入的指数和，减去最大值避免溢出
        for (int i = 0; i < n; i++) {
            output[i] = exp(input[i] - maxInput); // 数值稳定性处理
            sum += output[i];                     // 计算指数和
        }

        // 将每个指数除以总和
        for (int i = 0; i < n; i++) {
            output[i] /= sum;                     // 归一化处理，转换为概率分布
        }
    }

    ai_u8 ZxcModel::activations[AI_TEST_DATA_ACTIVATIONS_SIZE];
    ai_float ZxcModel::in_data[AI_TEST_IN_1_SIZE];
    ai_float ZxcModel::out_data[AI_TEST_OUT_1_SIZE];
    ai_float ZxcModel::softmax_tmp[AI_TEST_OUT_1_SIZE];

    ai_buffer* ZxcModel::ai_input;
    ai_buffer* ZxcModel::ai_output;

    ai_handle ZxcModel::network = AI_HANDLE_NULL;

    bool ZxcModel::init(){

        ai_error err;
        ai_network_report report;
        const ai_handle acts[] = { activations };
        err = ai_test_create_and_init(&network, acts, NULL);
        if (err.type != AI_ERROR_NONE) {
            DEBUG_INFO("cc error");
            return false;
        }

        if (ai_test_get_report(network, &report) != true) {
            DEBUG_INFO("report error");
            return false;
        }

        ai_input = ai_test_inputs_get(network, NULL);
        ai_output = ai_test_outputs_get(network, NULL);

        ai_input[0].data = AI_HANDLE_PTR(in_data);
        ai_output[0].data = AI_HANDLE_PTR(out_data);

        

        return true;
    }

    u8 ZxcModel::inturrupt(){
        u8 index = 0;
        // srand(3);
        // for (int i = 0; i < AI_TEST_IN_1_SIZE; i++) {
        //     in_data[i] = rand() % 0xFFFF;
        // }
        // ai_input[0].data = AI_HANDLE_PTR(input);
        ai_i32 n_batch;
        n_batch = ai_test_run(network, &ai_input[0], &ai_output[0]);
        if (n_batch != 1) {
            DEBUG_INFO("error");
        }
        else{
            // DEBUG_INFO("okkk");

            softmax(out_data,softmax_tmp,AI_TEST_OUT_1_SIZE);
            
            float d_tmp = 0;
            for (u8 i = 0; i < AI_TEST_OUT_1_SIZE; i++)
            {
                if (softmax_tmp[i]>d_tmp)
                {
                    d_tmp = softmax_tmp[i];
                    index = i;
                }
                
            }
        
        }
        return index;
    }

    void ZxcModel::set_input(u16* input, int len){

        if (len>AI_TEST_IN_1_SIZE)
        {
            DEBUG_INFO("error input too long");
            return;
        }
        for (int i = len; i < (AI_TEST_IN_1_SIZE); i++)
        {
            in_data[i-len] = in_data[i];
        }
        
        for (int i = 0; i < len; i++)
        {
            // DEBUG_INFO("f:%f",((float)input[i] - 2074.241764305899)/330.3760492693207);
            in_data[AI_TEST_IN_1_SIZE - len + i] = (((float)input[i] - 2074.241764305899)/330.3760492693207);
        }
        
        
    }
    
} // namespace zxc
