#include <iostream>
#include <vector>
#include <queue>
class Edge{ 
    public:
        int S, F, w;
};

class Graph{
    public:
        std::vector<Edge> edges;
        int V, E;
        Graph(int v, int e):V(v), E(e){};
        void print(){
            for(auto i : edges){
                std::cout << "S: " << i.S << ", F: " << i.F << ", w: " << i.w << std::endl;
            }
        }
        void addEdge(int v1, int v2, int w){
            Edge e; e.S = v1; e.F = v2; e.w = w;
            edges.push_back(e); 
        }

        int Dijstra(int start, int end){
            std::priority_queue<int, std::vector<int>, std::greater <int>> Q;
            std::vector<int> S;
            int dis[V]; int pi[V];
            for(int i = 0; i < V; i++){
                dis[i] = INT_MAX;
                pi[i] = -1;
                Q.push(i);
            }
            dis[start] = 0;
            
            while(!Q.empty()){
                int u = Q.top();
                Q.pop();
                S.push_back(u);
                for(auto edge : edges){
                    if(edge.S == u){
                        int v = edge.F;
                        int w = edge.w;
                        if(dis[u] != INT_MAX && dis[u] + w < dis[v]){
                            dis[v] = dis[u] + w;
                            pi[v] = u;
                        }
                    }
                }
            }
            return dis[end];
        }

};
int main(){
    int t, N, M, X, Y, D, S, s, news;
    std::cin >> t;
    for(int i = 0; i < t; i++){
        std::cin >> N >> M;
        Graph G(N,M);
        for(int j = 0; j < M; j++){
            std::cin >> X >> Y >> D;
            G.addEdge(X,Y,D);
        }
        std::cin>>S;
        s = 0;
        int finalRez = 0; 
        for(int j = 1; j < S; j++){
            std::cin >> news;
            finalRez += G.Dijstra(s, news);
            s = news;
        }
        finalRez += G.Dijstra(s, 0);
        std::cout << finalRez << "\n";
    }

    return 0;
} // 1 4 6 0 1 1 1 2 1 2 3 1 3 0 1 0 2 5 1 3 5 3 1 2 3