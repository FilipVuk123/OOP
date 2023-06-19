#include <iostream>
#include <list>
#include <numeric>
using namespace std;

double sum(list<double> &a){
    return accumulate(begin(a), end(a), 0.0);
} 

double prod(list<double> &a){
    double produkt = 1;
    for(double &i : a){
        produkt *= i;
    }
    return produkt;
}
double min(list<double> &a){
    a.sort();
    cout << a.front() << "\n";
}
double max(list<double> &a){
    a.sort();
    a.reverse();
    cout << a.front() << "\n";
}

int main(){
    double l [] = {59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};
    list<double> lista1;
    for (auto &i : l){
        lista1.push_back(i);
    }
    cout << sum(lista1) << "\n";
    cout << prod(lista1) << "\n";
    min(lista1);
    max(lista1);
    return 0;
};  