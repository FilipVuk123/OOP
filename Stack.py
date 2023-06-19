from queue import Queue

class Stack:
    def __init__(self):
        self.c = Queue()
        self.help = Queue()
        
    def push(self, x):
        self.c.put(x)
    def pop(self):
        if not self.c.empty():
            while (self.c.qsize > 1):
                self.help.put(self.c.get())
            to_return = self.c.get()
            
            while not self.help.empty():
                self.c.put(self.help.get())
            
            return to_return
        else:
            return None
    def empty(self):
        return self.c.empty()
    
if __name__== "__main__":
    s = Stack()
    s. push(1)
    s. push(2)
    s. push(3)
    s.pop()
    s. push(1)
    