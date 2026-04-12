/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(GPIOC, KEY_LED_4_Pin|KEY_LED_5_Pin|RK_HIGH_1_Pin|RK_LOW_4_Pin
                          |RK_LOW_3_Pin|RK_LOW_2_Pin|KEY_LED_1_Pin|KEY_LED_2_Pin
                          |KEY_LED_3_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, DAC_5_10V_Pin|RK_LOW_1_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, MODBUS_TRE_Pin|LED_Pin|RK_HIGH_4_Pin|RK_HIGH_3_Pin
                          |RK_HIGH_2_Pin|LCD_CS_Pin|LCD_DS_Pin|LCD_RES_Pin);

  /**/
  GPIO_InitStruct.Pin = KEY_LED_4_Pin|KEY_LED_5_Pin|RK_HIGH_1_Pin|RK_LOW_4_Pin
                          |RK_LOW_3_Pin|RK_LOW_2_Pin|KEY_LED_1_Pin|KEY_LED_2_Pin
                          |KEY_LED_3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = DAC_5_10V_Pin|RK_LOW_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = ENC_KEY_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(ENC_KEY_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MODBUS_TRE_Pin|LED_Pin|RK_HIGH_4_Pin|RK_HIGH_3_Pin
                          |RK_HIGH_2_Pin|LCD_CS_Pin|LCD_DS_Pin|LCD_RES_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BOOT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(BOOT_GPIO_Port, &GPIO_InitStruct);
  

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE2);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTC, LL_GPIO_AF_EXTI_LINE4);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTC, LL_GPIO_AF_EXTI_LINE5);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE0);

  /**/
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE1);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_2;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_4;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_5;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinMode(LINE_Z_GPIO_Port, LINE_Z_Pin, LL_GPIO_MODE_FLOATING);

  /**/
  LL_GPIO_SetPinMode(KEY1_GPIO_Port, KEY1_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(KEY2_GPIO_Port, KEY2_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(KEY3_GPIO_Port, KEY3_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(KEY4_GPIO_Port, KEY4_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinPull(KEY1_GPIO_Port, KEY1_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinPull(KEY2_GPIO_Port, KEY2_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinPull(KEY3_GPIO_Port, KEY3_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinPull(KEY4_GPIO_Port, KEY4_Pin, LL_GPIO_PULL_UP);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
  NVIC_EnableIRQ(EXTI0_IRQn);
  NVIC_SetPriority(EXTI1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
  NVIC_EnableIRQ(EXTI1_IRQn);
  NVIC_SetPriority(EXTI2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
  NVIC_EnableIRQ(EXTI2_IRQn);
  NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
  NVIC_EnableIRQ(EXTI4_IRQn);
  NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
  NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
