#include <iostream>
using namespace std;



void merge(int A[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], R[n2];
    for(int i = 0; i < n1; i++){
        L[i] = A[p + i];
    }
    for(int j = 0; j < n2; j++){
        R[j] = A[q + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = p;
    while (i < n1 && j < n2){ 
        if (L[i] <= R[j]){ 
            A[k] = L[i]; 
            i++; 
        } 
        else{ 
            A[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while(i < n1){
        A[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        A[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int A[], int p, int r){
    if (p<r){
        int q = (p+r)/2;
        mergeSort(A, p, q);
        mergeSort(A,q+1,r);
        merge(A, p, q, r);
    }
}

int main(void){

    int lista[] {2,17,44,4,3,10,-4,100};
    mergeSort(lista, 0, 7);

    for (auto &i : lista){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}