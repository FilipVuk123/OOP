class Person:
    __slot__ = ["name","age"]
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def walk(self):
        print( "{} ({}) walks.".format(self.name, self.age))
    
    def say(self, message):
        print("{} says: {}.".format(self.name, message))
    
class Superhero(Person):
    __slot__ = ["secret_identity"]
    def __init__(self, s_i, name, age):
        self.secret_identity = s_i
        super().__init__(name, age)
    def fly(self):
        print("{} (aka {}) is flying.".format(self.name, self.secret_identity))
    def use_super_sight(self):
        print("{} (aka {}) uses super sight.".format(self.name, self.secret_identity))
    def walk(self, use_power = False):
        if use_power == True:
            print("{} (aka {}) uses extra_speed running.".format(self.name, self.secret_identity))
        else:
            super().walk()
    
if __name__ == "__main__":
    Osoba1 = Person("Mike", 31)
    Osoba1.walk()
    Osoba1.say("Hello World")
    s1 = Superhero("Dash", "Brzi", 14)
    s1.fly()
    s1.say("HI I'm Dash")
    s1.use_super_sight()
    s1.walk(True)
    