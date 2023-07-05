
#ifndef LEDS_H
#define  LEDS_H


#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "inits.h"               

void led12_on( void );
void led12_off( void );

void led13_on( void );
void led13_off( void );

void led14_on( void );
void led14_off( void );

void led15_on( void );
void led15_off( void );


void led12_toggle( void );
void led13_toggle( void );
void led14_toggle( void );
void led15_toggle( void );


#endif
