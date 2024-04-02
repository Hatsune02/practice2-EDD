#ifndef CONTACTMANAGEMENT_HASHTABLE_H
#define CONTACTMANAGEMENT_HASHTABLE_H
#include <iostream>
#include <string>
#include "HashTableData.h"
using namespace std;

class HashTable {
private:
    int tableSize = 5;
    string* keys;
    HashTableData** values;
    int size;

    int hash(string&, int);
    void rehash();
public:
    HashTable();
    ~HashTable();
    void insert(string);
    HashTableData* search(string);
    //REPORTS
    void printContactsPerGroup();
    void printDataPerGroup();
    void printDataPerType();
    void printAllData();

    void graphviz();
    void graphviz2(const string&);
    void graphviz3(const string&);

    int validateNum(const string&);
};


#endif //CONTACTMANAGEMENT_HASHTABLE_H
