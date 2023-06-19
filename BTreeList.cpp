#include <iostream>
#include <vector>

using namespace std;

typedef unsigned Node; // Nodes are array indices!
typedef int Elem; // elements in the nodes are simple integers
typedef vector<Elem> NodeList; // list of nodes

class CompleteBinaryTree
{
public:
    NodeList _N;
    unsigned _size;
public:
    CompleteBinaryTree(NodeList& _N):_N(_N), _size(_N.size()-1){}

    // getters
    Node left(Node i){ return 2*i; }
    Node right(Node i){ return 2*i+1; }
    Node parent(Node i){ return i/2;  } // integer division!
    Elem& element(Node i){ return _N[i]; }
    Node root() { return 1; }
    unsigned size(){ return _size; }

    // setters
    bool updateLeft(Node i, Elem e); // set left child of Node i and return True, otherwise return False
    bool updateRight(Node i, Elem e); // set right child of Node i and return T, otherwise return F
    bool updateParent(Node i, Elem e); // set parent of Node i and return T, otherwise return F

    bool empty() { return _size == 0; }  // return True if tree is empty
    bool isLeaf(Node i){ return left(i) > _size; } // return True if leaf node
    void postorderPrint(Node i);
};

void CompleteBinaryTree::postorderPrint(Node i)
{
    // left, right, root traversal
    if (i > _size)
        return;
    postorderPrint(left(i));
    postorderPrint(right(i));
    cout <<  _N[i] << "  ";
}

bool CompleteBinaryTree::updateLeft(Node i, Elem e)
{
    if (i == 0 || i> _size || left(i) > _size)
        return false; // either Node i or left(i) doesn't exist in current tree
    else
    {
        _N[left(i)] = e;
        return true;
    }
}
bool CompleteBinaryTree::updateRight(Node i, Elem e){
    if (i == 0 || i> _size || right(i) > _size)
        return false; // either Node i or right(i) doesn't exist in current tree
    else
    {
        _N[right(i)] = e;
        return true;
    }
}
bool CompleteBinaryTree::updateParent(Node i, Elem e)
{
    if (i <= 1 || i> _size )
        return false; // either Node i doesn't exist in current tree or Node i is root
    else
    {
        _N[parent(i)] = e;
        return true;
    }
}
int main() {

    NodeList L;
    L.push_back(-1); // first place is not used!!! Dummy push_back!
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);
    L.push_back(5);
    L.push_back(6);
    L.push_back(7);

    CompleteBinaryTree T(L);
    cout << "T contains: " << T.size() << " nodes" << endl;

    T.postorderPrint(T.root());
    cout << endl;

    T.updateLeft(2, -4);
    T.updateRight(2, -5);
    T.updateParent(2, -1);

    T.postorderPrint(T.root());


}