#include <iostream>
#include <vector>

using namespace std;

class Vertex{
    public:
        int elem;
    public:
        Vertex(int a): elem(a){};
        friend ostream& operator<< (ostream& os, const Vertex& e){
            os << e.elem;
            return os;
        }
};

class Edge{
    public:
        Vertex start, end;
    public:
        Edge(Vertex a, Vertex b): start(a), end(b){}
        friend ostream& operator<< (ostream& os, const Edge& e){
            os << "(" << e.start << ", " << e.end << ")";
            return os;
        }
};


class Graph{
    public:
        vector<Edge> E; 
        vector<vector<Vertex>> Neighbours;
    public:
        bool exists(Vertex x){
            int s = 0;
    	    for(vector<Vertex> i : Neighbours){
                if(i[0].elem == x.elem){
                    return true;
                }
                s++;
            }
            return false;
        }
        void addVertex(Vertex a){
            vector<Vertex> v;
            v.push_back(a);
            Neighbours.push_back(v);
        }
        void addEdge(Edge e){
            if(!exists(e.start)) addVertex(e.start);
            if(!exists(e.end)) addVertex(e.end);

            E.push_back(e);
            int j = 0;
            for(vector<Vertex> i : Neighbours){
                if(i[0].elem == e.start.elem){
                    Neighbours.at(j).push_back(e.end);
                    // cout << i.size() << " ";
                }
                j++;
            }
            
        };
        void printNeightbours(){
            cout << "Polje susjedstva: " << endl;
            for(vector<Vertex> v : Neighbours){
                // cout << v.size() << " ";
                for(int i = 0; i < v.size(); i++){
                    cout << v.at(i) << " ";
                }
                cout << endl;   
            }
        };
        void printE(){
            cout << "Bridovi: ";
            for(auto i : E) cout << i << " ";
            cout << endl;
        };
        void deleteEdge(Edge e){
            for(int i = 0; i < E.size(); i++){
                if(E.at(i).start.elem == e.start.elem && E.at(i).end.elem == e.end.elem){
                    E.erase(E.begin() + i);
                }
            }
            for(int i = 0; i < Neighbours.size(); i++){
                for(int j = 0; j < Neighbours[i].size(); j++){
                    if(Neighbours[i][j].elem == e.end.elem && Neighbours[i].at(0).elem == e.start.elem){
                        Neighbours[i].erase(Neighbours[i].begin() + j);
                    }
                }
            }
        };
};
       

int main(){
    
    Edge E12(Vertex (1), Vertex (2));
    Edge E14(Vertex (1), Vertex (4));
    Edge E24(Vertex (2), Vertex(4));
    Edge E43(Vertex (4), Vertex(3));
    Edge E13(Vertex (1), Vertex(3));
    Edge E32(Vertex (3), Vertex(2));
    Edge E46(Vertex (4), Vertex(6));
    Edge E56(Vertex (5), Vertex(6));
    Edge E16(Vertex (1), Vertex(6));
    
    Graph G;
    
    G.addEdge(E12);
    G.addEdge(E24);
    G.addEdge(E14);
    G.addEdge(E43);
    G.addEdge(E13);
    G.addEdge(E32);
    G.addEdge(E16);
    G.addEdge(E56);
    G.addEdge(E46);
    
    G.printE();
    G.printNeightbours();
    G.deleteEdge(E12);
    G.deleteEdge(E46);
    G.deleteEdge(E43);
    
    G.printE();
    G.printNeightbours();

    return 0;
}