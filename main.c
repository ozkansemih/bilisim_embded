#include "main.h"                  // Device header
		int asd =0;
		char arr[5] ={};

		int rnd_asd =0;
		char rnd_arr[3] ={};
		char tahmin_str[2] ={0,0};
		char hak_cnt[2] = {};
		char hakk = 5;
		static int desee =0;
		int tahmin =0;	
		int tahmin_digit =0;
		int basamak =10;
		int basladi =0;
		int kalan_Hak = 5;
		int x_idx=0;
			
		int yakinlik =0 ;
		int flag = 1;
		uint32_t prev_tick =0;

		uint32_t msTicks;

int main(){
	
		inits();
		init_SPI1();

		GPIO_InitTypeDef GPIO_InitStructure;
		ADC_InitTypeDef ADC_InitStructure;
		ADC_CommonInitTypeDef ADC_CommonInitStructure;
		GPIO_InitTypeDef gp;
		USART_InitTypeDef usa;
		EXTI_InitTypeDef ext;
		NVIC_InitTypeDef nvi;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_TIM10 , ENABLE );
	
		gp.GPIO_Mode = GPIO_Mode_AF ;
		gp.GPIO_OType = GPIO_OType_PP ;
		gp.GPIO_PuPd = GPIO_PuPd_UP ;
		gp.GPIO_Pin = GPIO_Pin_8 ;
		gp.GPIO_Speed = GPIO_Speed_100MHz ;
		GPIO_Init ( GPIOB , &gp );
		GPIO_PinAFConfig ( GPIOB , GPIO_PinSource8 , GPIO_AF_TIM10 );

		TIM_TimeBaseInitTypeDef timb;
		TIM_OCInitTypeDef timoc;

		timb.TIM_ClockDivision = 0;
		timb.TIM_CounterMode = TIM_CounterMode_Up ;
		timb.TIM_Period = 100;
		timb.TIM_Prescaler = 600 ;
		TIM_TimeBaseInit ( TIM10 , &timb );

		timoc.TIM_OCMode = TIM_OCMode_PWM1 ;
		timoc.TIM_OCNPolarity = TIM_OCPolarity_High ;
		timoc.TIM_OutputState = ENABLE ;
		timoc.TIM_Pulse = 29;
		TIM_OC1Init ( TIM10 , & timoc );

		TIM_OC1PreloadConfig ( TIM10, TIM_OCPreload_Enable );
		TIM_ARRPreloadConfig ( TIM10 , ENABLE );

	//	TIM_Cmd ( TIM10 , ENABLE );

		gp.GPIO_Pin=GPIO_Pin_0;
		gp.GPIO_Mode=GPIO_Mode_IN;
		gp.GPIO_OType=GPIO_OType_PP;
		gp.GPIO_PuPd=GPIO_PuPd_DOWN;
		gp.GPIO_Speed=GPIO_Speed_100MHz;
		GPIO_Init(GPIOA,&gp);

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);

		ext.EXTI_Line=EXTI_Line0;
		ext.EXTI_LineCmd=ENABLE;
		ext.EXTI_Mode=EXTI_Mode_Interrupt;
		ext.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Init(&ext);
	
		nvi.NVIC_IRQChannel=EXTI0_IRQn;
		nvi.NVIC_IRQChannelCmd=ENABLE;
		nvi.NVIC_IRQChannelPreemptionPriority=0x00;
		nvi.NVIC_IRQChannelSubPriority=0x00;
		NVIC_Init(&nvi);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;  // potansiyometrenin data pini A1 pinine baglanacak
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, & GPIO_InitStructure);

		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4; // 4/8/16.. vs olabilir kristalin 4 de 1 i seçtik
		ADC_CommonInit(& ADC_CommonInitStructure);
 
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;	//8bitlik okuma islemi yapilacak
		ADC_Init(ADC1, & ADC_InitStructure);

		ADC_Cmd(ADC1, ENABLE);

		init_Screen();
		spi1_send( SPI1,0x20); // use basic instruction set
		spi1_send( SPI1,0x0C); // Display control, normal mode
		spi1_send( SPI1,0x21); // Function set
		spi1_send( SPI1,0xC6);  // voltaj ayari
		spi1_send( SPI1,0x20); // use basic instruction set
		spi1_send( SPI1,0x0C); // Display control, normal mode
		GPIO_SetBits( PCD8544_PORT, PCD8544_BL_PIN); // GPIOD GPIO_Pin_14
		clear_Screen();
		int i=0;
		int k=0;
		put_str_wAdress( 0,0," SAYI TAHMIN     OYUNU :)\0");
		put_str_wAdress( 0,2, "baslamak icin butona basiniz");
	
		//hak_cnt[0] = kalan_Hak+ '0';
//		put_str_wAdress ( 2*6,5, "hak kaldi");
	//	put_char_wAdress(0,5,hakk+'0');

		rnd_asd = get_RNG(100,0);

		rnd_arr[0] = rnd_asd/100 %10+ '0';
		rnd_arr[1] = rnd_asd/10 %10+ '0';
		rnd_arr[2] = rnd_asd/1 %10+ '0';

		put_str_wAdress (3*6 ,4,rnd_arr);

	while( 1  ){
		delayms(10);
		asd= Read_ADC();
		
		if ( basladi == 1){

			if ( asd < 410 ){
				put_char_wAdress ( 12*6,4,'0');
				tahmin_digit =0;
			}
			else if ( asd < 820 ){
				put_char_wAdress ( 12*6,4,'1');
				tahmin_digit =1;
			}
			else if ( asd < 1230 ){
				put_char_wAdress ( 12*6,4,'2');
				tahmin_digit =2;
			}
			else if ( asd < 1640 ){
				put_char_wAdress ( 12*6,4,'3');
				tahmin_digit =3;
			}
			else if ( asd < 2050 ){
				put_char_wAdress ( 12*6,4,'4');
				tahmin_digit =4;
			}
			else if ( asd < 2460 ){
				put_char_wAdress ( 12*6,4,'5');
				tahmin_digit =5;
			}
			else if ( asd < 2870 ){
				put_char_wAdress ( 12*6,4,'6');
				tahmin_digit =6;
			}
			else if ( asd < 3280 ){
				put_char_wAdress ( 12*6,4,'7');
				tahmin_digit =7;
			}
			else if ( asd < 3690 ){
				put_char_wAdress ( 12*6,4,'8');
				tahmin_digit =8;
			}
			else if ( asd < 4100 ){
				put_char_wAdress ( 12*6,4,'9');
				tahmin_digit =9;
			}
			
			if ( yakinlik == 0){			
				TIM_Cmd ( TIM10 , DISABLE );
			}
			else if( yakinlik == 1){
		
			//	TIM_Cmd ( TIM10 , ENABLE );
				delayms( 1);
				if ( flag == 1 ) {
					TIM10->ARR -=1 ;
				} 
				else if ( flag == 0 ) {
					TIM10->ARR+= 1;
				}
				if ( TIM10->ARR == 50 | TIM10->ARR == 150) {
					flag ^= 0x01;
				}
			}
			else if( yakinlik == 2){
	//			TIM_Cmd ( TIM10 , ENABLE );
				delayms( 1);
				if ( flag == 1 ) {
					TIM10->ARR -=1 ;
				} 
				else if ( flag == 0 ) {
					TIM10->ARR+= 1;
				}
				if ( TIM10->ARR == 200 | TIM10->ARR == 300) {
					flag ^= 0x01;
				}
			}
			
		}
	}

}
void oyun_baslat(){

	hakk= 5;
	x_idx =0;
	put_str_wAdress( 0*6,2,"  tahmininiz                ");
	put_str_wAdress ( 0,4, "              ");
	put_str_wAdress ( 2*6,5, "hak kaldi");
	put_char_wAdress(0,5,hakk+'0');
	basladi = 1;
	basamak = 10;
}

void oyunu_bitir(){
			if ( yakinlik != 3)

	put_str_wAdress (5*6 ,4,rnd_arr);

	basladi = 0;
	int i = 0;			
		int count_val = 24000000;
		if ( yakinlik == 3)
			count_val /=12;
	TIM10->ARR=100;	
	while ( i++ < count_val){
		if ( yakinlik == 3){
			
					if ( flag == 1 ) {
						TIM10->ARR -=1 ;
					} 
					else if ( flag == 0 ) {
						TIM10->ARR+= 1;
					}
					if ( TIM10->ARR == 80 | TIM10->ARR == 120) {
						flag ^= 0x01;
					}
		}

	}
	put_str_wAdress( 0*6,2," oyun bitti                       ");
	put_str_wAdress( 0,3, "baslamak icin butona basiniz");
	put_str_wAdress( 0,5, "              ");
	TIM_Cmd ( TIM10 , DISABLE );
				rnd_asd = get_RNG(100,0);

		rnd_arr[0] = rnd_asd/100 %10+ '0';
		rnd_arr[1] = rnd_asd/10 %10+ '0';
		rnd_arr[2] = rnd_asd/1 %10+ '0';
}

void EXTI0_IRQHandler(void){
	
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET){
		
		if (( msTicks -prev_tick) >200){
					desee++;

			if ( basladi == 0){
				oyun_baslat();

			}
		else if ( basladi == 1 ){

			if ( basamak == 10){
				
				tahmin += basamak * tahmin_digit;
				basamak =1;
						put_char_wAdress ( x_idx,3,tahmin_digit+'0');
				x_idx +=6;
			}
			else if ( basamak == 1){
				
				tahmin += tahmin_digit;
				tahmin_str[0] = tahmin/10 + '0';
				tahmin_str[1] = tahmin%10 + '0';

				put_char_wAdress ( x_idx,3,tahmin_digit+'0');
				x_idx +=6;

				if ( tahmin != rnd_asd){
					//kalan_Hak--;	
					hakk--;				
			//		hak_cnt[0] = kalan_Hak +'0';
				//	put_str_wAdress ( 0*6,5,hak_cnt);
					put_char_wAdress ( 0*6,5,hakk+'0');
					basamak = 10;
					tahmin_str[0] = 0;
					tahmin_str[1] = 0;
			//put_str_wAdress( 0*6,3,"    ");
					put_char_wAdress ( x_idx,3,' ');
					x_idx +=6;
					if ( tahmin > rnd_asd ){
						if ( yakinlik == 0 |  yakinlik == 2){
							TIM10->ARR = 100;
							yakinlik = 1;
						}
							TIM_Cmd ( TIM10 , ENABLE );
					}
					if ( tahmin < rnd_asd ){
						 if ( yakinlik == 0 | yakinlik  ==  1 ){
							yakinlik = 2;
							TIM10->ARR = 250;
						 }
						
							TIM_Cmd ( TIM10 , ENABLE );
					}
					tahmin =0;
					if  (hakk <=0 ){
						oyunu_bitir();
					}
			//		TIM_Cmd ( TIM10 , ENABLE );
				}
				else {
				put_str_wAdress( 0*6,2,"  bildinizzz  ");
					yakinlik =3;
					oyunu_bitir();
//					if ( flag == 1 ) {
//						TIM10->ARR -=1 ;
//					} 
//					else if ( flag == 0 ) {
//						TIM10->ARR+= 1;
//					}
//					if ( TIM10->ARR == 80 | TIM10->ARR == 120) {
//						flag ^= 0x01;
//					}
				}
			}
		}
			//	TIM_Cmd ( TIM10 , DISABLE );
	}
		prev_tick = msTicks;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

uint32_t get_RNG( int top_lim, int bot_lim ){
	while( RNG_GetFlagStatus(RNG_FLAG_DRDY) != SET );
	return bot_lim + RNG_GetRandomNumber()%(top_lim-bot_lim);
}

uint16_t Read_ADC(void){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1, ADC_SampleTime_56Cycles);  /*hesaplama islemi tek cycle da hesaplanmaz,genis sürede daha az ak1m ceker,
		tepki süresi önemli ise kisa tutulabilir */
	ADC_SoftwareStartConv(ADC1);     // adc1 üzerinde yazilimsal dönüsümü baslat 
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);  /*icerideki sart saglandikca assagiya inme while noktali virgül ile bitiyorsa,
		her dönüsüm sonrasi bayrak sifirlandi*/
	return ADC_GetConversionValue(ADC1);	
}


void delayms(int ms){
  uint32_t currTick=0;
	currTick = msTicks;
	while((msTicks - currTick)< ms){		}
}

void SysTick_Handler(){
	msTicks++;
}

