// // module1.c 
#include "msp430.h"
#include "..\..\MODULES\ring_buffer8.h"
#include "module1.h"

RingBuffer8b_TypeDef module1_event_data;
RingBuffer8b_TypeDef module1_output_data;

unsigned int module1SupportFunction(unsigned int);

void module1EventHandler( unsigned char module1param )
{ 
  static unsigned int data1;
  unsigned int inputdata = 0;  // Assume this data actually comes from a ring buffer
  unsigned char inputevent;
  bool new_event = FALSE;
  
  
  if(ringbuffer8b_isempty(&module1_event_data) == FALSE)
  {
    inputevent = ringbuffer8b_dequeue(&module1_event_data);
    new_event = TRUE;
  }

  if(new_event)
  {
    switch(inputevent)
    {
    case MODULE1_EVENT_BUTTONPRESS:            
      data1 = module1SupportFunction(inputdata);  //
      break;
      
    }
      
    
  }
  
  
  
}


unsigned int module1SupportFunction(unsigned int input)
{
  return input * 2;
}
