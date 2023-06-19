#include "zadatak2.h"
#include <iostream>
using namespace std;

ostream& operator << (ostream& os, const SquareMatrix& mat){
    for(int i = 0; i < mat.M; i++){
        for(int j = 0; j < mat.M; j++){
            os << mat.container[i][j] << " ";
        }
        os << "\n";
    }
    return os;
};

int main(){
    double a = 0.0;
    SquareMatrix matrica1(10);
    for(int i = 0;i < matrica1.M; i++){
        for(int j = 0; j < matrica1.M; j++){
            if (i == j){
                matrica1.container [i][j] = a + 1.0;
            }
        }
    }
    // cout << matrica1 << endl;
    SquareMatrix matrica2(10);
    for(int i = 0; i < matrica2.M; i++){
        for(int j = 0; j < matrica2.M; j++){
                matrica2.container [i][j] = 1.0;
        }
    }
    cout << matrica2 << endl;

    SquareMatrix matrica3(10);
    matrica3 = matrica1;
    matrica3 /= 10.0;
    
    cout << matrica3 << endl;

    return 0;
}