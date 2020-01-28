#ifndef PLAYRUNH
#define PLAYRUNH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "CasualText.h"
#include "../Application.h"
#include <string>
using namespace std;

class Application;

class PlayrunInterface : public sf::Drawable
{
    int startScore = 0;
    bool blockTimer = false;
    bool timeIsUp=false;
    Application* app;
    const int BEAT_TIMER_SCORE = 300;
    const int NUM_LIFES = 3;
    int runTime;
    sf::Vector2f pos;
    const string lifesPrefix = "Lifes: ";
    const string scorePrefix = "Score: ";
    const string boardPrefix = "Board number ";
    const string timerPrefix = "Time left: ";
    int lifes;
    sf::Clock timeLeft;
    long long int score;
    int actualBoardNum;
    CasualText scoreText;
    CasualText boardText;
    CasualText lifesText;
    CasualText timerText;
    sf::Font& innerFont;
    int descreaseLifesAmmount();
    void constructTextInterface();

public:
    int getScore(){return score;}
    void updateStartScore(){startScore = score;}
    void reloadOnDeath();
    bool popLife();
    bool ableToContinue(){return lifes>=0;}
    PlayrunInterface(sf::Font& font, sf::Vector2f pos, int runTime_, Application* app);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void resetTimer(int runTime_);
    void updateTimer();
    void addPoints(int points);
    void addTimerScore();
    void incBoardNum(){
        actualBoardNum++;
        boardText.setString(boardPrefix + to_string(actualBoardNum));
    }
    void blockTimerUpdate(){blockTimer = true;}
    void unblockTimerUpdate(){blockTimer = false;}
};

#endif