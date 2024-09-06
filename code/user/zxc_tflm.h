#ifndef __ZXC_TFLM_H__
#define __ZXC_TFLM_H__
#include "math.h"
#include "test.h"
#include "test_data.h"
#include "ai_platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "zxc_debug.h"

namespace zxc
{
   
    class ZxcModel{

    private:
        static ai_u8 activations[AI_TEST_DATA_ACTIVATIONS_SIZE];
        
        static ai_float out_data[AI_TEST_OUT_1_SIZE];
        static ai_float softmax_tmp[AI_TEST_OUT_1_SIZE];
        static ai_buffer *ai_input;
        static ai_buffer *ai_output;

        static ai_handle network;
    public:

        static ai_float in_data[AI_TEST_IN_1_SIZE];
        static bool init();
        static u8 inturrupt();
        static void set_input(u16* input, int len);

    };
} // namespace zxc

#endif