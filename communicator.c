// communicator.c 
#include "msp430.h"
#include "serial.h"
#include "ring_buffer8.h"                
#include "score.h"

RingBuffer8b_TypeDef payload_data;

unsigned char consumer_state = 0;
unsigned char producer_state = 0;

void MessageReceiver( void )
{ 
  unsigned char data;
  unsigned char local_checksum;
  switch(consumer_state)
  {
    // Start bit
    case 0:
        local_checksum = ""; // Unsure if this is how you'd clear a variable
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          if(data == 0xE3)
          {
            local_checksum += data;
            consumer_state = 0x01;
          }
          else 
          {
            consumer_state = 0;
          }
        break;          
        }

    //Destination address check
    case 1:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          if(data == myAddress)
          {
            consumer_state = 0x02;
          }
        }
        else 
        {
            consumer_state = 0;
        }
        break;   

    // Function byte
    // If 0, score is ongoing score. If 1, the score is the high score
    case 2:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
            data = ringbuffer8b_dequeue(&rx_data_rb);
            local_checksum += data;
            consumer_state = 0x03;
        } 
        else 
        {
            consumer_state = 0;
        }
        break;
        

    // Active game flag. Used to start timer after gamemode selection
    // 0x00: Game off
    // 0x01: Game active
    case 3:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x04;

          // Do something

        }
          else 
        {
            consumer_state = 0;
        }
        break;   

      // Lives remaining
      case 4:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x05;

          // Do something

        }
          else 
        {
            consumer_state = 0;
        }
        break;  
      
      // Score data byte 1
      // Bits 1-8
      case 5:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x06;
        }
          else 
        {
            consumer_state = 0;
        }
        break;   

      // Score data byte 2
      // Bits 9-16
      case 6:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x07;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
      
      // Score data byte 3
      // Bits 17-24
      case 7:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x08;
        }
          else 
        {
            consumer_state = 0;
        }
        break;

    // Score data byte 4
    // Bits 25-32
    case 8:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x09;
        }
          else 
        {
            consumer_state = 0;
        }
        break;
    
    // Local checksum verification
    case 9:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          if(data == local_checksum)
          {
            consumer_state = 0x0A;
          }
        }
          else 
        {
            consumer_state = 0;
        }
        break;

    // Stop byte
    case 10:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
            if(data == 0xE3)
            {
            consumer_state = 0;
            }
        }
        break;
    }
    
}


void SendMessage(unsigned char dest_address, unsigned char function_flag, unsigned char active_flag, unsigned char lives,
unsigned char score_byte1, unsigned char score_byte2, unsigned char score_byte3, unsigned char score_byte4)
{
    chk = dest_address + function_flag + active_flag + lives + score_byte1 + score_byte2 + score_byte3 + score_byte4;
    ringbuffer8b_enqueue(&tx_data_rb, 0xE3);
    ringbuffer8b_enqueue(&tx_data_rb, dest_address); //Destination address
    ringbuffer8b_enqueue(&tx_data_rb, function_flag); //Function 
    ringbuffer8b_enqueue(&tx_data_rb, active_flag);
    ringbuffer8b_enqueue(&tx_data_rb, lives);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte1);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte2);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte3);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte4);
    ringbuffer8b_enqueue(&tx_data_rb, chk);
    ringbuffer8b_enqueue(&tx_data_rb, 0x3E;
  
     IE2 |= UCA0TXIE;     // Enable Transmit Register Empty Interrupt
}
