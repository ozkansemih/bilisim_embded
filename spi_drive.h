
#ifndef  SPI_DRIVE_
#define SPI_DRIVE_

#include "stm32f4xx_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "delayy.h"            

#define SPI_PORT GPIOB
#define MOSI_PIN GPIO_Pin_15
#define MISO_PIN GPIO_Pin_14
#define SCK_PIN  GPIO_Pin_13
#define CS_PIN    GPIO_Pin_12

void spi_send( SPI_TypeDef* spi, char data);
void spi1_send( SPI_TypeDef* spi, char data);
void spi1_send_PRV( SPI_TypeDef* spi, char data);

#endif
