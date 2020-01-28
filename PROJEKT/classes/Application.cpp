#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Application.h"
#include "Board.h"

Application::Application() : appWindow(sf::VideoMode(800, 600), "Boulder Dash"),
                actualBoardNum(1), boardView(sf::FloatRect(-32, -32, 800, 562.5)),
                menuView(sf::FloatRect(-832, -632, 800, 600)), appView(sf::FloatRect(0,0,800,600)),
                background(TextureManager::getBackgroundTexture())
{
    loadBoardsFromTheFolder("./boards");
    if (!globalFont.loadFromFile("./assets/Lato-Light.ttf"))
    {
        corrupt = true;
        return;
    }
    appWindow.setFramerateLimit(40);
    boardView.setViewport(sf::FloatRect(0, 0.0625f, 1, 0.9375f));
    menuView.setViewport(sf::FloatRect(0, 0, 1, 1));
    appView.setViewport(sf::FloatRect(0,0,1,1));
    background.setPosition(-832, -632);
    background.setTextureRect({0, 0, 800, 600});
    alertBox.construct(globalFont, sf::Vector2f(-816, -64));
    SB = new StartButton(sf::Vector2f(355,275),sf::Vector2f(90,50),globalFont,this);
    EX = new ExitButton(sf::Vector2f(360,345),sf::Vector2f(80,50),globalFont,this);
};

bool Application::listen(){
    while(appWindow.isOpen()){
        if(readyToExit)
            return true;
        appWindow.display();
        appWindow.clear(sf::Color(0,0,0));
        if(state == BOARDS)
            listenBoard();
        else
            listenMenu();
    }
}

void Application::listenBoard(){
    int finishLevelTrig = 0;
    while(appWindow.pollEvent(appEvent)){
        switch(appEvent.type){
            case sf::Event::KeyPressed:
                if(appEvent.key.code == sf::Keyboard::Escape){
                    finishLevelTrig = -1;
                }
                if(appEvent.key.code == sf::Keyboard::D)
                    currentBoard->movePlayer(0);
                if(appEvent.key.code == sf::Keyboard::W)
                    currentBoard->movePlayer(1);
                if(appEvent.key.code == sf::Keyboard::A)
                    currentBoard->movePlayer(2);
                if(appEvent.key.code == sf::Keyboard::S)
                    currentBoard->movePlayer(3);
                if(appEvent.key.code == sf::Keyboard::R && currentBoard->initRestart())
                    finishLevelTrig = 2;                    
                if(appEvent.key.code == sf::Keyboard::C && currentBoard->isReadyToFinish())
                    finishLevelTrig = 1;
                break;
            case sf::Event::KeyReleased:
                if(appEvent.key.code == sf::Keyboard::D)
                    currentBoard->abortHoldingKey();
                if(appEvent.key.code == sf::Keyboard::A)
                    currentBoard->abortHoldingKey();
        }
    }
    
    
    appWindow.setView(menuView);
        appWindow.draw(background);
        appWindow.draw(*PI);
        PI->updateTimer();
        if(alertBox.isVisible()) appWindow.draw(alertBox);
    appWindow.setView(boardView);
        appWindow.draw(*currentBoard); 
    currentBoard->checkEvents();
    if(finishLevelTrig == 1)
        loadNextBoard();
    else if (finishLevelTrig == -1)
        abortGame();
    else if (finishLevelTrig == 2)
        currentBoard->boardReload();
}

void Application::listenMenu(){
    while(appWindow.pollEvent(appEvent)){
        switch(appEvent.type){
            case sf::Event::MouseButtonPressed:
                SB->checkIfHovered(sf::Vector2f(appEvent.mouseButton.x,appEvent.mouseButton.y));
                EX->checkIfHovered(sf::Vector2f(appEvent.mouseButton.x,appEvent.mouseButton.y));
        }
    }

    appWindow.setView(appView);
        appWindow.draw(*SB);
        appWindow.draw(*EX);
}

void Application::loadBoardsFromTheFolder(string folderName){ //loads as many boards as there are in the folder
    int i = 1;
    Board* toAdd;
    do{
        toAdd = new Board(folderName+"/"+to_string(i),this);
        if(*toAdd){ //bool conversion operator
            boards.push_back(toAdd);
            i++;
        }else{
            delete toAdd;
            break;
        }

    }while(true); 
    boardsNum = i-1; //further check if there are no boards
}

void Application::startGame(){
    boardIterator = boards.begin();
    currentBoard = *(boardIterator);
    currentBoard->loadBoardFromSymbolics();
    PI = new PlayrunInterface(globalFont, sf::Vector2f(-820, -630), currentBoard->getRuntime(),this);
    state = BOARDS;
}

void Application::abortGame(){
    delete PI;
    PI = nullptr;
    alertBox.hide();
    currentBoard->wipeBoardData();
    state = MENUS;
}

bool Application::loadNextBoard(){
    alertBox.hide();
    currentBoard->wipeBoardData();
    boardIterator++;
    if(boardIterator == boards.end()){
        state = MENUS;
        PI = nullptr;
        delete PI;
        return false;
    }
    currentBoard = *(boardIterator);
    currentBoard->loadBoardFromSymbolics();
    PI->updateStartScore();
    PI->resetTimer(currentBoard->getRuntime());
    PI->incBoardNum();
    return true;
}

Application::~Application(){
    if(PI)
       delete PI;
    if(SB)
        delete SB;
    if(EX)
        delete EX;
    list<Board *>::const_iterator iterator;
    for (iterator = boards.begin(); iterator != boards.end(); ++iterator)
    {
        delete (*iterator);     
    }
}

bool Application::areThereMoreBoards(){
    list<Board *>::const_iterator iterator;
    iterator = boardIterator;
    ++iterator;
    if(iterator == boards.end())
        return false;
    else
    {
        return true;
    }
    
}