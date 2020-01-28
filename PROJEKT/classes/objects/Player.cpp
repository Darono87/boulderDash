#include "Player.h"

void Player::pushRestart(){
    setTexture(innerTexture);
    pushAborted = false;
    pushDirection = -1;
    beingPushed = nullptr;
}

int Player::objectEnter(EventAwareSprite* another ,int direction){
    Lava* lava = dynamic_cast<Lava*>(another);
    if(lava){
        //player is dead
        playerDie();
        lava->freeze();
        return -1;
    }
};

void Player::startPushing(Stone* which, int direction){
    pushTime.restart();
    beingPushed = which;
    pushDirection = direction;
    setTexture(pushTexture);
}

int Player::playerPushCheck()
{
    if (pushAborted)
    {
        pushRestart();
        return -1;
    }
    if (pushTime.getElapsedTime().asMilliseconds() > 500)
    {
        return 1;
    }
    return 0;
}
void Player::playerPushExec()
{
    sf::Vector2i oldCoords(boardX,boardY);
    if (pushDirection == 0)
    {
        beingPushed->putOnTheBoard(beingPushed->getX() + 1, beingPushed->getY());
        putOnTheBoard(boardX + 1, boardY);
    }
    else if (pushDirection == 2)
    {
        beingPushed->putOnTheBoard(beingPushed->getX() - 1, beingPushed->getY());
        putOnTheBoard(boardX - 1, boardY);
    }
    emitEventsAfterMove(oldCoords.x,oldCoords.y,pushDirection);
    root->issueEvent(beingPushed,102);
    pushRestart();
}

void Player::emitEventsAfterMove(int oldX, int oldY, int direction){
    if(root->issueEvent(root->elements[oldX][oldY-1],102) || root->issueEvent(root->elements[oldX-1][oldY-1],104) || root->issueEvent(root->elements[oldX+1][oldY-1],103))
        return;
    if(!root->issueEvent(root->elements[oldX-1][oldY],104))
        root->issueEvent(root->elements[oldX+1][oldY],103);
}

void Player::playerDie(){
    if(immune || dead)
        return;
    moveBlock = true;
    dead = true;
    setTexture(deathTexture);

    root->app->PI->blockTimerUpdate();
    if(root->app->PI->popLife())
        root->app->alertBox.display("You've died! Press R to restart");
    else
        root->app->alertBox.display("You've lost! Press ESC to go back to main menu");
    
 }