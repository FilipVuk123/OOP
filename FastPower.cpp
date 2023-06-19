#include <iostream>
using namespace std;

int fastPower(int b, int e){ // implement fast power algorithm
    int x;
    if (e == 0){
        return 1;
    }else{
        if(e % 2 == 0){
            x = fastPower(b, e/2);
            return x * x;
        }else{
            x = fastPower(b, (e-1)/2);
            return b * x * x;
        }
    }
    
}

int main(){
    
    cout << fastPower(2, 3) << endl;
    return 0;
}