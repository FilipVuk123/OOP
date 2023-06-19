#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct PositionVector{
    double x, y;
    PositionVector(){};
    PositionVector(double x, double y){
        this->x = x;
        this->y = y;
    };
    PositionVector(const PositionVector& v){
        this->x = v.x;
        this->y = v.y;
    };
    double norm() const{return sqrt(pow(x,2)+pow(y,2));};
    void print() const{
        cout << "x: " << x << " y: "<< y << ", norma: " << norm() << endl;
    };

};

bool sortHelp(PositionVector a,PositionVector b){return a.norm() > b.norm();};

int main(){
    PositionVector polje [5] = {PositionVector(2.5, 3.6),PositionVector(5.5,3.6),PositionVector(4.4,4.4), PositionVector(10.0,0.1),PositionVector(0.0,0.0)};
    for(PositionVector &i:polje){
        i.print();
    }
    sort(polje, polje + 5, sortHelp);
    cout << endl;
    for(PositionVector &i:polje){
        i.print();
    }

    return 0;
};