
#include "spi_drive.h"


void spi_send( SPI_TypeDef* spi, char data){

//	GPIO_ResetBits( SPI_PORT, CS_PIN);
//	spi->DR = data;
//	while(spi->SR & 0x80){}
//		
		while(!SPI_I2S_GetFlagStatus(spi,SPI_I2S_FLAG_TXE));

			SPI_I2S_SendData(spi,data);

//	GPIO_SetBits( SPI_PORT, CS_PIN);

}

void spi1_send( SPI_TypeDef* spi, char data){

			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
			while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
			SPI1->DR = data;  // load the data into the Data Register

			/*During discontinuous communications, there is a 2 APB clock period delay between the
			write operation to the SPI_DR register and BSY bit setting. As a consequence it is
			mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
			data.
			*/
			while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
			while (((SPI1->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
			//  Clear the Overrun flag by reading DR and SR
			uint8_t temp = SPI1->DR;
			temp = SPI1->SR;
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	
//		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//		SPI1->DR = data;
//		while(SPI1->SR & 0x80){}
//		delayms(1);
//		GPIO_SetBits(GPIOA,GPIO_Pin_4);


//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
//	SPI_I2S_SendData(SPI1,data);
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);

//		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//		SPI1->DR = data;
//		while(SPI1->SR & 0x80){}
//		GPIO_SetBits(GPIOA,GPIO_Pin_4);

}
void spi1_send_PRV( SPI_TypeDef* spi, char data){


		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		SPI1->DR = data;
		while(SPI1->SR & 0x80){}
	//	delayms(1);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
			
			
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	SPI_I2S_SendData(SPI1,data);
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);

__NOP();
}
