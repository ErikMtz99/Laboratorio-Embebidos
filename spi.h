/*
 * spi.h
 *
 * Created: 5/11/2022 6:10:25 PM
 *  Author: Erik Martinez
 */ 


#ifndef SPI_H_
#define SPI_H_
#define BAUDRATE 9600
#include "stdint.h"

void spiInit( void );
uint8_t spiSend( uint8_t data );
uint32_t spiXchg(const uint8_t * send_buff, uint32_t bc, uint8_t * receive_buff);
void rcvr_datablock(const uint8_t * send_buff, uint32_t lba, uint8_t * receive_buff, uint32_t bs );
#endif /* SPI_H_ */