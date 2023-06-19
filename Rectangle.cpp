#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

class Rectangle;

class Point{
	protected:
		double x, y;
	public:
		Point(){};
		Point(double x1, double y1){
			this->x = x1;
			this->y = y1;
		};
			
	double getx() const{return x;};
	double gety() const{return y;};
	
	void setx(double x1){this->x = x1;};
	void sety(double y1){this->y = y1;};
	
	void print() const{
		cout << x << " i " << y << endl;
	};
	
	bool isInside(Rectangle) const;

	
};

class Rectangle{
	protected:
		Point A, B, C, D;
	public:
	
		Rectangle(Point A1,Point B1, Point C1){
			this -> A = A1;
			this -> B = B1;
			this -> C = C1;
			this -> D = calcD();
		};
	
		Point getA() const {return A;};
		Point getB() const {return B;};
		Point getC() const {return C;};
		Point getD() const {return D;};
		/*Point calcD() const{
			Point D(C.getx()-(B.getx() - A.getx()),C.gety()-(B.gety() - A.gety()));
			return D;
		};*/
		
		double ab() const {
			double str = pow(A.getx() - B.getx(),2) + pow(A.gety()- B.gety(),2);
			return sqrt(str);
		};
		
		double bc() const {
			double str = pow(C.getx() - B.getx(),2) + pow(C.gety()- B.gety(),2);
			return sqrt(str);
		};
		
		double area() const {return (ab() * bc());};
			
		double perimeter() const {return (2*ab() + 2*bc());};
		
		/*
		* Pomakni kvadrat za "neku točku"
		*/
		void translate(Point T){
			A.setx(A.getx() + T.getx());
			A.sety(A.gety() + T.gety());
			B.setx(B.getx() + T.getx());
			B.sety(B.gety() + T.gety());
			C.setx(C.getx() + T.getx());
			C.sety(C.gety() + T.gety());
			D.setx(D.getx() + T.getx());
			D.sety(D.gety() + T.gety());
		};
			
		
		void rotate(){
			A.setx(-(A.getx()));
			A.sety(-(A.gety()));
			B.setx(-(B.getx()));
			B.sety(-(B.gety()));
			C.setx(-(C.getx()));
			C.sety(-(C.gety()));
			D.setx(-(D.getx()));
			D.sety(-(D.gety()));
			
		};
		
		void print() const{
			cout<< "A: (x,y) = (" << A.getx() << "," << A.gety() << ")" << endl;
			cout<< "B: (x,y) = (" << B.getx() << "," << B.gety() << ")" << endl;
			cout<< "C: (x,y) = (" << C.getx() << "," << C.gety() << ")" << endl;
			cout<< "D: (x,y) = (" << D.getx() << "," << D.gety() << ")" << endl;
		};
		
	private:
		Point calcD() const{
			Point D(C.getx()-(B.getx() - A.getx()),C.gety()-(B.gety() - A.gety()));
			return D;
		};
};

bool Point::isInside(Rectangle r) const {
		Point a = r.getA();
		Point b = r.getB();
		Point c = r.getC();
		Point d = r.getD();
		
		double minX = min(min(a.getx(), b.getx()), min(c.getx(), d.getx()));
		double maxX = max(max(a.getx(), b.getx()), max(c.getx(), d.getx()));
		double minY = min(min(a.gety(), b.gety()), min(c.gety(), d.gety()));
		double maxY = max(max(a.gety(), b.gety()), max(c.gety(), d.gety()));
		
	if ((x >= minX) && (x <= maxX) && (y >= minY) && (y <= maxY)){
		return true;
	}else{
		return false;
	};
};

int main(){
    Point A(3,1),B(1,1),C(1,2);
	Rectangle R (A,B,C);
	Point P(2,1.5);
	R.print();
	cout<<"Area:"<<R.area()<<endl;
	cout<<"Perimeter:"<<R.perimeter()<<endl;
	if (P.isInside(R) == 1){cout << "Point inside rectangle? - true" << endl;} else {cout << "Point inside rectangle? - false" << endl;};
	cout << "Rotate for pi rad"<< endl;
	R.rotate();
	R.print();
	cout << "Translate for (2, 3)" << endl;
	R.translate(Point(2,3));
	R.print();
	if (P.isInside(R) == 1){cout << "Point inside rectangle? - true" << endl;} else {cout << "Point inside rectangle? - false" << endl;};

	
    return 0;
};