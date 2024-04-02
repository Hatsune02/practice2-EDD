
#ifndef CONTACTMANAGEMENT_PARSER_H
#define CONTACTMANAGEMENT_PARSER_H
#include "structures/HashTable.h"
#include "structures/HashTableData.h"
#include <regex>
#include <ctime>

class Parser {
private:
    HashTable *contactGroups;
    string *commands;

    void split(const string&, string[], int&);
    void addGroup(const string&, string[]);
    void addContact(const string&, string[]);
    void searchContact(const string&, const string&);
    string obtainDate();
    int getType(const string&);
public:
    Parser(HashTable*, string*);
    void console();
};


#endif //CONTACTMANAGEMENT_PARSER_H
