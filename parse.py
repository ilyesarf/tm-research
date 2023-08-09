
import yaml

class Parser:
    def __init__(self, file):
        self.data = yaml.safe_load(open(file, 'r'))
        self.alphabet = self.data['alphabet']
        self.blank = self.data['blank']
        self.init_q = self.data['init_state']
        self.halt = self.data['halt']
        self.states = self.parse_states(self.data['states'])

    def parse_states(self, unparsed):
        from tm import State
        states = {}
        for st in unparsed:
            st = eval(st)
            if st[0] not in states.keys():
                states[st[0]] = []

            states[st[0]].append(State(*st[1:]))
        
        return states