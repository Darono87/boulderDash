#ifndef APPH
#define APPH

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "./interface/PlayrunInterface.h"
#include "./interface/Button.h"
#include "Board.h"
#include <list>

class Board;
class PlayrunInterface;
class StartButton;
class ExitButton;

enum APP_STATE{MENUS,BOARDS};

class Application
{
    friend class Player;
    friend class Board;
    friend class Diamond;
    friend class Chest;
    friend class PlayrunInterface;

private:
    StartButton* SB;
    ExitButton* EX;
    APP_STATE state = MENUS;
    list <Board*> boards;
    int boardsNum;
    Board* currentBoard;
    list<Board*>::const_iterator boardIterator;
    sf::RenderWindow appWindow;
    sf::Event appEvent;
    sf::View appView;
    sf::View boardView;
    sf::View menuView;
    sf::Sprite background;
    sf::Font globalFont;
    AlertBox alertBox;
    PlayrunInterface* PI;
    int actualBoardNum;
    bool corrupt = false;
    bool readyToExit = false;

    void listenBoard();
    void listenMenu();
    void loadBoardsFromTheFolder(string folderName);
    void abortGame();

public:
    Application();
    bool listen();
    void startGame();
    bool loadNextBoard();
    bool areThereMoreBoards();
    void exit(){readyToExit=true;}
    ~Application();
};

#endif