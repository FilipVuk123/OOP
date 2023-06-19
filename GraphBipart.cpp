#include <iostream>
#include <vector>
#include <queue>
using namespace std;
    
vector<vector<int>> graph;
vector<int> color;
 
bool isBipartite(int n, int e){
    color[0] = 1;
    queue <int> q;
    q.push(0);
    while (!q.empty()){
        int temp = q.front();
        q.pop();
        for (int i = 0; i < n; i++){
            if (graph[temp][i] && color[i] == -1){ // vrh bez boje
                color[i] = 1 - color[temp];
                // cout << color[i] << " ";
                q.push(i);
            }else if (graph[temp][i] && color[i] == color[temp]){
                // cout << color[i] << " ";
                return false;
            }    
            // ako postoji brid s vrhovima iste boje graf nije bipartitan
        }
    }
    return true;
}
 
int main()
{
    int u, v, n, m;
    cin >> n >> m;

    graph.resize(n);
    color.resize(n,-1);
    for(int i = 0; i < n; i++) graph[i].resize(n);
    
    for(int i = 0; i < m; i++){ // matrična reprezentacija
        cin >> u >> v;
        u--; 
        v--;
        graph[u][v]=1;
        graph[v][u]=1;
    }
    /* 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }*/

    if(isBipartite(n, m)) cout<<"Yes"; else cout<<"No";
    return 0;
}
/*
Aloritam koji sam koristio:
1. proci BFSom sve vrhove.
2. uzeti vrh i obojati ga 
3. obojati sve susjedne vrhove dok svi ne budu obojani
4. ako u bilo kojem trenutku posotji brid s vrhovima iste boje -> graf nije bipartitan
*/