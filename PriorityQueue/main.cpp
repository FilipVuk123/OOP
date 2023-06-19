#include "MinPriorityQueue.h"


template <typename K, typename V>
ostream& operator<<(ostream& os, const pair<K, V>& p) {
    return os << "K: " << p.first << ", V: " << p.second << "\t";
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const MinPriorityQueue<K, V>& mpq) {
    os << "Priority queue: " << endl;

    MinPriorityQueue<K, V> mpq2{mpq};

    while (!mpq2.tree.empty())
        os << mpq2.extractMin() << "\t";
    return os << endl << endl;

}

int main() {

    MinPriorityQueue<int, string> mp{};
    mp.insert({1, "osoba4"});
    mp.insert({2, "osoba7"});
    mp.insert({7, "osoba5"});
    mp.insert({8, "osoba1"});
    mp.insert({5, "osoba6"});
    cout << mp;
    mp.insert({6, "osoba9"});
    cout << mp;
    mp.extractMin();
    cout << mp;
    mp.decreaseKey(2, 4);
    cout << mp;

    return 0;
}