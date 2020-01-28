#include "Button.h"
void StartButton::click(){
    app->startGame();
}
void ExitButton::click(){
    app->exit();
}