#include <iostream>
using namespace std;

struct MyClass{
    int value;
    MyClass(): value{} {cout << "default" << endl;};
    MyClass(const MyClass& mc): value{mc.value} {cout << "copy" << endl;};
    ~MyClass(){cout << "delete" << endl;};
};
MyClass& someFunction(){
    MyClass* mc = new MyClass{};
    return *mc;
 };

int main(){
    MyClass mc = someFunction();
    delete mc; // fix?
    return 0;
};