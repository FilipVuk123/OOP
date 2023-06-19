#include <iostream>
#include <vector>
using namespace std;

class DynamicStack{
    protected:
        vector<int> container;
    public:
        DynamicStack(){};
        DynamicStack(const DynamicStack& s){
            container.clear();
            for (int i : s.container){ //tzv. range-for; i -> svaki element containera
                push(i);
            }
        };

        bool empty() const {
            return this->container.empty();
        }
        
        void push(int x){
            container.push_back(x);
        };
        int pop(){
            container.pop_back();
        };
        
        void print(){
            for(int n : container){
                cout << n << " ";
            }
            cout << endl;
        };
};

int main(){

    DynamicStack *mojStack = new DynamicStack();

    for (int i = 1; i <= 10;i++){
        mojStack->push(i);
    }
    mojStack->print(); 

    DynamicStack *kopija = new DynamicStack(*mojStack);
    
    while(!(kopija->empty())){
        kopija-> pop();
        kopija->print();
    }

    delete mojStack;
    delete kopija;
    return 0;
};