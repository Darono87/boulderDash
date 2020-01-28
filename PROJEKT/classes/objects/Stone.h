
#ifndef STONEH
#define STONEH

#include "Eventaware.h"
using namespace std;


class Stone : public EventAwareSprite{
    TextureManager& innerTexture;
    int readyToFall(); 
    int readyToSlip();
    void stoneSlip();
    void fallVert();
    sf::Clock fallTimer;
    sf::Clock slipTimer;
    bool isFalling = false;
    bool isSlipping = false;
    const int STONE_FALL_TIME = 200;
    const int STONE_SLIP_TIME = 200;
    int slipDirection = -1;
    public:
        Stone(int x, int y, Board* root) : EventAwareSprite(x,y,root), innerTexture(TextureManager::getTextureStone()){
            setTexture(innerTexture);
        };
        int objectEnter(EventAwareSprite* another ,int direction);  
        int eventCheck(int code){
            switch(code){
                case 102:
                    return readyToFall(); //fire it after some time
                case 103:
                    slipDirection = 2;
                    return readyToSlip(); 
                case 104:
                    slipDirection = 0;
                    return readyToSlip();
                default:
                    return -1;
            }
        }
         // check function, whether an event with a code for example 101 can fire or not. Also detects the situation when the event isn't needed anymore
        void eventExecute(int code){
            switch(code){
                case 102: return fallVert();
                case 103:
                case 104: return stoneSlip();
            }
        }
        bool isItFalling(){return isFalling;}
        bool acceptEvent(int code);
        // Function to execute in case of an event with int code
};

#endif