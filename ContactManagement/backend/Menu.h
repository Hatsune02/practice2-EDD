
#ifndef CONTACTMANAGEMENT_MENU_H
#define CONTACTMANAGEMENT_MENU_H
#include "structures/HashTable.h"
#include "structures/HashTableData.h"
#include "Parser.h"
#include "Reports.h"

class Menu {
private:
    HashTable contactsGroup;
    void graphs();
    void exportation();
public:
    void menu();
    int validateNum(const string&);

};


#endif //CONTACTMANAGEMENT_MENU_H
