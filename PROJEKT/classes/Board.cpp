#include "Board.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> 
#include "./objects/Bedrock.h"
#include "./objects/Stone.h"
#include "./objects/Dirt.h"
#include "./objects/Diamond.h"
#include "./objects/Chest.h"
#include "./objects/Lava.h"

#include <iostream>
using namespace std;

void Board::loadBoardFromSymbolics()
{
    vector<EventAwareSprite*> lavaToFire;
    elements = new EventAwareSprite **[boardSize.x];

    for (int i = 0; i < boardSize.x; i++)
    {

        elements[i] = new EventAwareSprite *[boardSize.y];

        for (int j = 0; j < boardSize.y; j++)
        {
            switch (startingPoint[j][i])
            {
            case 'E':
                elements[i][j] = new Dirt(i, j, this);
                break;
            case 'L':
                elements[i][j] = new Lava(i, j, this);
                lavaToFire.push_back(elements[i][j]);
                break;
            case 'D':
                elements[i][j] = new Diamond(i, j, this);
                break;
            case 'S':
                elements[i][j] = new Stone(i, j, this);
                break;
            case '@':
                elements[i][j] = new Chest(i, j, this);
                break;
            case '_':
                elements[i][j] = nullptr;
                break;
            case '!':
                player = new Player(i, j, this);
                elements[i][j] = player;
                break;
            case 'B':
                elements[i][j] = new Bedrock(i, j, this);
            }
        }
    }
    for(int i = 0; i < lavaToFire.size(); i++){
        issueEvent(lavaToFire[i],301);
    }
}

bool Board::emptyLavaOrPlayer(int x, int y){
    if(!elements[x][y])
        return true;
    else if(player->getCoords() == sf::Vector2i(x,y))
        return true;
    if(dynamic_cast <Lava*>(elements[x][y]))
        return true;
    return false;
}

void Board::wipeBoardData()
{
    if(!elements)
        return; //if dynamic table wasn't created there is nothing to be removed!
    for (int i = 0; i < boardSize.x; i++)
    {
        for(int j = 0; j < boardSize.y; j++){
            if(elements[i][j])
                delete elements[i][j];
            elements[i][j] = nullptr;
        }
        delete[] elements[i];
        elements[i] = nullptr;
    }
    delete[] elements;
    elements = nullptr;
    eventList.clear();
}

void Board::boardReload()
{
    wipeBoardData();
    loadBoardFromSymbolics();
}

bool Board::loadSymbolicsFromFile(string pathToBoard, bool dropToConsole){
    ifstream loadedMap(pathToBoard);
    if (!loadedMap)
        return false;

    string line;
    int numLine = 0;
    int mapLength = 0;

    //Detect board time - first line in the file

    loadedMap >> boardRuntime;

    while (loadedMap >> line)
    { // first loop - length + height detector + verifier

        numLine++;
        startingPoint.push_back(vector<char>());
        int numRow = 0;

        stringstream reader(line);
        char object;
        while (reader >> object)
        {
            numRow++;

            //check if object is a valid symbol
            if (object != '!' && object != '?' && object != '_' && object != 'B' && object != 'E' && object != 'S' && object != 'D' && object != '@' && object != 'L')
            {
                loadedMap.close();
                return false;
            }

            startingPoint[numLine - 1].push_back(object);
        }
        if (dropToConsole)
            cout << line << endl;

        if (numLine == 1)
            mapLength = numRow;
        else if (numRow != mapLength) //check if width is consistent
            return false;
    }

    boardSize.y = numLine;
    boardSize.x = mapLength;
    successfullyLoaded = true;
    return true;
}

bool Board::loadFromFile(string pathToBoard, bool dropToConsole)
{ //load using stringstreams. Returns false if something goes wrong, true otherwise

    /* Loading assumes that the board has width of the first row in the file 
        It will read all the rows, so the number of rows is the height 
        If any row has insufficient width, error will be thrown
        Error will be thrown if any non-normal symbols are found
        The first while loop will build the char-table and verify the integrity of the board. If it's good it will proceed.
        The second loop will build the dynamic objects for the board and fill this->elements
    */

   if(!loadSymbolicsFromFile(pathToBoard,dropToConsole))
        return false;

    //stage 2 - load the symbolics to the objects in the elements***

    loadBoardFromSymbolics();

    return true;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < boardSize.x; i++)
    {

        for (int j = 0; j < boardSize.y; j++)
        {
            if (elements[i][j])
                target.draw(*elements[i][j], states);
        }
    }
}

void Board::movePlayer(int direction)
{
    if (!player->canMove())
        return;

    player->faceDirection(direction);
    sf::Vector2i pCoords = player->getCoords();
    sf::Vector2i oldCoords(pCoords.x, pCoords.y);

    switch (direction)
    {
    case 0:
        pCoords.x += 1;
        break;
    case 1:
        pCoords.y -= 1;
        break;
    case 2:
        pCoords.x -= 1;
        break;
    case 3:
        pCoords.y += 1;
        break;
    }
    int moveStatus;
    if (elements[pCoords.x][pCoords.y])
    {
        moveStatus = elements[pCoords.x][pCoords.y]->objectEnter(player, direction);
    }
    else
        moveStatus = 1;
    if (moveStatus == 1)
    {
        player->putOnTheBoard(pCoords.x, pCoords.y);

        player->emitEventsAfterMove(oldCoords.x, oldCoords.y, direction);
    }
}
void Board::abortHoldingKey()
{
    if (player->isPushing())
        player->abortPush();
}

bool Board::issueEvent(EventAwareSprite *receipent, int code)
{
    
    if (receipent && receipent->acceptEvent(code))
    {
        eventList.push_back(new Event(code, receipent));
        return true;
    }
    return false; // rejected
};

void Board::checkEvents()
{
    list<Event *>::const_iterator iterator;
    for (iterator = eventList.begin(); iterator != eventList.end(); ++iterator)
    {
        if ((*iterator)->checkEvent())
        {
            iterator = eventList.erase(iterator);
        }
    }
};

bool Board::initRestart()
{
    if (player->isDead() && app->PI->ableToContinue())
    {
        app->PI->reloadOnDeath();
        app->alertBox.hide();
        return true;
    }
    return false;
}

bool Board::isReadyToFinish()
{
    if (player->isImmune())
        return true;
}

void Board::win()
{
    player->playerWin();
    app->PI->addTimerScore();
    if(app->areThereMoreBoards())
        app->alertBox.display("You have won! Press C to continue to the next board");
    else
        app->alertBox.display("Game complete! Press C to finish. Your score is: " + to_string(app->PI->getScore()));
    app->PI->blockTimerUpdate();
}
void Board::timerIsUp() { 
    issueEvent(player, 201);
}