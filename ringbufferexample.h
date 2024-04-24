#define RINGBUFFERSIZE 32

typedef struct 
{
  unsigned char head;
  unsigned char tail;
  unsigned char array[RINGBUFFERSIZE];
  
} RingBuffer_TypeDef;

typedef enum {FALSE = 0, TRUE = 1} bool;

bool ringbuffer_isfull(RingBuffer_TypeDef *rb);
bool ringbuffer_isempty(RingBuffer_TypeDef *rb);
unsigned char ringbuffer_dequeue(RingBuffer_TypeDef *rb);
bool ringbuffer_enqueue(RingBuffer_TypeDef *rb, unsigned char bytedata);
void ringbuffer_flush(RingBuffer_TypeDef *rb);
void testEnqueue(void);        // ADD prototype to allow calling test from main
void testDequeue(void);
