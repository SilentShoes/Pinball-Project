// communicator.c 
#include "msp430.h"
#include "serial.h"
#include "ring_buffer8.h"                

RingBuffer8b_TypeDef payload_data;

unsigned char consumer_state = 0;
unsigned char producer_state = 0;

/* Function address
unsigned char addressScore = 0x01;
unsigned char addressLights = 0x02;
unsigned char addressMusic = 0x03;
unsigned char addressSensors = 0x04;
unsigned char addressFlippers = 0x05;
unsigned char addressBumpers = 0x06;
unsigned char addressPlunger = 0x07;
*/

void MessageReceiver( void )
{ 
  unsigned char data;
  unsigned char local_checksum;
  switch(consumer_state)
  {
    // Start bit
    case 0:
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
          break;  
        }
          
    // Gamemode code
    // Unused for now - little time left
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

    // Active game flag. Used to start timer after gamemode selection
    // 0x00: Game off
    // 0x01: Game active
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

      // Ball lost flag.
      case 5:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x06;

          // Do something

        }
          else 
        {
            consumer_state = 0;
        }
        break;  

      // 10 seconds of timer remaining flag
      case 6:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x07;

          // Do something

        }
          else 
        {
            consumer_state = 0;
        }
        break;  
      
      // Score data byte 1
      // Bits 1-8
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

      // Score data byte 2
      // Bits 9-16
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
      
      // Score data byte 3
      // Bits 17-24
      case 9:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x0A;
        }
          else 
        {
            consumer_state = 0;
        }
        break;

    // Score data byte 4
    // Bits 25-32
    case 10:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x0B;
        }
          else 
        {
            consumer_state = 0;
        }
        break;
    
    // Local checksum verification
    case 11:    
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          if(data == local_checksum)
          {
            consumer_state = 0x0C;
          }
        }
          else 
        {
            consumer_state = 0;
        }
        break;

    // Stop byte
    case 12:    
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


void SendMessage(unsigned char dest_address, unsigned char gamemode, unsigned char active_flag, unsigned char ball_lost_flag, unsigned char ten_sec_flag,
unsigned char score_byte1, unsigned char score_byte2, unsigned char score_byte3, unsigned char score_byte4, unsigned char checksum)
{
    ringbuffer8b_enqueue(&tx_data_rb, 0xE3);
    ringbuffer8b_enqueue(&tx_data_rb, dest_address); //Destination address
    ringbuffer8b_enqueue(&tx_data_rb, 0x00);
    ringbuffer8b_enqueue(&tx_data_rb, gamemode);
    ringbuffer8b_enqueue(&tx_data_rb, active_flag);
    ringbuffer8b_enqueue(&tx_data_rb, ball_lost_flag);
    ringbuffer8b_enqueue(&tx_data_rb, ten_sec_flag);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte1);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte2);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte3);
    ringbuffer8b_enqueue(&tx_data_rb, score_byte4);
    ringbuffer8b_enqueue(&tx_data_rb, checksum);
    ringbuffer8b_enqueue(&tx_data_rb, 0x3E;

  
     IE2 |= UCA0TXIE;     // Enable Transmit Register Empty Interrupt
}
