#ifndef BUTTONH
#define BUTTONH

#include <SFML/Graphics.hpp>
#include "CasualText.h"
#include "../Application.h"

class Application;
class Button : public sf::Drawable{
    protected:
    CasualText innerText;
    sf::RectangleShape innerShape;
    sf::Font& innerFont;
    public:
        Button(sf::Vector2f pos, sf::Vector2f size, sf::Font& f) : innerFont(f), innerShape(size){
            innerShape.setPosition(pos);
            innerShape.setFillColor(sf::Color(153, 122, 28));
            innerText.construct(innerFont,sf::Vector2f(pos.x+17,pos.y+13));
        }
        bool checkIfHovered(sf::Vector2f cPos){ //cursor Position
            sf::Vector2f pos = innerShape.getPosition();
            sf::Vector2f size = innerShape.getSize();

            if(cPos.x >= pos.x && cPos.x <= pos.x+size.x && cPos.y >= pos.y && cPos.y <= pos.y+size.y){
                click();
                return true;
            }
            else
                return false;
        }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const{
            target.draw(innerShape);
            target.draw(innerText);
        }
        virtual void click()=0;
};

class StartButton : public Button{
    Application* app;
    public:
    StartButton(sf::Vector2f pos, sf::Vector2f size, sf::Font& f, Application* app) : Button(pos,size,f), app(app){
        innerText.setString("START");
    }
    void click();
};

class ExitButton : public Button{
    Application* app;
    public:
    ExitButton(sf::Vector2f pos, sf::Vector2f size, sf::Font& f, Application* app) : Button(pos,size,f), app(app){
        innerText.setString("EXIT");
    }
    void click();
};

#endif