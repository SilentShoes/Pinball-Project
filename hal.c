/*     MSP430G2553 HAL FOR G2 LAUNCHPAD   ******************************************************************
;
;       P2      7 6 5 4 3 2 1 0
;               | | | | | | | | 
;               | | | | | | | *-PWM (T1-OUTO) or CAPTURE (T1-0A)
;               | | | | | | *---PWM (T1-OUT1) or CAPTURE (T1-1A)
;               | | | | | *-----PWM (T1-OUT1) or CAPTURE (T1-1B)
;               | | | | *-------PWM (T1-OUT0) or CAPTURE (T1-0B)
;               | | | *---------PWM (T1-OUT2) or CAPTURE (T1-2A)
;               | | *-----------PWM (T1-0UT2) or CAPTURE (T1-2B)
;               | *-------------PWM (T1-OUT2) or XTAL IN
;               *---------------XTAL OUT
;
;
;      P1       7 6 5 4 3 2 1 0
;               | | | | | | | | 
;               | | | | | | | *-LED
;               | | | | | | *---UARTA0 (RX) or PWM (TO-OUT0) or CAPTURE (T0-0A)
;               | | | | | *-----UARTA0 (TX) or PWM (T0-OUT1) or CAPTURE (T0-1A)
;               | | | | *-------PB or ADC(A3)
;               | | | *---------ADC(A4)
;               | | *-----------PWM (TO OUT0) or ADC(A5) 
;               | *-------------PWM (T0 OUT1) or ADC(A6) or COMPA or SPI/I2C
;               *---------------ADC(A7) or SPI/I2C or COMPA
****************************************************************************** */

#include "msp430G2553.h"
#include "hal.h"

void configGPIO_UI( void )
{
  P1OUT = 0;                                    // Clear output buffer           
  P1DIR = _STATUSLED_BIT;                        // StatusLED (P1.0) output
  P1REN = _PUSHBUTTON_BIT;                      // Pushbutton pull up resistor enabled
  P1OUT = _STATUSLED_BIT | _PUSHBUTTON_BIT;       
}

void configGPIO_CAPTURE_TESTER( void )
{
  P2DIR |= BIT1+BIT3+BIT5;                        
}


void configTIMERA0_10msTick( void )
{
  TA0CCTL0 = CCIE;                    // Set TA1CCR1 reset/set            
  TA0CCR0 = 10000;                    // Set  Period        
  TA0CTL = TASSEL_2+MC_1+ID_3;             // SMCLK, upmode, divide by 8
}

/*
;   Timer_A0, Capture TA0.0, , DCO SMCLK
;
;   Description: Allows a program to capture a pulse width on P1.1
;   using Timer_A0 configured for continuous mode. 
;   The value in TA1CCR0 reflects the period of the signal on P1.1
;  
;   ACLK = n/a, SMCLK = MCLK = TACLK = default DCO
*/
void configTIMERA0_CAPTURE( void )
{
  P1DIR &= BIT1;                // P1.1 Input
  P1DIR |= BIT1;                // Enable TIMER A0.1 CCI0A on P1.1
  TA0CTL = TASSEL_2+MC_2;               // SMCLK, Continuous Counting Mode
  TA0CCTL0 = CM_1 + CCIS_0 + SCS + CAP; // Capture on Rising Edge, CCI0A, Synchronized capture,  Capture Mode
  
}

/*
;   Timer_A0, PWM TA0.1, TA0.1, Up Mode, DCO SMCLK
;
;   Description: Allows a program to generate two PWM outputs on  
;   P1.5 (TA0.1) using Timer_A0 configured for up mode. 
;   The value in TA0CCR0, 512-1, defines the PWM period
;   and the value in TA1CCR0 the PWM duty cycles.
;   ACLK = n/a, SMCLK = MCLK = TACLK = default DCO
*/
void configTIMERA0_PWM( void )
{
  P1DIR = BIT5;                                 // P1.5
  P1SEL = BIT5;                                 // PWM options P1.5 -> TA0.1
  
  TA0CCR0 = MTRDRIVE_PERIOD;                    // Set PWM Period        
  TA0CCTL1 = OUTMOD_7;                          // Set TA1CCR1 reset/set            
  TA0CCR1 = MTRDRIVE_OFF;                           // Init TA1CCR1 PWM Duty Cycle	
  TA0CTL = TASSEL_2+MC_1;                       // SMCLK, upmode
}


/*
;   Timer_A1, PWM TA1.1, TA1.2, Up Mode, DCO SMCLK
;
;   Description: Allows a program to generate two PWM outputs on P2.1 (TA1.1) and 
;   P2.4 (TA1.2) using Timer_A1 configured for up mode. 
;   The value in TA1CCR0, 512-1, defines the PWM period
;   and the value in TA1CCR1, TA1CCR2 the PWM duty cycles.
;   ACLK = n/a, SMCLK = MCLK = TACLK = default DCO
*/
void configTIMERA1_PWM( void )
{
  P2OUT = 0;                                    // Clear output buffer
  P2DIR = _M1PWM_BIT+_M2PWM_BIT;                 // P2.1, P2.2 outputs 
  P2SEL = _M1PWM_BIT+_M2PWM_BIT;                 // PWM options P2.1,P2.4 -> TA1.1, TA1.2 
  
  TA1CCR0 = MTRDRIVE_PERIOD;                    // Set PWM Period        
  TA1CCTL1 = OUTMOD_7;                          // Set TA1CCR1 reset/set            
  TA1CCR1 = MTRDRIVE_OFF;                           // Init TA1CCR1 PWM Duty Cycle	
  TA1CCTL2 = OUTMOD_7;                          // Set TA1CCR2 reset/set            
  TA1CCR2 = MTRDRIVE_OFF;                           // Init TA1CCR2 PWM Duty Cycle	            
  TA1CTL = TASSEL_2+MC_1;                       // SMCLK, upmode
}

/*
;   Timer_A1, Capture TA1.0, , DCO SMCLK
;
;   Description: Allows a program to capture a pulse width on P2.0
;   using Timer_A1 configured for continuous mode. 
;   The value in TA1CCR0 reflects the period of the signal on P2.0
;  
;   ACLK = n/a, SMCLK = MCLK = TACLK = DCO
*/
void configTIMERA1_CAPTURE( void )
{
  P2DIR &= ~(BIT0 + BIT2 + BIT4);       // P2.0 P2.2 P2.4 input
  P2SEL |= BIT0 + BIT2 + BIT4;          // Enable TIMER A1.0 CCI0A on P2.0, TIMER A1.1 CCI1B on P2.2, TIMER A1.2 CC2A on P2.4
  TA1CTL = TASSEL_2+MC_2;               // SMCLK, Continuous Counting Mode
  TA1CCTL0 = CM_1 + CCIS_0 + SCS + CAP + CCIE; // Capture on Rising Edge, CCI0A, Synchronized capture,  Capture Mode
  TA1CCTL1 = CM_1 + CCIS_1 + SCS + CAP; // Capture on Rising Edge, CCI1B, Synchronized capture,  Capture Mode
  TA1CCTL2 = CM_1 + CCIS_0 + SCS + CAP; // Capture on Rising Edge, CCI2A, Synchronized capture,  Capture Mode
  
}



void configUSCI_A0( void )
{
  
  P1SEL |= BIT1 + BIT2;                          // P1.1 = RXD, P1.2=TXD
  P1SEL2 |= BIT1 + BIT2;                         // P1.1 = RXD, P1.2=TXD  
  UCA0CTL1 |= UCSSEL_2;                          // SMCLK as input clock
  UCA0BR0 = 65;                                 // Config baud rate divider 8MHz 9600
  UCA0BR1 = 3;                                   // 8MHz 9600
  UCA0MCTL = UCBRS1;                             // Modulation UCBRSx = 2
  UCA0CTL1 &= ~UCSWRST;                          // **Initialize USCI state machine**  BIC.B #UCSWRST, &UCA0CTL1
  IE2 |= UCA0RXIE;                               // Enable USCI_A0 RX interrupt
}



void setP21DutyCycle ( unsigned int dutycycle )
{
  TA1CCR1 = dutycycle;
}

void setP24DutyCycle ( unsigned int dutycycle )
{
  TA1CCR2 = dutycycle;
}

void turnOnLED1 ( void )
{
    P1OUT |= _STATUSLED_BIT;
}


void turnOffLED1 ( void )
{
    P1OUT &= ~_STATUSLED_BIT;
}

void toggleLED1 ( void)
{
  P1OUT ^= _STATUSLED_BIT;
}
