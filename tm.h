#define m 2
#define n 3


struct Cell{
    int val; //cell value (must be in Machine->alphabet)
    struct Cell *right; //right cell
    struct Cell *left; //left cell
};

struct State{
    char q; //state letter
    int symb1; //input symbol
    int symb2; //output symbol
    int move; // move direction
    char next_q; //next state letter
};

struct Head{
    struct Cell* cell; //current position
    struct State state; //current state
};

struct Machine{
    int alphabet[m]; //alphabet array (i.e [0,1])
    int blank; //blank symbol (i.e 0)
    struct State states[m*n]; //array of State
    char init_q; //init State letter (i.e 'A')
    char halt; //halt State letter (i.e 'H')
    //struct Head *head;
    struct Cell* cell; //initial empty tape (i.e Cell->val = 0)
};


extern void insertStart(struct Cell** headCell, struct Cell** cell);

extern void insertEnd(struct Cell** headCell, struct Cell** cell);

extern void parseState(struct State* state, const char* unparsedState);

extern struct State retrieveState(int l, struct State states[], char q, int symb1);

extern void evalState(int l, struct Machine* machine, struct Head* tapeHead, int blank);

extern int sumTape(struct Cell** headCell);

extern void printTape(int i, struct Cell* headCell);

extern void runTape(int l, const char** unparsedStates);