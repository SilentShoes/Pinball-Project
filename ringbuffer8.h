#ifndef RING_BUFFER8_H
#define RING_BUFFER8_H

#define RINGBUFFERSIZE 16
//
//
/* other */


typedef struct
{
  unsigned char head;
  unsigned char tail;
  unsigned int array[RINGBUFFERSIZE];

} RingBuffer8b_TypeDef;



#ifndef RING_BUFFER16_H
typedef enum {FALSE = 0, TRUE = 1} bool;
#endif

bool ringbuffer8b_isfull(RingBuffer8b_TypeDef *rb);
bool ringbuffer8b_isempty(RingBuffer8b_TypeDef *rb);
unsigned char ringbuffer8b_dequeue(RingBuffer8b_TypeDef *rb);
bool ringbuffer8b_enqueue(RingBuffer8b_TypeDef *rb, unsigned char bytedata);
void ringbuffer8b_flush(RingBuffer8b_TypeDef *rb);



#endif
