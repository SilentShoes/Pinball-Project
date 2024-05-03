// // module1.h
#ifndef MODULE1_H
#define  MODULE1_H

#include "..\..\MODULES\ring_buffer8.h"

// PUBLIC FUNCTION PROTOTYPES
void module1EventHandler( unsigned char );
unsigned int module1SupportFunction(unsigned int);

// PUBLIC GLOBAL/STATIC DATA
extern RingBuffer8b_TypeDef module1_event_data;


// PUBLIC DEFINITIONS
#define MODULE1_MODE_NORMAL 0

#define MODULE1_EVENT_BUTTONPRESS 0 






#endif
