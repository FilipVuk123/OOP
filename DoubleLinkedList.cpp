#include <iostream>
using namespace std;

class Node{
    public:
        Node* next;
        Node* prev;
        int elem;

        Node(Node* n, Node* p, int x):next(n), prev(p), elem(x){};
};
class DoubleLinkedList{
    public:
        Node* head{}, *tail{};

        DoubleLinkedList(){};
        ~DoubleLinkedList(){
            Node * iter = head;
            Node * forDelete;
            while(iter != nullptr){
                forDelete = iter;
                iter = iter->next;
                delete forDelete;
            }
        };
        
        
        void insert(int x){
            Node* it = head;
            if(head == nullptr){
                Node* n = new Node(nullptr, nullptr, x);
                head = n;
                tail = head;
            }else if(x <= head->elem){
                // cout << " <= " << endl;
                Node* n = new Node(head, nullptr, x);
                head = n;
            }else if(x >= tail->elem){
                // cout << " >= " << endl;
                Node* n = new Node(nullptr, tail, x);
                Node* iter = head;
                while(iter->next != nullptr){
                    iter = iter->next;
                }
                iter->next = n;
                tail = n;
            }else{
                Node* iter = head;
                while(x >= iter->elem){
                    iter = iter->next;
                }
                iter = iter->prev;
                
                Node* n = new Node(iter->next, iter, x);
                iter->next->prev = n;
                iter->next = n;
            }
        }
        void print(){
            Node* iter = head;
            while(iter != nullptr){
                cout << iter->elem << " ";
                iter = iter->next;
            }
            cout << endl;
        }
};
int main(){

    DoubleLinkedList L;
    L.insert(2);
    L.insert(1);
    L.insert(-1);
    L.insert(12);
    L.insert(15);
    L.insert(7);
    L.insert(9);
    L.insert(-20);
    L.insert(-1000);
    L.print();


    return 0;
}