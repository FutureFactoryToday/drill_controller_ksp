/**
 ****************************************************************************************
 *
 * \file SSD1322_HW_Driver.c
 *
 * \brief Hardware dependent functions for SSD1322 OLED display.
 *
 * This file contains functions that rely on hardware of used MCU. In this example functions
 * are filled with STM32F411RE hardware implementation. To use this library on any other MCU
 * you just have to provide its hardware implementations of functions from this file and higher
 * level functions should work without modification.
 *
 * Copyright (C) 2020 Wojciech Klimek
 * MIT license:
 * https://github.com/wjklimek1/SSD1322_OLED_library
 *
 ****************************************************************************************
 */

//#include "../SSD1322_OLED_lib/SSD1322_HW_Driver.h"
#include "SSD1322_HW_Driver.h"
void SSD1322_HW_drive_Init(void){
	LL_GPIO_ResetOutputPin(SSD1322_HW_CS_Port, SSD1322_HW_CS_Pin);
	LL_GPIO_ResetOutputPin(SSD1322_HW_DC_Port, SSD1322_HW_DC_Pin);
	LL_GPIO_ResetOutputPin(SSD1322_HW_Res_Port, SSD1322_HW_Res_Pin);
	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = SSD1322_HW_CS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(SSD1322_HW_CS_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SSD1322_HW_DC_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(SSD1322_HW_DC_Port, &GPIO_InitStruct);
		
	GPIO_InitStruct.Pin = SSD1322_HW_Res_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(SSD1322_HW_Res_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SSD1322_HW_SCK_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(SSD1322_HW_SCK_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SSD1322_HW_MOSI_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(SSD1322_HW_MOSI_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SSD1322_HW_MISO_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(SSD1322_HW_MISO_Port, &GPIO_InitStruct);
	
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 10;
  LL_SPI_Init(SSD1332_HW_SPI, &SPI_InitStruct);
	
	LL_GPIO_SetOutputPin(SSD1322_HW_CS_Port, SSD1322_HW_CS_Pin);
	
	LL_SPI_Enable(SSD1332_HW_SPI);
}
//====================== CS pin low ========================//
/**
 *  @brief Drives CS (Chip Select) pin of SPI interface low.
 *
 *  CS pin may be also signed as "SS" or "NSS"
 */
void SSD1322_HW_drive_CS_low()
{
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1);
	//HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, 0);
}

//====================== CS pin high ========================//
/**
 *  @brief Drives CS (Chip Select) pin of SPI interface high.
 *
 *  CS pin may be also signed as "SS" or "NSS"
 */
void SSD1322_HW_drive_CS_high()
{
    LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_1);
	//HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, 1);
}

//====================== DC pin low ========================//
/**
 *  @brief Drives DC (Data/Command) pin of OLED driver low.
 *
 *  High state is for data and low state is for command.
 */
void SSD1322_HW_drive_DC_low()
{
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_5);
	//HAL_GPIO_WritePin(SPI5_DC_GPIO_Port, SPI5_DC_Pin, 0);
}

//====================== DC pin high ========================//
/**
 *  @brief Drives DC (Data/Command) pin of of OLED driver high.
 *
 *  High state is for data and low state is for command.
 */
void SSD1322_HW_drive_DC_high()
{
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_5);
	//HAL_GPIO_WritePin(SPI5_DC_GPIO_Port, SPI5_DC_Pin, 1);
}

//====================== RESET pin low ========================//
/**
 *  @brief Drives RESET pin of of OLED driver low.
 *
 *  Logic low on RESET resets OLED driver.
 */
void SSD1322_HW_drive_RESET_low()
{
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_2);
	//HAL_GPIO_WritePin(SPI5_RESET_GPIO_Port, SPI5_RESET_Pin, 0);
}

//====================== RESET pin high ========================//
/**
 *  @brief Drives RESET pin of of OLED driver high.
 *
 *  Logic low on RESET resets OLED driver.
 */
void SSD1322_HW_drive_RESET_high()
{
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
	//HAL_GPIO_WritePin(SPI5_RESET_GPIO_Port, SPI5_RESET_Pin, 1);
}

//====================== Send single SPI byte ========================//
/**
 *  @brief Transmits single byte through SPI interface.
 *
 *  @param[in] byte_to_transmit byte that will be transmitted through SPI interface
 */
void SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit)
{
	
  LL_SPI_TransmitData8(SPI1, byte_to_transmit);
	while (LL_SPI_IsActiveFlag_BSY(SPI1)){};
	//HAL_SPI_Transmit(&hspi5, &byte_to_transmit, 1, 10);
}

//====================== Send array of SPI bytes ========================//
/**
 *  @brief Transmits array of bytes through SPI interface.
 *
 *  @param[in] array_to_transmit array of bytes that will be transmitted through SPI interface
 *  @param[in] array_size amount of bytes to transmit
 */
void SSD1322_HW_SPI_send_array(uint8_t *array_to_transmit, uint32_t array_size)
{
    for(uint32_t i = 0; i < array_size; i++)
    {
        SSD1322_HW_SPI_send_byte(array_to_transmit[i]);
    }
	//HAL_SPI_Transmit(&hspi5, array_to_transmit, array_size, 100);
}

//====================== Milliseconds delay ========================//
/**
 *  @brief Wait for x milliseconds.
 *
 *  NOTE: This function is only used in initialization sequence to pull reset down and high
 *  and later to wait for Vdd stabilization. It takes time ONLY on startup (around 200ms)
 *  and is NOT USED during normal operation.
 *
 *  @param[in] milliseconds time to wait
 */
void SSD1322_HW_msDelay(uint32_t milliseconds)
{
	LL_mDelay(milliseconds);
}
