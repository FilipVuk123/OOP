#include <iostream>
#include <math.h>

using namespace std;

class IMU {
    private:
        double dx,dy,dz;
    public:
        IMU(double x, double y, double z): dx(x), dy(y), dz(z){};
        void measure(){
            dx = round((double) rand() / 10000);
            dy = round((double) rand() / 10000);
            dz = round((double) rand() / 10000);
        }
        friend ostream&operator<<(ostream& os, IMU& imu){
            os << "DX: " << imu.dx <<"  DY: " << imu.dy << " DZ: " << imu.dz << endl;
            return os;
        }
        friend class Car;     // Car and Dron -> sada pristupaju private clanovima IMUa... 
        friend class Drone;
};

struct Position{
    double x, y, z;
    Position(double x,double y,double z): x(x),y(y),z(z){}
};

class AutonomousVehicle{
    protected:
        IMU imu;
        Position pos;
    public:
        AutonomousVehicle(): imu(0.0, 0.0, 0.0), pos(0.0, 0.0, 0.0){};
        virtual void printDrive(ostream&) = 0;
        virtual void drive(double) = 0;

        friend ostream&operator<<(ostream& os, AutonomousVehicle& av){
            av.printDrive(os);
            return os;
        }
};  

class Car : public AutonomousVehicle{
    public:
        Car(): AutonomousVehicle(){}
        void printDrive(ostream& os){
            os << "Car at: " << "   x: " << pos.x << "  y: " << pos.y << "  z: " << pos.z << endl;
        }
        void drive(double dt){
            imu.measure();
            pos.x = pos.x + imu.dx * dt;
            pos.y = pos.y + imu.dy * dt;
            pos.z = 0;
        }
};

class Drone : public AutonomousVehicle{
    public:
        Drone() : AutonomousVehicle(){};
        void printDrive(ostream& os){
            os << "Dron at: " << "   x: " << pos.x << "  y: " << pos.y << "  z: " << pos.z << endl;
        }
        void drive(double dt){
            imu.measure();
            pos.x = pos.x + imu.dx * dt;
            pos.y = pos.y + imu.dy * dt;
            pos.z = pos.z + imu.dz * dt;
        }
};


int main(void){

    IMU imu1 (1.0, 0.6, 0.1);
    cout << imu1 << endl;

    Car cars [3] = {};
    Drone drones [2] = {};
    int i = 0;
    AutonomousVehicle* avs[5];

    for(Car& car: cars) avs [i++] = &car;
    for(Drone& drone: drones) avs [i++] = &drone;
    
    for(AutonomousVehicle* avPtr : avs) 
        for(int j = 0; j < 1000; j++)
            avPtr->drive(0.005);
 
    for(AutonomousVehicle* avPtr: avs)
        cout << *avPtr;    

    return 0;
}