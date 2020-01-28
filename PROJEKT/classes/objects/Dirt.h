
#ifndef DIRTH
#define DIRTH

#include "Eventaware.h"
using namespace std;


class Dirt : public EventAwareSprite{
    TextureManager& innerTexture;
    public:
        Dirt(int x, int y, Board* root) : EventAwareSprite(x,y,root), innerTexture(TextureManager::getTextureDirt()){
            setTexture(innerTexture);
        };
        int objectEnter(EventAwareSprite* another ,int direction){root->elements[boardX][boardY] = nullptr; delete this; return 1;};
        virtual int eventCheck(int code){return -1;} //not a single event really concerns dirt
         // check function, whether an event with a code for example 101 can fire or not. Also detects the situation when the event isn't needed anymore
        virtual void eventExecute(int code){}
        virtual bool acceptEvent(int code){return false;}
        // Function to execute in case of an event with int code   
};

#endif