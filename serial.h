#ifndef SERIAL_H
#define SERIAL_H

#include "..\..\MODULES\ring_buffer8.h"


// PUBLIC FUNCTION PROTOTYPES
void sendByteBlocking(unsigned char databyte);             
unsigned char sendByte(unsigned char databyte);

// PUBLIC GLOBAL/STATIC DATA
extern RingBuffer8b_TypeDef rx_data_rb;   
extern RingBuffer8b_TypeDef tx_data_rb;   

