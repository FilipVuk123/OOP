#include <iostream>
using namespace std;

class MyVector {
protected:
    int *P; 
    // at(), back(), front() imaju kodomenu double
    unsigned int _size, _capacity;
public: 
    MyVector(const MyVector& v)
    {
        _size = v.getSize();
        _capacity = v.getCapacity();
        P = new int[_size];
        for (int i=0; i<=_size;i++) P[i] = v.P[i];
    }
    
    MyVector(int n){
        P = new int[n]{}; // allocate and set to 0
        _capacity = n;
        _size = 0;
    }

    ~MyVector(){delete [] P;}

    void pushBack(double novi){
        if (!full()){
            P[++_size] = novi;
        }else{
            P[++_size] = novi;
            _capacity *= 2;
        }
    };
    int popBack(){
        if(!empty()){return P[_size--];}
        if (_capacity == _size*0.5){_capacity /= 2;}
    };

    unsigned int getCapacity() const { return _capacity;}
    unsigned int getSize() const { return _size;}

    void print(){
        for (int i=1; i<=_size; i++)
            cout << P[i] << " ";
        cout << endl;
    };

    bool empty() const{return _size==0;};
    bool full() const{return _capacity==_size;};

    int& at(unsigned int pos){return P[pos];};
    int& front(){return P[1];};
    int& back(){return P[_size];};

    MyVector& operator=(const MyVector&);
    MyVector& operator+=(const MyVector&);
    MyVector operator+(const MyVector&) const;
    int operator*(const MyVector&) const;
    bool operator==(const MyVector&) const;
    bool operator!=(const MyVector&) const;
    const int& operator[](int x) const {return P[x];};
    int& operator[](int x){return P[x];};
    int* begin() const {return &P[0];};
    int* end() const {return &P[_capacity];};
};
MyVector MyVector::operator+(const MyVector& v) const {
    MyVector z(v._capacity);
    z._size = max(v._size, _size);
    for (int i = 0; i < z._size;i++){
        z.P[i] = v.P[i] + P[i];
    }
    return z;
};
MyVector& MyVector::operator=(const MyVector& v){
    if (P != nullptr)
        delete [] P;
    _capacity = v._capacity;
    _size = v._size;
    P = new int [_capacity]{};
    for (int i = 0; i < _size; i++)
        P[i] = v.P[i];
    return *this;
};
MyVector& MyVector::operator+=(const MyVector& v){
    for (int i = 0; i <= _size; i++)
        P[i] = P[i] + v.P[i];
    return *this;
};
int MyVector::operator*(const MyVector& v) const{
    int skProd = 0;
    for (int i = 0; i <= _size; i++)
        skProd = skProd + (P[i]*v.P[i]);
    return skProd;
}
bool MyVector::operator==(const MyVector& v) const{
    for (int i = 0; i <= _size; i++){
        if (P[i] != v.P[i])
            return false;
    }
    return true;
}
bool MyVector::operator!=(const MyVector& v) const{
    for (int i = 0; i <= _size; i++){
        if (P[i] != v.P[i])
            return true;
    }
    return false;
}
int main(){
    MyVector vect(3);
    vect.pushBack(1);
    vect.pushBack(2);
    vect.pushBack(3);
    vect.print();
    MyVector vect2(3);
    vect2.pushBack(3);
    vect2.pushBack(2);
    vect2.pushBack(1);
    vect2.print();

    //vect += vect2;
    //vect.print();
    //int skProdukt;
    //skProdukt = vect * vect2;
    //cout << skProdukt << endl;
    //cout << (vect == vect2) << endl;
    //cout << (vect != vect2) << endl;
    // cout << vect.begin() << endl;
    // cout << vect.end() << endl;
    return 0;
}