
#ifndef EVENTH
#define EVENTH

#include "./objects/Eventaware.h"
#include <iostream>
using namespace std;

class EventAwareSprite;

class Event{
    int code;
    EventAwareSprite* affected;
    // Check function might return -1 aborted 0 not yet 1 fire 
public:
    Event(int code, EventAwareSprite* affected) : code(code), affected(affected){

    }
    bool checkEvent();
};

#endif