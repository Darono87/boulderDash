#include "Player.h"
#include <iostream>
int Stone::objectEnter(EventAwareSprite* another, int direction){

    if(direction == 1 || direction == 3)
        return -1;

    Player* player = dynamic_cast<Player*>(another);
    if(player){
        if(player->isPushing())
            return 0;
        if(direction == 0 && root->elements[boardX+1][boardY] != nullptr)
            return 0;
        else if(direction == 2 && root->elements[boardX-1][boardY] != nullptr)
            return 0;

        player->startPushing(this,direction);
        root->issueEvent(player,101);

        return 0;
    }
}

int Stone::readyToFall(){
    if(!isFalling){     
        fallTimer.restart();
        isFalling = true;
    }
    if(root->elements[boardX][boardY+1]){
        isFalling = false;
        return -1;
    } else if(fallTimer.getElapsedTime().asMilliseconds() >= STONE_FALL_TIME)
        return 1;
    else
        return 0;
    
}

int Stone::readyToSlip(){
    if(!isSlipping){     
        slipTimer.restart();
        isSlipping = true;
    }
    if((slipDirection==0 && root->elements[boardX+1][boardY])||(slipDirection==2 && root->elements[boardX-1][boardY])){
        isSlipping = false;
        slipDirection = -1;
        return -1;
    } else if(slipTimer.getElapsedTime().asMilliseconds() >= STONE_SLIP_TIME)
        return 1;
    else
        return 0;
    
}

void Stone::stoneSlip(){
    if(slipDirection==0){
        putOnTheBoard(boardX+1,boardY);
        if(!root->issueEvent(root->elements[boardX-1][boardY-1],102)) //Avalanche
            root->issueEvent(root->elements[boardX-2][boardY-1],104);
    }
    if(slipDirection==2){
        putOnTheBoard(boardX-1,boardY);
        if(!root->issueEvent(root->elements[boardX+1][boardY-1],102)) //Avalanche
            root->issueEvent(root->elements[boardX+2][boardY-1],103);
    }
    root->issueEvent(this,102);
    slipDirection = -1;
    isSlipping = false;
    
}

void Stone::fallVert(){
    putOnTheBoard(boardX,boardY+1);
    isFalling = false;
    if(!root->issueEvent(this,102)){
        //check if player was hit
        root->issueEvent(root->elements[boardX][boardY+1],201); //event - hit by a rock

        if(!root->issueEvent(this,103)){
            root->issueEvent(this,104); //after falling it can rool over to continue falling down
        }
    }
    if(!root->issueEvent(root->elements[boardX][boardY-2],102)) //Avalanche
        if(!root->issueEvent(root->elements[boardX-1][boardY-2],104))
            root->issueEvent(root->elements[boardX+1][boardY-2],103);
    
}

bool Stone::acceptEvent(int code){
    switch(code){
        case 101: return false;
        case 102: if(!root->elements[boardX][boardY+1]) return true; else return false;
        case 103: {
            Stone* isStone = dynamic_cast <Stone*> (root->elements[boardX][boardY+1]);
            if(!isFalling && isStone && !root->elements[boardX-1][boardY] && !root->elements[boardX-1][boardY+1])
                return true;
            else
                return false;
        }
        case 104: {
            Stone* isStone = dynamic_cast <Stone*> (root->elements[boardX][boardY+1]);
            if(!isFalling && isStone && !root->elements[boardX+1][boardY] && !root->elements[boardX+1][boardY+1])
                return true;
            else
                return false;
        }
        default: return false;
    }
}