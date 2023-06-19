#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

struct Student{
    int scores[5];

    Student(){};
    void fillScores(int (& arr)[5]){
        for (int i = 0;i < 5; i++){scores[i] = arr[i];}
    };

    int calculateTotalScore() const {return accumulate(scores, scores + 5, 0);}; // suma

    void print()const{
        for(auto &a : scores)
            cout << a << " ";
        cout << "\n";
    };
};

int main(){    

    ifstream file("data.txt");
    Student *st = new Student[5];
    int brStudenata;
    if(file.is_open())
        file >> brStudenata;
    // cout << brStudenata;
    int bodovi;
    if (file.is_open()){
        int arr[5];
        for(int i = 0;i < brStudenata;i++){
            for (int j = 0;j < 5;j++){
                file >> bodovi;
                arr[j] = bodovi;
            }
            st[i].fillScores(arr);
            //st[i].print();
        }
    }
    file.close();

    int pero = st[0].calculateTotalScore(); 

    int rez = count_if(st+1, st+brStudenata,[pero](Student a){return a.calculateTotalScore() >= pero;}); // stackoverflow
    cout << rez<< "\n";

    delete [] st;
    return 0;
}