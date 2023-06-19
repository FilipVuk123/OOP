/* Labirint rekurzivno :) */

#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> polje;

vector<vector<char>> input(int n){
    vector<vector<char>> to_return;
    string line;
    
    while(n > 0){
        vector<char> v;
        getline(cin, line);
        for(int j = 0; j < line.size(); j++){
            char c = line[j];
            if(c == '_'){
                n--;
                break;
            } 
            v.push_back(c);
        }
        to_return.push_back(v); 
    } 
    to_return.pop_back();
    return to_return;
}
vector<pair<int,int>> findStart(vector<vector<char>> V){
    vector<pair<int,int>> v;
    for(int i = 0; i < V.size(); i++){
        for(int j = 0; j < V[i].size(); j++){
            if(V[i][j] == '*'){
                pair<int, int> to_push (i,j);
                v.push_back(to_push);
            }
        }
    }
    return v;
}
int count = 0;
void recusion(vector<vector<char>> &V, int i, int j){
    if(V[i][j] == 'X' || V[i][j] == '#'){
        return;
    }
    count ++;
    V[i][j] = '#';
    recusion(V, i-1, j);
    recusion(V, i, j-1);
    recusion(V, i+1, j);
    recusion(V, i, j+1);
}


int main(){
    int n;
    cin >> n;
    polje = input(n);
    vector<pair<int,int>> zvj;
    zvj = findStart(polje);

    for(int a = 0; a < n; a++){
        recusion(polje, zvj[a].first, zvj[a].second);
    }
    cout << "Rjesenje: " << endl;
    for(int i = 0; i < polje.size(); i++){
        for(int j = 0; j < polje[i].size(); j++){
            cout << polje[i][j];
        }
        cout << endl;
    }
    // cout << "Counter: " << count << endl;
    return 0;
}