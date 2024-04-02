
#ifndef CONTACTMANAGEMENT_REPORTS_H
#define CONTACTMANAGEMENT_REPORTS_H
#include "structures/HashTable.h"
#include "structures/HashTableData.h"

class Reports {
private:
    HashTable *contactGroups;
    string *commands;

    void dataPerGroup();
    void allData();
    void report3();
    void contactsPerGroup();
    void logFile();
    int validateNum(const string&);
public:
    Reports(HashTable*,string*);
    void reportsMenu();

};


#endif //CONTACTMANAGEMENT_REPORTS_H
