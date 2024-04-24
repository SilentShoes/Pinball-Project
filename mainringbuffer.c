/*******************************************************************************
;   TankBot Motor Drive using Timer_A, PWM TA1.1, TA1.2, Up Mode, DCO SMCLK
;
;   Description: This program generates two PWM outputs on P2.1 (TA1.1) and 
;   P2.4 (TA1.2) using Timer_A configured for up mode. 
;   The value in TA1CCR0, 512-1, defines the PWM period
;   and the value in TA1CCR1, TA1CCR2 the PWM duty cycles.
;   ACLK = n/a, SMCLK = MCLK = TACLK = default DCO
;
;
;       P2      7 6 5 4 3 2 1 0
;                     | | | | |
;                     | | | | -
;                     | | | --- Motor 1 PWM
;                     | | ----- Motor 1 Enable
;                     | ------- Motor 2 Enable
;                     --------- Motor 2 PWM
;
;      P1       7 6 5 4 3 2 1 0
;                     | | | | |
;                     | | | | - LED
;                     | | | --- RX
;                     | | ----- TX
;                     | ------- PB
;                     ---------  
****************************************************************************** */
#include <msp430g2553.h>
#include "serial.h"
#include "hal.h"
#include "ring_buffer.h"                // ADD include

void programMode(void);
void navigateMode(void);

extern RingBuffer_TypeDef my_rb;       // ADD extern declaration


RingBuffer_TypeDef rx_data_rb;
RingBuffer_TypeDef tx_data_rb;

void main( void )
{
  unsigned char state = 100;
  unsigned char testbyte;
  unsigned char checksum;
  unsigned char my_address;
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_8MHZ;                       // Set DCO to 8MHz
  DCOCTL =  CALDCO_8MHZ; 

  configGPIO();
  configTIMERA0();
  configTIMERA1();
  configUSCI_A0();
  _BIS_SR(GIE);                 // Enable interrupt
  ringbuffer_flush(&my_rb);     // ADD 

  
  while(1)
  {
    

    switch(state)
    {
    case 0:     // SOM
        if(ringbuffer_isempty(&my_rb) == FALSE)
        {
          testbyte = ringbuffer_dequeue(&my_rb);
          if(testbyte == 0xE3)
            state = 0x01;
          else 
            state = 0;
        }
        checksum = 0;
        break;          
    case 1:     // msg
        if(ringbuffer_isempty(&my_rb) == FALSE)
        {
          testbyte = ringbuffer_dequeue(&my_rb);
          checksum = checksum + testbyte;
          state = 0x02;
        }   
        break;
    case 2:
        if(ringbuffer_isempty(&my_rb) == FALSE)
        {
          testbyte = ringbuffer_dequeue(&my_rb);
          checksum = checksum + testbyte;
          if(testbyte == my_address)
            state = 0x03;
          else 
            state = 0;
        }   
        break;
    case 100:
      testEnqueue();
      
      if(PB == 0)
         testDequeue();
      break;
    }


    

  }
  
}
