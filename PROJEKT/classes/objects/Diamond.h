
#ifndef DIAMONDH
#define DIAMONDH

#include "Eventaware.h"
using namespace std;


class Diamond : public EventAwareSprite{
    const int DIAMOND_POINTS = 50;
    TextureManager& innerTexture;
    public:
        Diamond(int x, int y, Board* root) : EventAwareSprite(x,y,root), innerTexture(TextureManager::getTextureDiamond()){
            setTexture(innerTexture);
        };
        int objectEnter(EventAwareSprite* another ,int direction){
            root->elements[boardX][boardY] = nullptr; 
            root->app->PI->addPoints(DIAMOND_POINTS);
            delete this;
            return 1;
        };
        virtual int eventCheck(int code){return -1;}
         // check function, whether an event with a code for example 101 can fire or not. Also detects the situation when the event isn't needed anymore
        virtual void eventExecute(int code){}
        virtual bool acceptEvent(int code){return false;}
        // Function to execute in case of an event with int code   
};

#endif