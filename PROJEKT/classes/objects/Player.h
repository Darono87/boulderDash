
#ifndef PLAYERH
#define PLAYERH

#include <SFML/Graphics.hpp>
#include "../TextureManager.h"
#include "Stone.h"
#include "Lava.h"

class Lava;

class Player : public EventAwareSprite{
    TextureManager& innerTexture;
    TextureManager& pushTexture;
    TextureManager& deathTexture;
    sf::Clock pushTime;
    sf::Clock moveLimit;
    Stone* beingPushed = nullptr;
    int pushDirection = -1;
    int facingDirection = 0;
    bool pushAborted = false;
    bool moveBlock = false;
    bool dead = false;
    bool immune = false;
    int playerPushCheck();
    void playerPushExec();
    void pushRestart();
    void playerDie();
    public:
        Player(int x, int y, Board* root) : EventAwareSprite(x,y,root), deathTexture(TextureManager::getTextureDeath()), innerTexture(TextureManager::getTexturePlayer()), pushTexture(TextureManager::getPushTexture()){
            setTexture(innerTexture);
        };
        int objectEnter(EventAwareSprite* another ,int direction);
        
        void startPushing(Stone* which, int direction);
        void abortPush(){pushAborted = true;}
        void faceDirection(int direction){
            if(direction == 1 || direction == 3 || direction == facingDirection)
                return;
            else
                scale(-1,1);
            facingDirection = direction;
            
        }
        bool isPushing(){return beingPushed;}
        bool isDead(){return dead;}
        bool isImmune(){return immune;}
        int eventCheck(int code){
            switch(code){
                case 101: return playerPushCheck();
                case 201: return 1;
                default: return -1;
            }
        }
         // check function, whether an event with a code for example 101 can fire or not. Also detects the situation when the event isn't needed anymore
        void eventExecute(int code){
            switch(code){
                case 101: return playerPushExec();
                case 201: return playerDie();
            }
        }
        bool acceptEvent(int code){
            switch(code){
                case 101: return true;
                case 201: return true;
                default: return false;
            }
        }
        bool canMove(){ 
            int elapsed = moveLimit.getElapsedTime().asMilliseconds();
            if(elapsed > 100 && !moveBlock){
                moveLimit.restart();
                return true;
            }
            return false;
        }
        void playerWin(){
            moveBlock = true;
            immune = true;
        }
        void emitEventsAfterMove(int oldX, int oldY, int direction);
        // Function to execute in case of an event with int code
};

#endif