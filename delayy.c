
#include "stdint.h"
#include "delayy.h"

// uint32_t msTicks;

void delayms(int ms){
  uint32_t currTick=0;
	currTick = msTicks;
	while((msTicks - currTick)< ms){
	
	}
}

void SysTick_Handler(){
	msTicks++;
	
}
