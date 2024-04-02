//
// Created by dog on 25/03/24.
//

#ifndef CONTACTMANAGEMENT_AVLTREE_H
#define CONTACTMANAGEMENT_AVLTREE_H
#include <iostream>
#include <fstream>
#include "Node.h"

class AVLTree {
private:
    Node *root;
    int type;
    int getHeight(Node *node);
    int getBalanceFactor(Node* node);

    Node* rightRotate(Node*);
    Node* leftRotate(Node*);
    Node* newNode(int, string);
    Node* insert(Node*, int, const string&);
    Node* search(Node*, int);
    void print(Node*, string, bool);
    void inOrder(Node*, int[], int&);
    void inOrderComparison(Node*, const string&, int[], int&);

    void graphviz(Node*, ofstream&, const string&);
public:
    AVLTree(int);
    ~AVLTree();
    void deleteTree(Node*);
    void insert(int, const string&);
    string search(int);
    void inOrder(int[], int&);
    void inOrderComparison(const string&, int[], int&);

    void print();
    void printTree(ofstream&, const string&);
    Node* getRoot();
    int getType();
};


#endif //CONTACTMANAGEMENT_AVLTREE_H
