//score.c
#include "communicator.h"
#include "score.h"

bool gameActive = 0;
unsigned int currentScore = 0;
unsigned int highscore = 0;
unsigned char multiplier = 1;
unsigned char lives = 3;
bool drainBit = 0;
bool bumperHitBit = 0;
unsigned char function = 0;

// Functionality addresses
unsigned char addressScore = 0x01;
unsigned char addressLights = 0x02;
unsigned char addressMusic = 0x03;
unsigned char addressSensors = 0x04;
unsigned char addressFlippers = 0x05;
unsigned char addressBumpers = 0x06;
unsigned char addressPlunger = 0x07;


char allAddresses[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

while (gameActive == 1)      //Signal recieved from button 
{
    //Send gamemode active flag to all
    for(int i = 0; i < 8; ++i)
    {
        SendMessage(allAddresses[i], function, gameActive, lives, score); //Figure out score bytes
    }
    
    if(bumperHitBit == 1)      // Bumper 1 is hit
    {
        currentScore = currentScore + (100 * multiplier);
        //Send coontinuous updates to scoreboard
        SendMessage(addressScore, function, gameActive, lives, score); //Figure out score bytes
        bumperHitBit = 0;
    }
    if(multiplier == 1)      // Certain bumpers hit increases multiplier
    {
        multiplier++;
    }
    if(drainBit == 1)        //Loss of a life
    {
        lives--;
    }
    if(lives == 0)       //Out of lives, game over
    {
        gameActive = 0; //Turn off game

        // Send (possible) new high score
        if(currentScore > high_score)
        {
            high_score = currentScore;       //Save high score
            function = 0x01;    //Change to high score function
            for(int i = 0; i < 8; ++i)
            {
                //Send (possible) new high score & game status to others
                SendMessage(allAddresses[i], function, gameActive, lives, score); //Figure out score bytes
            }
            function = 0;    //Reset function
            currentScore = 0;    //Reset score
        }
    }
}
