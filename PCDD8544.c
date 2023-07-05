
#include "PCD8544.H"
#include "delayy.H"

#define SPI_1 1
#define SPI_2 0

void clear_Screen(){
		GPIO_SetBits( GPIOD, PCD8544_DC_PIN);

int i=0;
	for ( i =0; i<504;i++){
		pr_smthng(0x00);

	}

}
	

void reset_Screen(){
//clear_Screen();
GPIO_SetBits ( GPIOD , PCD8544_RST_PIN);   // reset screen start
//delayms(10);
	GPIO_ResetBits ( GPIOD , PCD8544_RST_PIN);
//delayms(10);
	GPIO_SetBits ( GPIOD , PCD8544_RST_PIN);
}

void init_Screen( void ){

	reset_Screen();
GPIO_ResetBits( GPIOD, PCD8544_DC_PIN);
		
	GPIO_SetBits( PCD8544_PORT, PCD8544_BL_PIN); // GPIOD GPIO_Pin_14
//delayms(1000);
	GPIO_ResetBits( PCD8544_PORT, PCD8544_BL_PIN);
	
//		spi1_send( SPI1,0x21);
//	spi1_send( SPI1,0xCF);
//		spi1_send( SPI1,0x20);
//	spi1_send( SPI1,0x0C);
//	 PCD8544_set_contrast();
// PCD8544_set_display();
	
}

void put_char_nOKIA ( char ch){
 	GPIO_SetBits( GPIOD, PCD8544_DC_PIN);
	int i=0;
	while( i< 6){
		spi1_send(SPI1, ASCII[ch-0x20][i]);
		i++;
	}
}

void put_str_nOKIA ( char* ch){
	while( *ch ){
	put_char_nOKIA(*ch++);
	}

}

void set_adress(int x, int y){

	int new_X =0;
	int new_Y =0;
	
	new_Y = 0x40 | y;
	new_X = 	0x80 | x;
	GPIO_ResetBits( GPIOD, PCD8544_DC_PIN);
	spi1_send(SPI1, new_Y);
	spi1_send( SPI1, new_X);		
}

void put_str_wAdress(int x, int y, char * str){
	set_adress( x,y);
	put_str_nOKIA( str);
	
}

void put_char_wAdress(int x, int y, char str){
	set_adress( x,y);
	put_char_nOKIA( str);
	
}

#if SPI_2
void PCD8544_set_contrast(){

	GPIO_ResetBits( GPIOD, GPIO_Pin_13);
	spi_send( SPI2,0x21);
	spi_send( SPI2,0xCF);
	
}
void PCD8544_set_display(){

	GPIO_ResetBits( GPIOD, GPIO_Pin_13);
	spi_send( SPI2,0x20);
	spi_send( SPI2,0x0C);
	
}

void pr_smthng ( char smthng){
	GPIO_SetBits( GPIOD, GPIO_Pin_13);
	spi_send(SPI2, smthng);

}
#endif

#if SPI_1
void PCD8544_set_contrast(){

	GPIO_ResetBits( GPIOD, PCD8544_DC_PIN);
	spi1_send( SPI1,0x21);
	spi1_send( SPI1,0xCF);
	
}
void PCD8544_set_display(){

	GPIO_ResetBits( GPIOD, PCD8544_DC_PIN);
	spi1_send( SPI1,0x20);
	spi1_send( SPI1,0x0C);
	
}

void pr_smthng ( char smthng){
	GPIO_SetBits( GPIOD, PCD8544_DC_PIN);
	spi1_send(SPI1, smthng);

}
void pr_smthng_PRV ( char smthng){
	GPIO_SetBits( GPIOD, PCD8544_DC_PIN);
	spi1_send_PRV(SPI1, smthng);

}

#endif
