#include "../tm.h"

#define DEBUG 1

int main(){
    #ifdef DEBUG
        const char* unparsedStates[]={
            "A 0 1 1 B",
            "A 1 1 -1 C",
            "B 0 1 -1 A",
            "B 1 1 1 B",
            "C 0 1 -1 B",
            "C 1 1 1 H"
        };
        
        int l = 6; 
        runTape(l, unparsedStates);
    #endif

    #ifndef DEBUG
        const char* unparsedStates[]={
            "A 0 1 1 B",
            "B 0 1 -1 C",   
        };


        char* remainingStates[] = {
            "C 1 1 -1 B"
        };

        //runTape(l, unparsedStates);
        
        int l = 2; //len of current array of unpased states (variable)

        while (l <= (sizeof(unparsedStates)+sizeof(remainingStates))/sizeof(unparsedStates[0])){
            runTape(l, unparsedStates);
            unparsedStates[l] = remainingStates[(sizeof(unparsedStates)/sizeof(unparsedStates[0]))-l];
            ++l;
        }
    #endif
}