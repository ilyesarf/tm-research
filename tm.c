#include "tm.h"
#include <stdlib.h>
#include <stdio.h>

#define ALPHABET {0,1}
#define BLANK 0
#define INIT_Q 'A'
#define HALT 'H'

struct Cell* createCell(int val){
    struct Cell* cell = (struct Cell*)malloc(sizeof(struct Cell));
    if (cell == NULL){
        printf("MEM ALLOC ERROR");
        exit(1);
    }

    cell->val = val;
    cell->left = NULL;
    cell->right = NULL;

    return cell;
}

void insertStart(struct Cell** headCell, struct Cell** cell){
    (*headCell)->left = *cell;
    (*cell)->right = *headCell;
}

void insertEnd(struct Cell** headCell, struct Cell** cell){
    struct Cell* current = *headCell;
    while (current->right != NULL){
        current = current->right;
    }

    current->right = *cell;
    (*cell)->left = current;
}


void evalState(struct Head* tapeHead, int blank){
    struct Cell* cell = tapeHead->cell;
    struct State* state = tapeHead->state;
    if (&cell->left == NULL){
        struct Cell* blankCell = createCell(blank);
        insertStart(&cell, &blankCell);
    } else if (&cell->right == NULL){
        struct Cell* blankCell = createCell(blank);
        insertEnd(&cell, &blankCell);
    }
}

void parseState(struct State* state, const char* unparsedState){
    sscanf(unparsedState, "%c %d %d %d %c", &(state->q), &(state->symb1), &(state->symb2), &(state->move), &(state->next_q));
}

int main(){
    struct Machine machine;

    int alphabetArr[m] = ALPHABET;
    for (int i = 0; i < m; i++){
        machine.alphabet[i] = alphabetArr[i];
    }

    machine.blank = BLANK;
    
   const char* unparsedStates[]={
        "A 0 1 1 B",
        "A 1 1 -1 C",
        "B 0 1 -1 A",
        "B 1 1 1 B",
        "C 0 1 -1 B",
        "C 1 1 1 H",
    };
    for (int i = 0; i < n*m; i++) {
        struct State state = machine.states[i];
        parseState(&machine.states[i], unparsedStates[i]);
    } 

    machine.init_q = INIT_Q;
    machine.halt = HALT;
    
    struct Cell* initCell;
    initCell = createCell(machine.blank);
    
    return 0;
}