#include <iostream>
using namespace std;
// JEDNOSTRUKO POVEZANA LISTA!!!
struct Node{
    int n; // data
    Node* next;
    Node(int n, Node* next): n{n}, next{next}{};

};

class List{
    protected:
        Node* head;
    public:
        List(){head = nullptr;};
        void push_front(int);
        Node* search(int);
        void display();
        bool erase(int);
        ~List();
};
List::~List(){
    cout << "~List -- destructor says Hi! " << endl;
    Node* iter = head;
    while(iter != nullptr){
        Node* tmp = iter;
        iter = iter-> next;
        delete tmp;
    }
};
bool List::erase(int x){
    Node* iter = head;
    Node* prev = head;
    while(iter != nullptr){
        if(iter->n == x){
            // prebridgeati, obrisati!!!
            if(iter == head){
                head = iter-> next;
                delete iter;
            }
            prev->next = iter->next;
            delete iter;
            return true;
        }
        prev = iter;
        iter = iter->next;
    }
    return false;
};
void List::push_front(int x){
    Node* c = new Node(x, head);
    head = c;
}
void List::display(){
    Node* iter = head;

    while(iter != nullptr){
        cout << " " << iter->n << " | " << iter->next << " >>  " ;
        iter = iter->next;
    }
    cout<<endl;
}
Node* List::search(int x){
    Node* iter = head;

    while(iter!= nullptr){
        if(iter->n == x)
            return iter;
        iter = iter->next;
    }

    return nullptr;
};
int main(){  
    List L; 
    L.push_front(1);
    L.push_front(2);
    L.push_front(4);
    L.push_front(7);
    L.push_front(-7);
    L.push_front(77000);
    L.push_front(9);
    L.erase(1);
    L.erase(9);
    L.display();
    cout << L.search(1) << endl;


    return 0;
}; // referenca -> dereferenirani pointer... objekt...
// poiter -> nick varijable