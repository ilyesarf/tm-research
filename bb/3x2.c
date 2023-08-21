#include "../tm.h"

int main(){
    const char* unparsedStates[]={
        "A 0 1 1 B",
        "A 1 1 -1 C",
        "B 0 1 -1 A",
        "B 1 1 1 B",
        "C 0 1 -1 B",
        "C 1 1 1 H",
    };
    
    runTape(unparsedStates);
}