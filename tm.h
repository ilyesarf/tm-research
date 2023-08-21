#define n 3
#define m 2

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
    struct State states[n*m]; //array of State
    char init_q; //init State letter (i.e 'A')
    char halt; //halt State letter (i.e 'H')
    //struct Head *head;
    struct Cell* cell; //initial empty tape (i.e Cell->val = 0)
};

void insertStart(struct Cell** headCell, struct Cell** cell);

void insertEnd(struct Cell** headCell, struct Cell** cell);

void parseState(struct State* state, const char* unparsedState);

struct State retrieveState(struct State states[], char q, int symb1);

void evalState(struct Machine* machine, struct Head* tapeHead, int blank);

int sumTape(struct Cell** headCell);

void printTape(int i, struct Cell* headCell);