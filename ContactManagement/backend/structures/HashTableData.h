#ifndef CONTACTMANAGEMENT_HASHTABLEDATA_H
#define CONTACTMANAGEMENT_HASHTABLEDATA_H
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "AVLTree.h"
using namespace std;
namespace fs = std::filesystem;
class HashTableData {
private:
    int tableSize = 5;
    int contacts = 1;
    string* keys;
    AVLTree** values;
    string* valuesTree;
    int size, sizeValuesTree;

    int hash(string&, int);
    void rehash();
public:
    int integers = 0,strings = 0,chars = 0,dates = 0;

    HashTableData();
    ~HashTableData();
    void insert(string, int);
    void insertContact(string[]);
    AVLTree* search(string);
    void all();
    void searchContacts(const string&, const string&);

    void setArrValues(string[], int);
    int getContacts();
    int getSizeValuesTree();

    void graphHashTable(ofstream&, int, const string&);
    void graphHashTable1(ofstream&, int);
    void graphHashTable2(ofstream&, int, const string&);

    void exportContacts(const string&);
    void createTxt(const string&, const string&, int);

    int validateNum(const string&);
};


#endif //CONTACTMANAGEMENT_HASHTABLEDATA_H
