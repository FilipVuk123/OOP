#include <iostream>
#include <vector>
#include <queue>
int n;
std::vector<std::vector<bool>> graph; 
std::vector<bool> visited;
std::vector<int> tin, low;
std::priority_queue <int, std::vector<int>, std::greater<int>> points; 

int time = 0;

void DFS(int v, int p) {
    visited[v] = true;
    tin[v] = low[v] = time;
    time++;
    int children = 0;
    for (int i = 0; i < graph[v].size(); i++){
        if(graph[v][i]){
            if (visited[i]) {
                low[v] = std::min(low[v], tin[i]);
            } else {
                DFS(i, v);
                low[v] = std::min(low[v], low[i]);
                if ((low[i] >= tin[v]) && p!=-1)
                    points.push(v+1);
                children ++;
            }
        }
    }
    if(p == -1 && children > 1)
        points.push(v+1);
}

void find_cutpoints() {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) DFS (i, -1);
    }
}

int main(){
    int m, u, v;
    std::cin >> n >> m;
    graph.resize(n);
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for(int i = 0; i < graph.size(); i++) graph[i].assign(n, false);
    for(int i = 0; i < m; i++){ // matrična reprezentacija
        std::cin >> u >> v;
        u--; v--;
        graph[u][v] = true;
        graph[v][u] = true;
    }

    find_cutpoints();

    

    std::cout << "\n";
    while(!points.empty()){
        std::cout << points.top() << " ";
        points.pop();
    }
    std::cout << "\n";
    return 0;
}
/*
IDEJA:
1. DFS: 
    a) ako je neki vrh root -> ako ima barem 2 djece -> artikulacijska tocka
    b) inace -> ako nema "back edge"va -> artikulacijska tocka
2. provjera: v je artikulacijska tocka akko low[i] >= tin[v]
*/