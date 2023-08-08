
class Parser:
    def __init__(self, file):
        self.unparsed_states = open(file, 'r').readlines()
    
    def parse_states(self):
        from tm import State
        states = {}
        for st in self.unparsed_states:
            st = st.strip().split(' ')
            if st[0] not in states.keys():
                states[st[0]] = []
                
            states[st[0]].append(State(*[int(x) if x in "0123456789" else str(x) for x in st[1:]]))
        
        return states