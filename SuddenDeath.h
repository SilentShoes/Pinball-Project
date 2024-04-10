int currentScore = 0;
int highScore = 0;
int multiplier = 1;
int lives = 1;
int bumperHitBit = 0;
int drainBit = 0;

while (gameactive = 1)      //Signal recieved from button

{
    if(bumperHitBit = 1)       // Normal bumper is hit
        {
            score + 100 * multiplier;
        }
        
    if(10 secs pass)    //Every 10 seconds increase multiplier by 1
        {
            multiplier++;
        }
        
    if(drainBit = 1)         //Drain hit, game over
        {
            gameActive = 0;
        }
}

currentScore = highScore            //Keep high scores, save to certain variable

