#ifndef CTEXTH
#define CTEXTH

#include <SFML/Graphics.hpp> 
#include <string>
using namespace std;

class CasualText : public sf::Text{
protected:
    const int TEXT_SIZE = 18;
    const sf::Color TEXT_COLOR;

public:
    CasualText() : TEXT_COLOR(255,255,255,255){}
    void construct(sf::Font& f, sf::Vector2f pos){
        setFillColor(TEXT_COLOR);
        setCharacterSize(TEXT_SIZE);
        setFont(f);
        setPosition(pos);
    }

};

class AlertBox : public CasualText{
    bool visible = false;
public:
    AlertBox() : CasualText(){}
    void construct(sf::Font& f, sf::Vector2f pos){
        CasualText::construct(f,pos);
    }
    bool isVisible(){return visible;}
    void display(string text){
        visible = true;
        setString(text);
    }
    void hide(){
        visible = false;
        setString("");
    }

};

#endif