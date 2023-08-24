#include "../tm.h"

int main(){
    /*const char* unparsedStates[]={
        "A 0 1 1 B",
        "A 1 1 -1 C",
        "B 0 1 -1 A",
        "B 1 1 1 B",
        "C 0 1 -1 B",
        "C 1 1 1 H"
    };*/

    const char* unparsedStates[]={
        "A 0 1 1 B",
        "B 0 1 -1 A",
        //"A 1 1 -1 C",
        //"B 1 1 1 B",
    };

    int l = 2; //len of current array of unpased states (variable)

    runTape(l, unparsedStates);
}