#include "Event.h"
bool Event::checkEvent(){
    int result = affected->eventCheck(code);
    if(result == -1){
        return true;
    }
    else if(result == 1){
        affected->eventExecute(code);
        return true;
    }
    return false;
} //if false then event is still necessary. If true than we can remove it