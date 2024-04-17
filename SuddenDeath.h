bool gameActive = 0;
unsigned int currentScore = 0;
unsigned int highScore1 = 0;
unsigned int multiplier = 1;
bool bumperHitBit = 0;
bool drainBit = 0;

while (gameActive = 1)      //Signal recieved from button

{
    if(bumperHitBit == 1)       // Normal bumper is hit
        {
            currentScore = currentScore + (100 * multiplier);
        }
    if(10 secs pass)    //Needs interrupt
        {
            multiplier++;
        }
    if(drainBit == 1)         //Drain hit, game over
        {
            gameActive = 0;
        }
}

while (gameActive = 0)

{  
    if(currentScore > highScore1)    //Keep high scores, save to certain variable
    
        {
            currentScore = highScore;   //Save high score
                                        //Push to scoreboard
            currentScore = 0;           //Reset score
        }
}
