bool gameActive = 0;
unsigned int currentScore = 0;
unsigned int highscore = 0;
unsigned char multiplier = 0;
unsigned char lives = 3;
bool drainBit = 0;
bool bumperHitBit = 0;

/* Function address
unsigned char addressScore = 0x01;
unsigned char addressLights = 0x02;
unsigned char addressMusic = 0x03;
unsigned char addressSensors = 0x04;
unsigned char addressFlippers = 0x05;
unsigned char addressBumpers = 0x06;
unsigned char addressPlunger = 0x07;
*/

while (gameActive == 1)      //Signal recieved from button

{
    if(bumperHitBit == 1)      // Bumper 1 is hit
    {
        currentScore = currentScore + (100 * multiplier);
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
        gameActive = 0;
    }
}

while (gameActive == 0)
{
    if(currentScore > high_score)
        {
            high_score = currentScore;       //Save high score
                                            //Push to scoreboard
            currentScore = 0;              //Reset score
        }
}
