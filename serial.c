// serial.c 
#include "msp430.h"
#include "ring_buffer8.h"                // ADD include


RingBuffer8b_TypeDef rx_data_rb;   
RingBuffer8b_TypeDef tx_data_rb;   

void sendByteBlocking(unsigned char databyte)
{
  while((IFG2 & UCA0TXIFG) == 0);    
  UCA0TXBUF = databyte;  
}
              
unsigned char sendByte(unsigned char databyte)
{
  if((IFG2 & UCA0TXIFG) == 0)
    return(0);
  UCA0TXBUF = databyte;  
  return(1);
}


// TX and RX interrupt service routine
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI_RX_ISR(void)
{
unsigned char databyte;
  
  databyte = UCA0RXBUF;

  ringbuffer8b_enqueue(&rx_data_rb, databyte);
  
}

// Interrupt for sending data
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI_TX_ISR(void)
{
  if(ringbuffer8b_isempty(&tx_data_rb) == FALSE)
    UCA0TXBUF = ringbuffer8b_dequeue(&tx_data_rb);
  else
    IE2 &= ~UCA0TXIE;                               // Disable USCI_A0 TX interrupt
  

  
}
