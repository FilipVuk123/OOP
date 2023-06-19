//
// Created by Jurica on 4/16/2018.
//

#ifndef MINPRIORITYQUEUE_MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_MINPRIORITYQUEUE_H

#include "CompleteBinaryTree.h"

#include <limits>
#include <random>
#include <math.h>

template <typename K, typename V>
class MinPriorityQueue {
public:
    CompleteBinaryTree<K, V> tree;
    MinPriorityQueue();
    MinPriorityQueue(const MinPriorityQueue&);

    void downHeap(Node i);
    void upHeap(Node i);

    // s obzirom na prosljeđeni vektor, izgrađujemo prioritetni red
    // (pretpostavljamo da je prioritetni red prazan, ili pregazimo
    // sve dosad pohranjene parove)
    void buildMinHeap(const vector<pair<K, V>>& L);

    V minimum();
    V extractMin();
    void decreaseKey(Node i, K key);
    void insert(const pair<K, V>& v);
};

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(): tree{} {}

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(const MinPriorityQueue& mpq): tree{mpq.tree.N} {}

template <typename K, typename V>
V MinPriorityQueue<K, V>::minimum() { return tree.N.front().second; }

template <typename K, typename V>
V MinPriorityQueue<K, V>::extractMin() {
    if(tree.empty())
        0; // throw exception
    else {
        V value{minimum()};
        tree[0] = tree[tree.getSize() - 1];
        tree.setSize(tree.getSize() - 1);
        tree.N.pop_back();
        downHeap(0);
        return value;

    }
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::downHeap(Node i) {
    Node l{tree.left(i)};
    Node r{tree.right(i)};

    Node smallest{};

    if (l < tree.getSize() && tree[l].first < tree[i].first) smallest = l;
    else smallest = i;

    if (r < tree.getSize() && tree[r].first < tree[smallest].first) smallest = r;

    if (smallest != i) {
        tree.swapNodes(i, smallest);
        downHeap(smallest);
    }

}

template <typename K, typename V>
void MinPriorityQueue<K, V>::upHeap(Node i) {


    K tpf, tf;
    if(i > 0) {
        tpf = tree[tree.parent(i)].first;
        tf = tree[i].first;
    } else
        return;




    while (i > 0 && tree[tree.parent(i)].first > tree[i].first) {
        tree.swapNodes(tree.parent(i), i);
        i = tree.parent(i);
    }
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::decreaseKey(Node i, K key) {
    if(i >= tree.getSize() || key > tree[i].first) {
        //throw exception
        return;
    }
    tree[i].first = key;
    upHeap(i);
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::insert(const pair<K, V>& v) {
    tree.setSize(tree.getSize() + 1);
    tree.N.push_back(pair<K, V>{numeric_limits<K>::max(), v.second});
    decreaseKey(tree.getSize() - 1, v.first);
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::buildMinHeap(const vector<pair<K, V>>& L) {
    tree.N = L;
    tree.setSize(L.size());

    for(unsigned int i{tree.getSize() / 2u - 1}; i >= 0u; --i)
        downHeap(i);
}

#endif //MINPRIORITYQUEUE_MINPRIORITYQUEUE_H
