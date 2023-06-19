#include <iostream>
#include <list>
#include <vector>

using namespace std;

unsigned int modHash(const string& str) {
    unsigned int acc{0};
    for(const char& c: str) acc += c % 256;
    return acc % 256;
}

template <typename T, size_t S>
struct HashTable {
    list<pair<const string, T>> container[S];

    template <typename... Args>
    void insert(const string& key, Args... args) {
        list<pair<const string, T>>& appropriateList = container[modHash(key)];
        appropriateList.push_back(pair<const string, T>{key, T{args...}});
    }

    T search(const string& key) {
        const list<pair<const string, T>>& appropriateList = container[modHash(key)];
        for(const pair<const string, T>& el: appropriateList)
            if (el.first == key)
                return el.second;
        return T{};
    }

    void remove(const string& key) {
        container[modHash(key)].remove_if([&key](const pair<const string, T>& el) { return el.first == key ; });
    }


};

struct ID {
    const string email;
    unsigned int age;
};

ostream& operator<<(ostream& os, const ID& id) {
    return os << "Email: " << id.email << "; age: " << id.age << endl;
}

int main() {

    HashTable<ID, 256> ht{};

    ht.insert("Jurica", "jmaltar02@mathos.hr", 26u);
    ht.insert("Pero", "pero@mathos.hr", 27u);
    ht.insert("Ivo", "ivo@mathos.hr", 28u);

    cout << ht.search("Pero");

    return 0;
}