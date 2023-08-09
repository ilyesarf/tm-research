
import numpy as np

class Machine:
    def __init__(self, alphabet, blank, states, init_q, halt, tape):
        self.alphabet = alphabet
        self.blank = blank
        self.states = states
        self.init_q = init_q
        self.halt = halt
        self.tape = tape

    def eval_state(self, state, ind):
        if ind > len(self.tape)-1:
            self.tape = np.append(self.tape, self.blank)
        elif ind == -1:
            self.tape = np.insert(self.tape, 0, self.blank)
            ind = 0
        elif ind < -1:
            print(ind)
            exit(1)

        symb_st = [st for st in self.states[state] if st.symb1 == self.tape[ind]][0] #symbol-specific state
        self.tape[ind] = symb_st.symb2
        
        if symb_st.move == 'L':
            ind -= 1
        elif symb_st.move == 'R':
            ind += 1

        return symb_st.next_q, ind


class State:
    def __init__(self, symb1, symb2, move, next_q):
        self.symb1 = symb1
        self.symb2 = symb2
        self.move = move
        self.next_q = next_q

if __name__ == '__main__':
    from parse import Parser
    parser = Parser('bb.yml')
    
    tape = np.array([0])

    machine = Machine(parser.alphabet, parser.blank, parser.states, parser.init_q, parser.halt, tape)

    state, ind = parser.init_q, 0
    i = 0
    while True:
        print("state: ", state)
        print("head position: ", ind)
        print("current tape: ", machine.tape)
        print()
        #print(i)
        if state != 'H':
            state,ind = machine.eval_state(state, ind)
            i += 1
        else:
            print("total steps: ", i)
            print("sum: ", np.sum(machine.tape))
            exit(0)
