#include<iostream>
#include<vector>
using namespace std;

int maxSubarray(vector<int> arr) {
    int maxSum = arr[0];
    int tempSum = arr[0];
    for (int i = 1; i < arr.size(); ++i){
        tempSum += arr[i];
        if (tempSum < arr[i]) tempSum = arr[i];
        
        maxSum = max(maxSum, tempSum);
    }
    return maxSum;
}

int main(){
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << maxSubarray(A);
    return 0;
}