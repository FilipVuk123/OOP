#include "zadatak2.h"
using namespace std;
#include <iostream>

SquareMatrix::SquareMatrix(unsigned int x){
    M = x;
    container = new double *[M];
    for(int i = 0; i < M; i++){
        container[i] = new double [M];
    }
    
}
SquareMatrix::SquareMatrix(const SquareMatrix& mat){
    M = mat.M;
    container = new double*[M];
    for (int i = 0; i < M; i++) container[i] = mat.container[i];
}
SquareMatrix::~SquareMatrix(){
    for(int i = 0; i < M; ++i) {
        delete [] container[i];
    delete [] container;
    }  
}; 


const double* SquareMatrix::operator[](unsigned int x) const {
    // cout << "[ ] operator says HI! \n";
    return container[x];
}

SquareMatrix& SquareMatrix::operator=(const SquareMatrix& mat){
    // cout << " = operator says HI! \n";
    M = mat.M;
    container = new double *[M];
    for (int i = 0; i < M; i++) container [i] = mat.container[i];
    return *this;
}
bool SquareMatrix::operator==(const SquareMatrix& mat) const{
    // cout << " == operator says HI! \n";
    for(int i = 0; i < mat.M; i++){
        for (int j = 0; j < mat.M; j++){
            if (container[i][j] != mat.container[i][j])
                return false;
        }
    }
    return true;
}
bool SquareMatrix::operator!=(const SquareMatrix& mat) const{
    // cout << " != operator says HI! \n";
    for(int i = 0; i < mat.M; i++){
        for (int j = 0; j < mat.M; j++){
            if (container[i][j] != mat.container[i][j])
                return true;
        }
    }
    return false;
}
SquareMatrix& SquareMatrix::operator=(double x){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = x;
        }
    }
}
SquareMatrix& SquareMatrix::operator+=(double x){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = container [i][j] + x;
        }
    }
};
SquareMatrix& SquareMatrix::operator-=(double x){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = container [i][j] - x;
        }
    }
};
SquareMatrix& SquareMatrix::operator*=(double x){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = container [i][j] * x;
        }
    }
};
SquareMatrix& SquareMatrix::operator/=(double x){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = container [i][j] / x;
        }
    }
};
SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& mat){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = container [i][j] + mat.container [i][j];
        }
    }
};

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& mat){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = container [i][j] - mat.container [i][j];
        }
    }
};

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& mat){
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            container [i][j] = container [i][j] * mat.container [i][j];
        }
    }
};
SquareMatrix SquareMatrix::operator+(const SquareMatrix& mat) const{
    SquareMatrix nova(mat.M);
    for(int i = 0;i < M; i++){
        for(int j = 0; j < M; j++){
            nova.container [i][j] = container [i][j] + mat.container [i][j];
        }
    }
    return nova;
};
SquareMatrix SquareMatrix::operator-(const SquareMatrix& mat) const{
    SquareMatrix nova(mat.M);
    for(int i = 0;i < mat.M; i++){
        for(int j = 0; j < mat.M; j++){
            nova.container [i][j] = container [i][j] - mat.container [i][j];
        }
    }
    return nova;
};
SquareMatrix SquareMatrix::operator*(const SquareMatrix& mat) const{
    SquareMatrix nova(mat.M);
    for(int i = 0;i < mat.M; i++){
        for(int j = 0; j < mat.M; j++){
            for(int k = 0; k < mat.M; k++){
                nova.container [i][j] += container[i][k] * mat.container[k][j];
            }
        }
    }
    return nova;
};
