/**
 ****************************************************************************************
 *
 * \file SSD1322_HW_Driver.h
 *
 * \brief Hardware dependent functions declarations for SSD1322 OLED display.
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
#ifndef SSD1322_HW_DRIVER_H
#define SSD1322_HW_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include <math.h>

#define SSD1322_HW_CS_Port LCD_CS_GPIO_Port
#define SSD1322_HW_CS_Pin LCD_CS_Pin

#define SSD1322_HW_DC_Port LCD_DS_GPIO_Port
#define SSD1322_HW_DC_Pin	LCD_DS_Pin

#define SSD1322_HW_Res_Port LCD_RES_GPIO_Port
#define SSD1322_HW_Res_Pin	LCD_RES_Pin

#define SSD1322_HW_MISO_Port GPIOA
#define SSD1322_HW_MISO_Pin	LL_GPIO_PIN_6

#define SSD1322_HW_MOSI_Port GPIOB
#define SSD1322_HW_MOSI_Pin	LL_GPIO_PIN_5

#define SSD1322_HW_SCK_Port GPIOB
#define SSD1322_HW_SCK_Pin	LL_GPIO_PIN_3

#define SSD1332_HW_SPI SPI1

void SSD1322_HW_drive_CS_low();
void SSD1322_HW_drive_CS_high();
void SSD1322_HW_drive_DC_low();
void SSD1322_HW_drive_DC_high();
void SSD1322_HW_drive_RESET_low();
void SSD1322_HW_drive_RESET_high();
void SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit);
void SSD1322_HW_SPI_send_array(uint8_t *array_to_transmit, uint32_t array_size);
void SSD1322_HW_msDelay(uint32_t milliseconds);
void SSD1322_HW_drive_Init(void);
#ifdef __cplusplus
}
#endif

#endif /* SSD1322_HW_DRIVER_H */
