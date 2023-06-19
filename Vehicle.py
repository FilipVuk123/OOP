class Vehicle:
    __slot__ = ["model_year","kilometers"]
    
    def __init__(self, model_year, kilometers):
        self.kilometers = kilometers
        self.model_year = model_year
    def drive(self, new_kilometers):
        self.kilometers += new_kilometers
        print("After {} kilometers, odometer redaing is {}".format(new_kilometers, self.kilometers))
    
class Car(Vehicle):
    def __init__(self, model_year, kilometers, nod):
        super().__init__(model_year, kilometers)
        self.number_of_doors = nod

class Motorcycle(Vehicle):
    def __init__(self, model_year, kilometers):
        super().__init__(model_year, kilometers)
    def ride_on_the_rear_wheel(self):
        print("Motorcycle rides on the rear wheel.")
   
if __name__ == "__main__":
    ElectricBike = Vehicle(2018, 0)
    ElectricBike.drive(47)
    ElectricBike.drive(35)
    M = Motorcycle(2015, 150000)
    M.ride_on_the_rear_wheel()
    M.drive(25)
    C = Car(2017, 10000, 5)
    print(C.number_of_doors)
    