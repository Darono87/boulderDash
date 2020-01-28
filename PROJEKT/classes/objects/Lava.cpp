#include "Lava.h"
int Lava::lavaCheckMove()
{
    if (frozen)
        return -1;
    else if (moveTime.getElapsedTime().asMilliseconds() < 200){
        if((!root->emptyLavaOrPlayer(boardX + 1, boardY) && !root->emptyLavaOrPlayer(boardX - 1, boardY) &&
            !root->emptyLavaOrPlayer(boardX, boardY + 1) && !root->emptyLavaOrPlayer(boardX, boardY - 1)))
            moveTime.restart();
        return 0;
    }
    else
    {
        moveTime.restart();
        root->issueEvent(this, 301);
        return 1;
    }
}
bool Lava::cornerStillExists()
{
    switch(lastAdjWall){
        case 0:
            if(lastDirection == 3)
                return !root->emptyLavaOrPlayer(boardX +1, boardY +1);
            else
                return !root->emptyLavaOrPlayer(boardX +1, boardY -1);
        case 1:
            if(lastDirection == 0)
                return !root->emptyLavaOrPlayer(boardX -1, boardY +1);
            else
                return !root->emptyLavaOrPlayer(boardX +1, boardY +1);
        case 2:
            if(lastDirection == 3)
                return !root->emptyLavaOrPlayer(boardX -1, boardY +1);
            else
                return !root->emptyLavaOrPlayer(boardX -1, boardY -1);
        case 3:
            if(lastDirection == 0)
                return !root->emptyLavaOrPlayer(boardX -1, boardY -1);
            else
                return !root->emptyLavaOrPlayer(boardX +1, boardY -1);
    }
}
void Lava::lavaExecMove()
{
    int countFree = 0;
    int currentMove = 0;
    bool freeTable[4] = {root->emptyLavaOrPlayer(boardX + 1, boardY), root->emptyLavaOrPlayer(boardX, boardY + 1), root->emptyLavaOrPlayer(boardX - 1, boardY), root->emptyLavaOrPlayer(boardX, boardY - 1)};

    for (int i = 0; i < 4; i++)
        if (freeTable[i])
        {
            countFree++;
        }
    if (lastAdjWall < 0)
    {

        if (countFree == 1)
        { // ball placed at the dead end
            for (int i = 0; i < 4; i++)
                if (freeTable[i])
                    currentMove = lastDirection = i;
            if (currentMove > 1)
                lastAdjWall = currentMove - 1;
            else
                lastAdjWall = currentMove + 1;
        }
        else if ((countFree == 3 || countFree == 2) && !freeTable[lastDirection])
        { //lava drops on the wall straight vertically
            lastAdjWall = lastDirection;
            int secondOption = lastAdjWall - 1 >= 0 ? lastAdjWall - 1 : 3;
            currentMove = freeTable[(lastAdjWall + 1) % 4] ? (lastAdjWall + 1) % 4 : secondOption;
            lastDirection = currentMove;
        }
        else if ((countFree == 3 || countFree == 2) && freeTable[lastDirection])
        { //lava reaches the wall parallel
            currentMove = lastDirection;
            int secondOption = currentMove - 1 >= 0 ? currentMove - 1 : 3;
            lastAdjWall = !freeTable[(currentMove + 1) % 4] ? (currentMove + 1) % 4 : secondOption;
        }
    }
    else
    {

        if ((countFree == 2 || (countFree == 3 && !freeTable[lastAdjWall])) && freeTable[lastDirection])
        { //Case when we follow a straight wall or inside a tunnel 1 segment width
            currentMove = lastDirection;
        }
        else if ((countFree == 2 || countFree == 3 || countFree == 4) && freeTable[lastAdjWall])
        { // case when we were following the wall and then it bend away
            if(cornerStillExists()){
                currentMove = lastAdjWall;
                if (lastDirection > 1)
                {
                    lastAdjWall = lastDirection - 2;
                }
                else
                    lastAdjWall = lastDirection + 2;
                lastDirection = currentMove; //for next iteration
            } else{
                currentMove = lastDirection;
            }
        }
        else if (countFree == 2 && !freeTable[lastDirection] && !freeTable[lastAdjWall])
        { //corner blocking the way
            lastAdjWall = lastDirection;
            int secondOption = lastAdjWall - 1 >= 0 ? lastAdjWall - 1 : 3;
            currentMove = freeTable[(lastAdjWall + 1) % 4] ? (lastAdjWall + 1) % 4 : secondOption;
            lastDirection = currentMove;
        }
        else if (countFree == 1)
        { //dead end
            if (lastDirection > 1)
            {
                currentMove = lastDirection - 2;
            }
            else
                currentMove = lastDirection + 2;
            if (lastAdjWall > 1)
                lastAdjWall -= 2;
            else
                lastAdjWall += 2;

            lastDirection = currentMove;
        }
    }

    int newX;
    int newY;

    switch (currentMove)
    {
    case 0:
        newX = boardX + 1;
        newY = boardY;
        break;
    case 1:
        newX = boardX;
        newY = boardY + 1;
        break;
    case 2:
        newX = boardX - 1;
        newY = boardY;
        break;
    case 3:
        newX = boardX;
        newY = boardY - 1;
    }
    if (!root->elements[newX][newY])
    {
        putOnTheBoard(newX, newY);
    }
    else
    {
        root->elements[newX][newY]->objectEnter(this, currentMove);
    }
    if(invisible){
        invisible = false;
        root->elements[newX][newY] = this;
    }
}
 int Lava::objectEnter(EventAwareSprite* another ,int direction){
    if(dynamic_cast <Lava*>(another)){
        root->elements[boardX][boardY] = nullptr;
        another->putOnTheBoard(boardX,boardY);
        invisible = true;
    }
    
};