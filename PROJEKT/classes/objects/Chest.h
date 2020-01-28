
#ifndef CHESTH
#define CHESTH

#include "Eventaware.h"
using namespace std;


class Chest : public EventAwareSprite{
    int COMPLETE_SCORE = 200;
    TextureManager& innerTexture;
    public:
        Chest(int x, int y, Board* root) : EventAwareSprite(x,y,root), innerTexture(TextureManager::getTextureChest()){
            setTexture(innerTexture);
        };
        int objectEnter(EventAwareSprite* another ,int direction){
            root->elements[boardX][boardY] = nullptr;
            root->app->PI->addPoints(COMPLETE_SCORE);
            delete this;
            root->win();
            return 1;
        };
        virtual int eventCheck(int code){return -1;} //not a single event really concerns dirt
         // check function, whether an event with a code for example 101 can fire or not. Also detects the situation when the event isn't needed anymore
        virtual void eventExecute(int code){}
        virtual bool acceptEvent(int code){return false;}
        // Function to execute in case of an event with int code   
};

#endif