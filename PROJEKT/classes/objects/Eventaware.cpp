#include "Eventaware.h"
void EventAwareSprite::putOnTheBoard(int x, int y){
    if(x < 0 || x >= root->boardSize.x || y < 0 || y >= root->boardSize.y )
        return;
    root->elements[boardX][boardY] = nullptr;
    boardX = x;
    boardY = y;
    
    setPosition(calculatePositionVector(x,y));
    if(!root->elements[x][y])
        root->elements[x][y] = this;
}