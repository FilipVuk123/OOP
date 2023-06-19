#include <iostream>
using namespace std;



void insertionSort(int A[],int n){
    for(int i = 1; i< n; i++){
        int key = A[i];
        int j = i - 1;
        while(j >= 0 && key <= A[j]){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}
void bubbleSort(int A[], int n){
    bool swapped;
    for(int i = 0; i < n - 1; i++){
        swapped = false;
        for(int j = 0; j < n - i - 1 ; j++){
            if (A[j] >= A[j+1]){
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
                swapped = true;
                // cout << "tu sam" << endl;
            }
        }
        if (swapped == false) break;
    }
}

int main(){
    int lista[] = {1,4,7,2,6,9,11};
    int lista1[] = {1,5,7,77,4,6,12};

    insertionSort(lista1, 7);
    bubbleSort(lista, 7);

    for (auto &i : lista){
        cout << i << " ";
    }
    cout << endl;
    for (auto &i : lista1){
        cout << i << " ";
    }
    return 0;
}
