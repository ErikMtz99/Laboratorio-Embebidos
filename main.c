/*
 * GccApplication1.c
 *
 * Created: 5/11/2022 6:09:54 PM
 * Author : Erik Martinez
 */ 

#include "spi.h"
#include "myprintf.h"
#include "sam.h"
#include "stdint.h"
#include "uart.h"
#include "stdio.h"

#define SIZE_SD_CMD 0x06
#define RXBUFSIZE 0x400

void initCycles(void); 

const uint8_t CMD00[SIZE_SD_CMD] ={0x40, 0x00, 0x00, 0x00, 0x00, 0x95}; 
const uint8_t CMD08[SIZE_SD_CMD] ={0x48, 0x00, 0x00, 0x01, 0xAA, 0x87}; 
uint8_t CMD17[SIZE_SD_CMD] ={0x51, 0x00, 0x00, 0x00, 0x00, 0x01}; 
uint8_t CMD172[SIZE_SD_CMD] ={0x51, 0x00, 0x00, 0x08, 0x00, 0x01};
const uint8_t CMD18[SIZE_SD_CMD] ={0x52, 0x00, 0x00, 0x00, 0x00, 0x01}; 
const uint8_t CMD55[SIZE_SD_CMD] ={0x77, 0x00, 0x00, 0x00, 0x00, 0x65};
const uint8_t CMD41[SIZE_SD_CMD] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x77};
uint8_t RxBuffer[RXBUFSIZE];

int main(void) { 
	uint32_t temp = 0xFF; /* Initialize the SAM system */ 
	uint32_t voltaje, c_pattern, c_pattern2, bit34, response;
	uint8_t y;
	SystemInit(); 
	UARTInit(); 
	spiInit(); 
	initCycles(); //myprintf("\n"); 
	do 
	{
		spiXchg( CMD00, SIZE_SD_CMD, RxBuffer );
		response = RxBuffer[0] & 0x1;
	} while (response != 1);

	spiXchg( CMD08, SIZE_SD_CMD, RxBuffer ); 
	voltaje = RxBuffer[3]; 
	c_pattern = RxBuffer[4]; 
	bit34 = RxBuffer[5] & 0x4;
	
	//for (y=0;y<5;y++){
	//	myprintf("\nBuffer %x", RxBuffer[y]);
	//}
	if(bit34 == 0){
		
		if((voltaje == 0x1) && (c_pattern == 0xaa)){
			do 
			{
				spiXchg( CMD55, SIZE_SD_CMD, RxBuffer );
				temp = spiXchg( CMD41, SIZE_SD_CMD, RxBuffer );	
			} while (temp !=0);
			//Write your code here
			myprintf("\nIs Ready"); 
		}
	}
 
	rcvr_datablock(CMD17, 0x0000, RxBuffer, 512);
		
}

void initCycles(void){ 
	uint32_t i; 
	REG_PORT_OUTSET0 = PORT_PA18; 
	for(i=0;i<76;i++) 
	spiSend(0xFF);
}






