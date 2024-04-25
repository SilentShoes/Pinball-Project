// communicator.c 
#include "msp430.h"
#include "serial.h"
#include "ring_buffer8.h"                

RingBuffer8b_TypeDef payload_data;

unsigned char consumer_state = 0;
unsigned char producer_state = 0;

void MessageReceiver( void )
{ 
  unsigned char data;

  switch(consumer_state)
  {
    case 0:     // SOM
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x01;
        }
          else 
        {
            consumer_state = 0;
        }
        break;          
    case 1:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x02;
        }
        else 
        {
            consumer_state = 0;
        }
        break;   
    case 2:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x03;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    case 3:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x04;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
     case 4:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x05;
        }
          else 
        {
            consumer_state = 0;
        }
        break;   
    case 5:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x06;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    case 6:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x07;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
     case 7:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x08;
        }
          else 
        {
            consumer_state = 0;
        }
        break;   
    case 8:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x09;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    case 9:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x0A;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    }
    
}


void SendMessage(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4)
{
    ringbuffer8b_enqueue(&tx_data_rb, 0xE3);
  
     IE2 |= UCA0TXIE;     // Enable Transmit Register Empty Interrupt
}
