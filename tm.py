
import numpy as np

class Machine:
    def __init__(self, alphabet, blank, states, init_q, halt, tape):
        self.alphabet = alphabet
        self.blank = blank
        self.states = states
        self.init_q = init_q
        self.halt = halt
        self.tape = tape


class State:
    def __init__(self, symb1, symb2, move, next_q):
        self.symb1 = symb1
        self.symb2 = symb2
        self.move = move
        self.next_q = next_q

if __name__ == '__main__':
    from parse import Parser
    parser = Parser('bb.tm')
    
    alphabet = [0, 1]
    blank = 0
    states = parser.parse_states()
    init_q = 'A'
    halt = 'H'
    tape = np.array([])

    machine = Machine(alphabet, blank, states, init_q, halt, tape)
    
