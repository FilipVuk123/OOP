#include <iostream>
#include <vector>

class Edge{ 
    public:
        int S, T, w;
};

class Graph{ 
    public:
        int V, E;
        std::vector<Edge> edges;
        Graph(int v, int e): V(v), E(e){};
        void addEdge(int v1, int v2, int w){ // neusmjereni graf
            Edge e; e.S = v1; e.T = v2; e.w = w;
            Edge a; a.T = v1; a.S = v2; a.w = w;
            edges.push_back(e);
            edges.push_back(a);
            
        }
        void print(){
            for(auto i : edges){
                std::cout << "S: " << i.S << ", T: " << i.T << ", w: " << i.w;
            }
        }
        int BellmanFord(int start, int end){ // algoritam skripta
            int dis[V];
            for(int i = 0; i < V; i++) dis[i] = INT_MAX;
            dis[start] = 0;

            //print();

            for(int i = 0; i < V - 1; i++){
                for(int j = 0; j < 2*E; j++){
                    int u = edges[j].S;
                    int v = edges[j].T;
                    int w = edges[j].w;
                    // std::cout << dis[u] << "+" << w << "<" << dis[v];
                    if(dis[u] != INT_MAX && dis[u] + w < dis[v]){
                        // std::cout << "IN IF!";
                        dis[v] = dis[u] + w;
                    }
                }
            }
            if(dis[end] == INT_MAX) return -1; else return dis[end]; 
        }
};


int main(){
    std::vector<int> result;
    int N, n, m, S, T, v1, v2, w;

    /*
    Graph G(3,3);
    G.addEdge(0,1,100);
    G.addEdge(0,2,200);
    G.addEdge(1,2,50);
    G.BellmanFord(0, 2);
    */
    
    std::cin >> N;
    for(int i = 0; i < N; i++){
        std::cin >> n >> m >> S >> T;
        Graph G(n,m);
        for(int j = 0; j < m; j++){
            std::cin >> v1 >> v2 >> w; 
            G.addEdge(v1,v2,w);
        }
        // G.print();
        result.push_back(G.BellmanFord(S, T));
    }

    for(int i = 0; i < N; i++){
        if(result[i] == -1) std::cout << "Case #" << i + 1 << ": unreachable\n"; 
        else std::cout << "Case #" << i + 1 << ": " << result[i] << std::endl; 

    }
    return 0;
}
