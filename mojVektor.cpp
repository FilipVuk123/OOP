#include <iostream>
using namespace std;

class mojVektor {
protected:
    double *P; // at(), back(), front() imaju kodomenu double
    unsigned int _size, _capacity;
public: 
    mojVektor(const mojVektor& v)
    {
        _size = v.getSize();
        _capacity = v.getCapacity();
        P = new double[_size];
        for (int i=0; i<=_size;i++) P[i] = v.P[i];
    }
    
    mojVektor(int x)
    {
        P = new double[x];
        _capacity = x;
        _size = x;  
        for (int i=1; i<=_size;i++) P[i] = i;

    }
    ~mojVektor(){delete [] P;}

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

    double& at(unsigned int pos){return P[pos];};
    double& front(){return P[1];};
    double& back(){return P[_size];};

};

int main(){
    mojVektor *vek = new mojVektor(10);
    vek->print();
    mojVektor *kop = new mojVektor(*vek);
    while(!(kop->empty())){
        kop->popBack();
        kop->print();
    }
    
    delete vek;
    delete kop;

    return 0;
};