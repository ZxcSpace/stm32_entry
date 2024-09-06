/**
  ******************************************************************************
  * @file    test_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Thu Sep  5 19:09:57 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef TEST_DATA_PARAMS_H
#define TEST_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_TEST_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_test_data_weights_params[1]))
*/

#define AI_TEST_DATA_CONFIG               (NULL)


#define AI_TEST_DATA_ACTIVATIONS_SIZES \
  { 8000, }
#define AI_TEST_DATA_ACTIVATIONS_SIZE     (8000)
#define AI_TEST_DATA_ACTIVATIONS_COUNT    (1)
#define AI_TEST_DATA_ACTIVATION_1_SIZE    (8000)



#define AI_TEST_DATA_WEIGHTS_SIZES \
  { 3084, }
#define AI_TEST_DATA_WEIGHTS_SIZE         (3084)
#define AI_TEST_DATA_WEIGHTS_COUNT        (1)
#define AI_TEST_DATA_WEIGHT_1_SIZE        (3084)



#define AI_TEST_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_test_activations_table[1])

extern ai_handle g_test_activations_table[1 + 2];



#define AI_TEST_DATA_WEIGHTS_TABLE_GET() \
  (&g_test_weights_table[1])

extern ai_handle g_test_weights_table[1 + 2];


#endif    /* TEST_DATA_PARAMS_H */
