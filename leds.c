
#include	"leds.h"

void led12_on( void ){
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
}
void led12_off( void ){
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
}

void led12_toggle(){
	GPIOD->ODR ^= (1<<12);
}
void led13_toggle(){
	GPIOD->ODR ^= (1<<13);
}

void led13_on( void ){
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
}
void led13_off( void ){
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
}void led14_on( void ){
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
}
void led14_off( void ){
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
}
void led14_toggle(){
	GPIOD->ODR ^= (1<<14);
}

void led15_on( void ){
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
}
void led15_off( void ){
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
}
void led15_toggle(){
	GPIOD->ODR ^= (1<<15);
}

