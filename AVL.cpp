#include <iostream>
using namespace std;

// Pokusao sam i na stack overflow... nisu mi uspjeli pomoci :(

class Node{ // WORKS
    public:
        Node *left, *right, *parent;
        int elem, height;

        Node(Node* l, Node* r, Node* p, int x, int h): left(l), right(r), parent(p), elem(x), height(h){}
        ~Node(){};
};

ostream&operator<<(ostream& os, const Node &n){  // WORKS
    os << "Node: " << n.left << ", " << n.right << ", " << n.parent << ", " << n.elem << ", " << n.height << ", my adress: " << &n << endl;
    return os;
}

class AVL{
    public:
        Node* root{};
        AVL(){};
        ~AVL(){Destructor(root);}
        void Destructor(Node* node){
            if (node){
                Destructor(node->left);
                Destructor(node->right);
                delete node;
            }
        }
        void inorder(Node* node){ // WORKS
            if(node!=nullptr){
                inorder(node->left);
                cout << node->elem << " ";
                inorder(node->right);
            }
        }
        int minimum(Node* node){ // WORKS
            if(node->left!= nullptr) return minimum(node->left);
            return node->elem;
        }
        int maximum(Node* node){ // WORKS
            if(node->right!= nullptr) return maximum(node->right);
            return node->elem;
        }
        Node* predacessor(Node* node);
        Node* successor(Node* node);
        int height(Node* node){ 
            if(node == nullptr) return 0;
            return node->height;
        }
        int balance(Node* node){
            // cout << *node;
            int l_height = height(node->left);
            int r_height = height(node->right);
            int b_factor = l_height - r_height;
            // cout << ", Balance: " << b_factor << endl;
            return abs(b_factor);
        }
        Node* Insert(int x){ // inserting like its BST then checking for AVL proporties
            cout << "-------------------------------------------------------" << endl;
            cout << "Insert: " << x << endl;
            Node* current;
            if(root == nullptr){
                cout << "Importing root" << endl;
                Node* n = new Node( nullptr, nullptr, nullptr, x, 0);
                cout << *n;
                root = n;
            }else{
                Node* iter = root;
                while(iter != nullptr){
                    current = iter;
                    if(x > current->elem){
                        iter = iter->right;
                    }else{
                        iter = iter->left;
                    }
                }
                Node* n = new Node(nullptr, nullptr, current, x, current->height + 1);
                cout << *n ;
                cout << "Parent " << current->elem;
                if(x > current->elem){
                    current->right = n;
                    cout << " child right: " << n->elem << endl; 
                }else{
                    current->left = n;
                    cout << " child left: " << n->elem << endl;
                }
                // find one that makes AVL unbalanced then rotate
                Node* node = to_rotate(root);
                cout << "For node: " << current->elem << " Balance: " << balance(current) << endl;
                cout << "before if" << endl;
                if(node != nullptr){ 
                    cout << "in rotation if! " << endl;
                    if(node->right->height > node->left->height){
                        leftRotate(node);
                    }else if(node->right->height < node->left->height){
                        rightRotate(node);
                    }
                }
                
            }
        };

        Node* to_rotate(Node* node){ // find node that makes AVL unbalanced
            if(balance(node) > 1 || node == nullptr){
                cout << "to_rotate" << endl;
                return node;
            }
            to_rotate(node->left);
            to_rotate(node->right);
        }

        void Delete(Node* node);

        void rightRotate(Node* &x){
            cout << "rightRotate: " << x->elem << endl;
            Node* y = x->left;
            Node* T = y->right;
            x->left = T;
            if(y->right != nullptr) y->right->parent = x;

            y->parent = x->parent;

            if(x->parent == nullptr){
                root = y;
            }else if(x = x->parent->right){
                x->parent->right = y;
            }else{
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
        }
        void leftRotate(Node* &x){
            cout << "leftRotate: " << x->elem << endl;
            Node* y = x->right;
            Node* T = y->left;
            x->right = T;
            if(y->left != nullptr) y->left->parent = x;

            y->parent = x->parent;

            if(x->parent == nullptr){
                root = y;
            }else if(x == x->parent->left){
                x->parent->left = y;
            }else{
                x->parent->right = y;
            }   
            y->left = x;
            x->parent = y; 
        }
        
};

int main(){
    cout << "In main: " << endl;
    AVL avl;
    avl.Insert(1);
    avl.Insert(4);
    avl.Insert(9);
    avl.Insert(2);
    
    avl.inorder(avl.root);
    // cout << "Minimum: " << avl.minimum(avl.root) << endl;
    // cout << "Maximum: "<< avl.maximum(avl.root) << endl;
    

    return 0;
}