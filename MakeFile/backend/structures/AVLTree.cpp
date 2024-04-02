#include "AVLTree.h"

AVLTree::AVLTree(int t) {
    root = nullptr;
    type = t;
}
AVLTree::~AVLTree() {
    deleteTree(root);
    root = nullptr;
}
void AVLTree::deleteTree(Node *node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int AVLTree::getHeight(Node *node) {
    if(node == nullptr) return 0;
    return node->height;
}
int AVLTree::getBalanceFactor(Node *node) {
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* aux = x->right;

    x->right = y;
    y->left = aux;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* aux = y->left;

    y->left = x;
    x->right = aux;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node *AVLTree::newNode(int key, string value) {
    Node *node = new Node();
    node->key = key;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

Node *AVLTree::insert(Node *node , int key, const string& value) {
    if(node == nullptr) return newNode(key, value);

    if(key < node->key) node->left = insert(node->left, key, value);
    else if(key > node->key) node->right = insert(node->right, key, value);
    else return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balanceFactor < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balanceFactor > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(int key, const string& value) {
    root = insert(root, key, value);
}

Node *AVLTree::search(Node *node, int key) {
    if (node == nullptr || node->key == key) return node;

    // Si la clave es menor que la clave de la raíz, buscar en el subárbol izquierdo
    if (key < node->key) return search(node->left, key);

    // Si la clave es mayor que la clave de la raíz, buscar en el subárbol derecho
    return search(node->right, key);
}

string AVLTree::search(int key) {
    if(search(root,key)) return search(root,key)->value;
    return "";
}

void AVLTree::inOrder(Node *node, int *keys, int &index) {
    if (node == nullptr) return;
    inOrder(node->left, keys, index);
    keys[index++] = node->key;
    inOrder(node->right,keys, index);
}
void AVLTree::inOrder(int *keys, int &index) {
    inOrder(root, keys, index);
}

void AVLTree::inOrderComparison(Node *node, const string &targetValue, int *keys, int &index) {
    if (node == nullptr) return;
    inOrderComparison(node->left, targetValue, keys, index);
    if (node->value == targetValue) {
        keys[index++] = node->key;
    }
    inOrderComparison(node->right, targetValue, keys, index);
}
void AVLTree::inOrderComparison(const string &targetValue, int *keys, int &index) {
    inOrderComparison(root, targetValue, keys, index);
}

void AVLTree::print(Node *node ,string indent, bool last) {
    if (node != nullptr) {
        cout << indent;
        if (last) {
            cout << "└─";
            indent += "  ";
        } else {
            cout << "├─";
            indent += "| ";
        }
        cout << node->value << endl;

        print(node->left, indent, false);
        print(node->right, indent, true);
    }
}

void AVLTree::print() {
    print(root, "", true);
}

void AVLTree::graphviz(Node *node, ofstream &file, const string& k) {
    if (node == nullptr) return;

    if (node->left != nullptr) {
        file << "  " << k << node->key << "_" << node->value <<  " -> " << k << node->left->key << "_" << node->left->value << ";\n";
        graphviz(node->left, file, k);
    }

    if (node->right != nullptr) {
        file << "  " << k << node->key << "_" << node->value << " -> " << k << node->right->key << "_" << node->right->value << ";\n";
        graphviz(node->right, file, k);
    }
}

void AVLTree::printTree(ofstream &file, const string &k) {
    graphviz(root, file, k);
}

Node *AVLTree::getRoot() {
    return root;
}

int AVLTree::getType() {
    return type;
}
