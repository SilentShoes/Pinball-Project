#include <msp430g2553.h>
#include <ThreeInTheChamber.h>
#include <SuddenDeath.h>

unsigned int gm_three_in_the_chamber = 0;
unsigned int gm_sudden_death = 0;

void main (void)
{
while (1)
    {
        if (gm_three_in_the_chamber == 1 && gm_sudden_death == 0)
        {
            //Move to ThreeInTheChamber.h
        } else if (gm_three_in_the_chamber ==1 && gm_sudden_death = 1)
        {
            //Move to SuddenDeath.h
        } else if (gm_three_in_the_chamber ==1 && gm_sudden_death = 1)
        {
            gm_three_in_the_chamber = 0;
            gm_sudden_death = 0;
        }
    }
}