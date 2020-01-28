
#ifndef EVENTAWAREH
#define EVENTAWAREH
#include <SFML/Graphics.hpp>
#include <string>
#include "../Board.h"

using namespace std;

// common interface for all of the tiles on the board
class Board;
class EventAwareSprite : public sf::Sprite{
    protected:
        const static int GRID_SIZE = 32;
        int boardX, boardY;
        Board* root;
    public:
        EventAwareSprite(int x, int y, Board* root_):boardX(x),boardY(y), root(root_){
            setPosition(calculatePositionVector(x,y));
            setOrigin(GRID_SIZE*0.5,GRID_SIZE*0.5);
        }
        virtual int objectEnter(EventAwareSprite* another, int direction)=0; 
        virtual int eventCheck(int code)=0;
         // check function, whether an event with a code for example 101 can fire or not. Also detects the situation when the event isn't needed anymore
        virtual void eventExecute(int code)=0;
        // Function to execute in case of an event with int code
        virtual bool acceptEvent(int code){return true;}
        // Optional Function used as an event filter
        sf::Vector2f calculatePositionVector(int x, int y){
            return sf::Vector2f(x*GRID_SIZE, y*GRID_SIZE-0.5);
        }
        void putOnTheBoard(int x, int y);
        int getX(){return boardX;}
        int getY(){return boardY;}
        sf::Vector2i getCoords(){return sf::Vector2i(boardX,boardY);}
   
};

#include "Player.h" // Player.h Eventaware.h Board.h are interconnected. If you want to include Eventaware, you must include Player.h which HAS TO be after Eventaware.h because of inhertance model

#endif