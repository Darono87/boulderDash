#include "PlayrunInterface.h"
int PlayrunInterface::descreaseLifesAmmount()
{
    lifesText.setString(lifesPrefix + to_string(--lifes));
    return lifes;
}
void PlayrunInterface::constructTextInterface()
{
    addPoints(0);
    boardText.setString(boardPrefix + to_string(actualBoardNum));
    lifesText.setString(lifesPrefix + to_string(lifes));
    updateTimer();
}
bool PlayrunInterface::popLife()
{
    if (lifes == 0){
        lifes--;
        return false;
    }
    else
        return descreaseLifesAmmount() + 1;
} //success if there is a life to consume

PlayrunInterface::PlayrunInterface(sf::Font& font, sf::Vector2f pos, int runTime_, Application* app) : pos(pos), score(0), lifes(NUM_LIFES), app(app),
                                                        actualBoardNum(1), innerFont(font), runTime(runTime_)
{
    scoreText.construct(innerFont, sf::Vector2f(pos.x + 310, pos.y));
    lifesText.construct(innerFont, sf::Vector2f(pos.x, pos.y));
    boardText.construct(innerFont, sf::Vector2f(pos.x + 650, pos.y));
    timerText.construct(innerFont,sf::Vector2f(pos.x+310,pos.y+20));

    constructTextInterface();
}
void PlayrunInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(scoreText);
    target.draw(boardText);
    target.draw(lifesText);
    target.draw(timerText);
}
void PlayrunInterface::resetTimer(int runTime_) {runTime = runTime_; timeLeft.restart(); timeIsUp = false; blockTimer = false;}
void PlayrunInterface::updateTimer(){
    if(blockTimer)
        return;
    float tl = timeLeft.getElapsedTime().asSeconds();
    if(runTime-tl<=0 && !timeIsUp){
        timerText.setString(timerPrefix + "0");
        app->currentBoard->timerIsUp();
        timeIsUp = true;
    }
    else if(runTime-tl>0)
        timerText.setString(timerPrefix + to_string(runTime-tl));
    
}
void PlayrunInterface::addPoints(int points){
    score += points;
    scoreText.setString(scorePrefix + to_string(score));
}
void PlayrunInterface::addTimerScore(){
    score += BEAT_TIMER_SCORE*((runTime-timeLeft.getElapsedTime().asSeconds())/runTime);
    scoreText.setString(scorePrefix + to_string(score));
}

void PlayrunInterface::reloadOnDeath(){
    resetTimer(runTime);
    score = startScore;
    addPoints(0);
}