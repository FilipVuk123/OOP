#include <iostream>
#include <string>
using namespace std;

class Credentials{
    public:
        string username, email;
        unsigned int age;

        Credentials(): username{}, email{}, age{} {};
        Credentials(const string username, const string email,const unsigned int age): username{username}, email{email}, age{age} {};
        Credentials(const Credentials& c){
            username = c.username;
            email = c.email;
            age = c.age;
        };
        
        ~Credentials() = default;

        Credentials& operator=(Credentials& c){
            username = c.username;
            email = c.email;
            age = c.age;
        }
};
ostream& operator<<(ostream& os, Credentials& c){
    os << "Username: " << c.username <<"     Email: " << c.email << "     Age: " << c.age << endl;
    return os;
}

template <typename T, size_t S>
class Queue{
    public:
        T* head;
        T* tail;
        T container[S]{};
        
        Queue(): head{container}, tail{container - 1} {}

        Queue(const Queue& q){
            head = q.head;
            tail = q.tail;
            for(int i = 0; i < S; i++)
                container[i] = q.container[i];
        };
        ~Queue()= default;

        bool empty() const {return head == tail + 1;};
        bool full() const {return container + S - 1 == tail;};

        template<typename... Ta>
        void enqueue(T t, Ta... ts){
            if(!full()){
                *++tail = t;
                return enqueue(ts...);
            }
        }

        void enqueue() {}
        T dequeue(){
            if(!empty()){
                T box = *head;
                for(int i = 0; i < (tail- head + 1); i++){
                    *(head+i) = *(head + i+1);
                }
                tail--;   
                return box;               
            }                        
        }

        void print() {
            for(int i = 0; i < (tail - head + 1); i++){
                cout << container[i]; 
            }
            cout << endl;
        }
};

int main(){

    Queue<Credentials, 10> que;
    Credentials c1("Filip","filip@mathos.hr", 19);
    Credentials c2("Josip","josip@mathos.hr", 29);
    Credentials c3("Ena","ena@mathos.hr", 44);
    Credentials c4("Mirna","mirna@mathos.hr", 20);
    Credentials c5("Dorotea","dorotea@mathos.hr", 25);
    Credentials c6("Doki", "doki@mathos.hr", 20);
    
    que.enqueue(c1, c2, c3, c4, c5);
    que.print();
    que.dequeue();
    que.print();
    que.enqueue(c6);
    que.print();

    return 0;
}