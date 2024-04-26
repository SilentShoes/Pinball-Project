#include "io430.h"

unsigned int countdown1 = 0;
unsigned int countup1   = 0;

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  if(countdown1 > 0)
    countdown1--;
  
}

void setCountDown1(unsigned int count)
{
  countdown1 = count;
}

unsigned int getCountDown1(void)
{
  return(countdown1);
}

void setCountUp1(unsigned int count)
{
  countup1 = count;
}

unsigned int getCountUp1(void)
{
  return(countup1);
}
