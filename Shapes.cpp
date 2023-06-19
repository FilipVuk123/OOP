#include <iostream>
using namespace std;

class Shapes{
    public:
        virtual double area() const = 0;
};

class Rectangle : public Shapes{
	private: 
        double width, height;
    public:
        Rectangle(double w, double h){
            width = w;
            height = h;
        }
        double area()const{
            return width*height;
        }
};

class Circle : public Shapes {
    private:
        double radius;
    public:
        Circle(double r){
            radius = r;
        }
        double area()const{
            return 3.14*radius*radius;
        }
};


int main(void){

    Rectangle R1(5.5, 7.2);
    Rectangle R2(0.2, 1.5);
    Rectangle R3(8.9, 9.8);
    Circle C1(1.5);
    Circle C2(2.6);
    Circle C3(2.7);
    
    Shapes* s1 = &R1;
    Shapes* s2 = &R2;
    Shapes* s3 = &R3;
    Shapes* s4 = &C1;
    Shapes* s5 = &C2;
    Shapes* s6 = &C3;
    

    Shapes* polje [] = {s1,s2,s3,s4,s5,s6};
    double suma = 0.0;
    for (auto &i : polje){
        suma += i->area();
    }
    cout << "Suma svih povrsina je: " << suma << endl;

    return 0;
}