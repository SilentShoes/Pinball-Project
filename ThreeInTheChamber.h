bool gameActive = 0;
unsigned int currentScore = 0;
unsigned int highScoreTITC = 0;
unsigned int multiplier = 0;
unsigned int lives = 3;
bool drainBit = 0;
bool bumperHitBit = 0;

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
    if(currentScore > highScore2)
        {
            currentScore = highScoreTITC;       //Save high score
                                            //Push to scoreboard
            currentScore = 0;              //Reset score
        }
}
