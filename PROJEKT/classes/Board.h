#ifndef BOARDH
#define BOARDH

#include <SFML/Graphics.hpp>
#include <string>
#include "./objects/Eventaware.h"
#include <list>
#include "Event.h"
#include "Application.h"
using namespace std;

class EventAwareSprite;
class Player;
class Event;
class Application;

class Board : public sf::Drawable{
friend class Player;
friend class EventAwareSprite;
friend class Dirt;
friend class Stone;
friend class Diamond;
friend class Chest;
friend class Lava;
private:
    int boardRuntime = 20; //DEFAULT
    Application* app;
    list <Event*> eventList;
    string pathToBoard;
    sf::Vector2i boardSize;
    EventAwareSprite*** elements; //2 dimensional array consisting of POINTERS to various sprites - from the player to tile elements
    vector <vector <char>> startingPoint;
    Player* player;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool successfullyLoaded = false;
public:
    bool emptyLavaOrPlayer(int x, int y);
    int getRuntime(){return boardRuntime;}
    void loadBoardFromSymbolics();
    bool loadSymbolicsFromFile(string pathToBoard, bool dropToConsole = false);
    void boardReload();
    bool initRestart();
    bool isReadyToFinish();
    void wipeBoardData();
    void win();
    bool issueEvent(EventAwareSprite* recipent, int code );
    void checkEvents();
    bool loadFromFile(string pathToBoard, bool dropToConsole = false);
    Board(string pathToBoard, Application* root) : app(root), pathToBoard(pathToBoard){loadSymbolicsFromFile(pathToBoard);};
    inline operator bool(){return successfullyLoaded;}
    void abortHoldingKey();
    void timerIsUp();
    void movePlayer(int direction); //direction 0 - right 1 - up 2 - left 3 - down. Called from application
    // needs to be initialized in loadFromFile. File could be corrupted/missing so the state variable must exist
    ~Board(){
        wipeBoardData();
    }
};

#endif