//
// Created by dog on 25/03/24.
//

#ifndef CONTACTMANAGEMENT_NODE_H
#define CONTACTMANAGEMENT_NODE_H
#include <string>
using namespace std;

class Node {
public:
    int key;
    string value;
    Node *left;
    Node *right;
    int height;
};


#endif //CONTACTMANAGEMENT_NODE_H
