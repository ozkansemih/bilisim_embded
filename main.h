#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f4xx_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f4xx_rng.h"              // Keil::Device:StdPeriph Drivers:RNG
#include "stm32f4xx_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f4xx_syscfg.h"           // Keil::Device:StdPeriph Drivers:SYSCFG
#include "stm32f4xx_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "misc.h"

#include "inits.h"
#include "leds.h"
#include "PCD8544.h"
//#include "delayy.H"
#include "spi_drive.h"

void oyun_baslat();
void oyunu_bitir();
uint16_t Read_ADC(void);

uint32_t get_RNG( int top_lim, int bot_lim );

/*
27 Feb 2021
	5510 pin    F407 pin
		1				PD-8   rst
		2				PA-4    ce
		3				PD-9   dc
		4				PA-7    din  - mosi
		5				PA-5    clk  - sck
		6				3V3     vcc
		7				PD-10   bl
		8				GND     gnd

*/
