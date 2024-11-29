#include "../tm.h"
#include <stdio.h>
//#define DEBUG 1

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
        int i;
        char* unparsedStates[100]={
            "A 0 1 1 B",
        };


        char* remainingStates[100] = {
           "A 1 1 -1 C",
            "B 0 1 -1 A",
            "B 1 1 1 B",
            "C 0 1 -1 B",
            "C 1 1 1 H" 
        };

        //runTape(l, unparsedStates);
        
        int l = 6; //(sizeof(unparsedStates)+sizeof(remainingStates))/sizeof(unparsedStates[0]);
        int unp_l = 1; //len of current array of unparsed states (variable)
        int rem_l = l-unp_l; //len of array of remaining states
        

        while (unp_l <= l){ 
            runTape(unp_l, unparsedStates);
            
            unparsedStates[unp_l] = remainingStates[0];//(sizeof(unparsedStates)/sizeof(unparsedStates[0]))-unp_l];
            remainingStates[0] = "";
            
            i = 1;
            while(i<rem_l){
                remainingStates[i-1] = remainingStates[i];
                i++;
            }
            
            rem_l--;
            unp_l++;
        }
        printf("All states been executed!\n");
    #endif

    return 0;
}