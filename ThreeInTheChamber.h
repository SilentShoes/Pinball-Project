int currentScore = 0;
int highScore = 0;
int multiplier = 1;
int lives = 3;
int bumperHitBit = 0;
int drainBit = 0;
int bumper1Bit = 0;
int bumper2Bit = 0;
int bumper3Bit = 0;
int bumper4Bit = 0;

while (gameActive = 1)      //Signal recieved from button

{
    if(bumperHitBit = 1)      // Normal bumper is hit
        {
            100 * multiplier = currentScore;
        }
    
    if(bumper1Bit = 1,bumper2Bit = 1,bumper3Bit = 1,bumper4Bit)      // Certain bumpers hit increases multiplier
        {
            multiplier++;
        }

    if(drainBit = 1)        //Loss of a life
        {
            lives--;
        }
    
    if(lives = 0)       //Out of lives, game over
        {
            gameActive = 0;
        }
}

currentScore = highScore       //Keep high scores, save to certain variable
