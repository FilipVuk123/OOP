    #include <iostream>
#include <list>
using namespace std;

class Node;

typedef list<Node*> NodeList;
typedef int Elem;




class Node
{
protected:
    Elem _elt;
    Node* _left;
    Node* _right;
    Node* _par;
public:
    Node(Elem e): _elt(e), _left(nullptr), _right(nullptr), _par(nullptr){}
    // setters
    void setLeft(Node *left)  { _left = left; }
    void setRight(Node *right) { _right = right; }
    void setParent(Node *par) { _par = par; }
    // getters
    Elem element() const { return _elt; }
    Node * left() const { return _left; }
    Node * right() const { return _right; }
    Node * parent() const  { return _par; }
    // predicates
    bool isRoot() const { return _par == nullptr; } // return True if root
    bool isLeaf() const { return (_left == nullptr) && (_right == nullptr); }  // return True if leaf

};

class BinaryTree
{
public:
    Node* _root;
    unsigned int _size;
public:
    BinaryTree():_root(nullptr), _size(0){}
    Node* root(){ return _root; }
    unsigned size() { return _size ; }

    bool addRoot(Elem e); // add root to the empty tree
    bool expandLeaves(Node *, Elem, Elem); // add leaves to leaf node

    void postorderPrint(Node*); // print nodes in postorder manner
    void preorderPrint(Node*); // print nodes in preorder manner

    void preorderTree(Node*, NodeList&); // save node pointer to NodeList in preorder fashion
    ~BinaryTree(); // delete tree, i.e. delete all nodes
};

void BinaryTree::preorderTree(Node* n, NodeList& L){

    if (n == nullptr)
        return;
    L.push_back(n);
    preorderTree(n->left(), L);
    preorderTree(n->right(), L);
}

BinaryTree::~BinaryTree()
{
    // collect all nodes in list of nodes
    NodeList L;
    preorderTree(_root, L);
    // delete them one by one
    for (auto n: L)
    {
        delete n;
    }
}
void BinaryTree::postorderPrint(Node *n){
    if (n == nullptr)
        return;

    postorderPrint(n->left());
    postorderPrint(n->right());
    cout << n->element() << "  " ;
}

void BinaryTree::preorderPrint(Node *n)
{
    if (n == nullptr)
        return;
    cout << n->element() << "  " ;
    preorderPrint(n->left());
    preorderPrint(n->right());
}
bool BinaryTree::addRoot(Elem e)
{
    if (_root != nullptr)
        return false;
    else
    {
        _root = new Node(e);
        _size = 1;
        return true;
    }
}

bool BinaryTree::expandLeaves(Node *n, Elem e1, Elem e2)
{
    if (n->left() != nullptr && n->right() != nullptr)
        return false;
    else
    {
        Node* n1 = new Node(e1);
        Node* n2 = new Node (e2);
        n->setLeft(n1);
        n1->setParent(n);
        n->setRight(n2);
        n2->setParent(n);
        _size += 2;
        return true;
    }
}


unsigned depth(const BinaryTree& T, const Node& n)
{
    if (n.isRoot())
        return 0;
    else
        return 1 + depth(T, *n.parent() );w

}

unsigned height(const BinaryTree& T, const Node& n)
{
    if (n.isLeaf())
        return 0;
    else
        return 1 + max(height(T, *n.left()), height(T, *n.right()));
}

int main() {
    Elem e = 1;
    Node n(e);

    BinaryTree T;
    T.addRoot(1);
    T.expandLeaves(T.root(), 2, 3);
    T.expandLeaves(T.root()->left(), 4, 5);

    T.preorderPrint(T.root());
    cout << endl;
    T.postorderPrint(T.root());
    cout << endl;

    cout << depth(T, *(T.root()->left()->left())) << endl;

    cout << height(T, *T.root()) << endl;
    cout << " Success !" << endl;

    return 0;
}