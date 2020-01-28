
#ifndef LAVAH
#define LAVAH

#include "Eventaware.h"
using namespace std;


class Lava : public EventAwareSprite{
    TextureManager& innerTexture;
    sf::Clock moveTime;
    int MOVE_CONST;
    bool frozen = false;
    bool invisible = false;
    int lastDirection = 0;
    int lastAdjWall = -1;
    int lavaCheckMove();
    void lavaExecMove();
    bool cornerStillExists();
    public:
        void freeze(){frozen=true;}
        Lava(int x, int y, Board* root) : EventAwareSprite(x,y,root), innerTexture(TextureManager::getTextureLava()){
            setTexture(innerTexture);
        };
        int objectEnter(EventAwareSprite* another ,int direction);
        virtual int eventCheck(int code){
            switch (code)
            {
            case 301:
                return lavaCheckMove();
                break;
            
            default:
                return -1;
            }
        }
         // check function, whether an event with a code for example 101 can fire or not. Also detects the situation when the event isn't needed anymore
        virtual void eventExecute(int code){
            switch (code)
            {
            case 301:
                return lavaExecMove();
            
            }
        }
        virtual bool acceptEvent(int code){
            if(code == 301){
                return true;
            }
            return false;
        }
        // Function to execute in case of an event with int code   
};

#endif