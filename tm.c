#include "tm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//#define DEBUG 1

#define ALPHABET {0,1}
#define BLANK 0
#define INIT_Q 'A'
#define HALT_Q 'H'

struct Cell* createCell(int val){
    struct Cell* cell = (struct Cell*)malloc(sizeof(struct Cell));
    if (cell == NULL){
        printf("MEM ALLOC ERROR\n");
        exit(1);
    }

    cell->val = val;
    cell->left = (struct Cell *) NULL;
    cell->right = (struct Cell *) NULL;

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

void parseState(struct State* state, const char* unparsedState){
    sscanf(unparsedState, "%c %d %d %d %c", &(state->q), &(state->symb1), &(state->symb2), &(state->move), &(state->next_q));
}

struct State retrieveState(int l, struct State states[], char q, int symb1){
    struct State state;
    for (int i =0; i < l; i++){ 
        state = states[i];
        if (state.q == q && state.symb1 == symb1){
            return state;
        }
    }

    state.q = '\0';
    return state;
}

void evalState(int l, struct Machine* machine, struct Head* tapeHead, int blank){
    struct Cell* cell = (*tapeHead).cell;
    struct State state = (*tapeHead).state;

    #ifdef DEBUG
        printf("state: q=%c, symb1=%d, symb2=%d, move=%d, next_q=%c\n",
            state.q, state.symb1, state.symb2, state.move, state.next_q);
    #endif

    if (state.move == -1 && cell->left == NULL){
        #ifdef DEBUG
            printf("cell->left is NULL\n");
        #endif

        struct Cell* blankCell = createCell(blank);
        insertStart(&cell, &blankCell);

        machine->cell = blankCell; 
    } else if (state.move == 1 && cell->right == NULL){
        #ifdef DEBUG
            printf("cell->right is NULL\n");
        #endif

        struct Cell* blankCell = createCell(blank);
        insertEnd(&cell, &blankCell);
    }

    #ifdef DEBUG
        printf("cell->val (before) = %d\n", cell->val);
    #endif

    cell->val = state.symb2;
    
    #ifdef DEBUG
        printf("cell->val (after) = %d\n", cell->val);
    #endif

    if (state.move == -1){
        (*tapeHead).cell = cell->left;
        #ifdef DEBUG
            printf("moved left\n");
        #endif
    } else if (state.move == 1){
        (*tapeHead).cell = cell->right;
        #ifdef DEBUG
            printf("moved right\n");
        #endif
    }

    if (state.next_q != 'H'){
        (*tapeHead).state = retrieveState(l, machine->states, state.next_q, (*tapeHead).cell->val);
    } else{
        (*tapeHead).state.q = 'H';
    }
}

int sumTape(struct Cell** headCell){
    int sum = 0;
    struct Cell* current = *headCell;

    while (current != NULL){
        sum += current->val;
        current = current->right;
    }

    return sum;
}

void printTape(int i, struct Cell* headCell) {
    struct Cell* current = headCell;
    printf("tape %d: ", i+1);
    while (current != NULL) {
        printf("%d, ", current->val);
        current = current->right;
    }
    printf("NULL\n\n");
}

void runTape(int l, const char** unparsedStates){
    clock_t st = clock(); 
    struct Machine machine;

    int alphabetArr[m] = ALPHABET;
    for (int i = 0; i < m; i++){
        machine.alphabet[i] = alphabetArr[i];
    }

    machine.blank = BLANK;

    for (int i = 0; i < l; i++) {
        #ifdef DEBUG
            printf("unparsed state at index %d: %s\n", i, unparsedStates[i]);
        #endif
        struct State state = machine.states[i];
        parseState(&machine.states[i], unparsedStates[i]);
    } 

    machine.init_q = INIT_Q;
    machine.halt = HALT_Q;
    
    machine.cell = createCell(machine.blank);

    struct Head tapeHead;
    tapeHead.cell = machine.cell;
    tapeHead.state = retrieveState(l, machine.states, machine.init_q, machine.cell->val); 

    int i = 0;
    while (!(tapeHead.state.q == '\0' || tapeHead.state.q == machine.halt)){
        evalState(l, &machine, &tapeHead, machine.blank);
        printTape(i, machine.cell);
        ++i;
    }

    int sum = sumTape(&machine.cell);
    clock_t et = clock();

    printf("steps: %d\n", i);
    printf("tape sum: %d\n", sum);

    printf("--------------------------\nexecution time: %fs\n--------------------------\n\n", (double)(et-st)/CLOCKS_PER_SEC);
}