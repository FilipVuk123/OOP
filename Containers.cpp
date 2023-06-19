#include <iostream>
using namespace std;


template <typename T, size_t S>
class Container{
    protected:
        // kod nasljeđene klase vraca
        // pokazivač na prvi element polja
        virtual T* first() = 0;
        // kod nasljeđene klase vraća
        // pokazivač na konstantni prvi element polja
        virtual const T* first() const = 0;
        // pomocna metoda za end() i []
        virtual T* last() = 0;
        virtual T& elementAt(int i) = 0;
    public:
        Container() = default;
        virtual ~Container() = default;
        // vrati pokazivač na prvi element polja
        T* begin(){return first();};
        // vrati pokazivač na zadnji element polja
        T* end(){return last();}
        // vrati pokazivač na konstantni prvi element polja
        const T* begin() const{return first();};
        // vrati pokazivač na konstantni zadnji element polja
        const T* end() const {return last();}
        // preopterećeni operator dohvaćanja
        T& operator[](int i){return elementAt(i);}
        // konstantni preopterećeni operator dohvaćanja
        const T& operator[](int i) const{return elementAt(i);};

        
        virtual void print(ostream& os) const = 0;
        
};

template <typename T, size_t S>
class DynamicContainer: private Container<T, S> {
    private:
        T* container;
    public:
        DynamicContainer(int n){
            container = new T [S];
            for(int i = 0; i < S; i++)
                container [i] = n;
        }
        T* first() override {return 0;}
        const T* first() const override {return 0;}
        T* last() override {return 0;}

        T& elementAt(int i) override {return container[i];}
        ~DynamicContainer(){
            delete [] container;
        };
        
        void print(ostream& os) const {
            for(int i = 0; i < S; i++)
                os << container[i] << " "; 
        };
        
};

template <typename T, size_t S>
class StaticContainer: private Container<T, S> {
    private:
        T container [S];
    public:
        StaticContainer(int n){ 
            for(int i = 0; i < S; i++)
                container [i] = n;
        }
        T* first() override {return 0;}
        const T* first() const override {return 0;}
        T* last() override {return 0;}

        T& elementAt(int i) override {return container[i];}
        void print(ostream& os) const {
            for(int i = 0; i < S; i++)
                os << container[i] << " "; 
        };
        
};


int main(void){
    StaticContainer<int, 3> SC1(7);
    StaticContainer<int, 2> SC2(3);
    DynamicContainer<int, 4> DC1(3);
    DynamicContainer<int, 4> DC2(4);

    // cout << DC1.first() << " " << DC1.last() << "  " << DC1.elementAt(0) << endl;
    // cout << SC1.first() << " " << SC1.last() << "  " << SC1.elementAt(0) << endl;
    // SC1.print(cout);
    // DC1.print(cout);

    Container<int,3>& cont1 = *reinterpret_cast<Container<int,3>*>(&SC1); 
    Container<int,2>& cont2 = *reinterpret_cast<Container<int,2>*>(&SC2); 
    Container<int,4>& cont3 = *reinterpret_cast<Container<int,4>*>(&DC1); 
    Container<int,4>& cont4 = *reinterpret_cast<Container<int,4>*>(&DC2); 
    
    // Smjestiti sve u zajednicko polje
    int* polje = new int [13]; 
    int i = 0;
    for(int a = 0; a < 3; a++) polje[i++] = cont1[a];
    for(int a = 0; a < 2; a++) polje[i++] = cont2[a];
    for(int a = 0; a < 4; a++) polje[i++] = cont3[a];
    for(int a = 0; a < 4; a++) polje[i++] = cont4[a];
    
    int suma = 0;
    for(int s = 0; s < 13; s++) {
        suma += polje[s];
        cout << polje[s] << " ";
    }
    cout << endl;
    cout << "Suma svih elemenata svih containera je: " << suma << endl;
    delete [] polje;
    return 0;
}