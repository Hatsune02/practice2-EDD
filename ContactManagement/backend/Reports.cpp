
#include "Reports.h"

Reports::Reports(HashTable* cG, string* c) {
    contactGroups = cG;
    commands = c;
}

void Reports::dataPerGroup() {
    //Multplicar contactos * sizeValuesTree
    contactGroups->printDataPerGroup();
}

void Reports::allData() {
    //El mismo ciclo para contactGroups y hacer contactos*sizeValuesTree para cada uno del ciclo.
    contactGroups->printAllData();
}

void Reports::report3() {
    contactGroups->printDataPerType();
}

void Reports::contactsPerGroup() {
    contactGroups->printContactsPerGroup();
}

void Reports::logFile() {
    for(int i = 0; i < 100; i++){
        if(commands[i].empty()) break;
        cout << i+1 << ". " << commands[i] << endl;
    }
}

void Reports::reportsMenu() {
    string line;
    int option1;
    do{
        cout << "REPORTE DE CONTACTOS______________________________________" << endl;
        cout << "1. Cantidad de datos por Grupo."
                "\n2. Cantidad de datos de todo el sistema."
                "\n3. Cantidad de datos por tipo."
                "\n4. Cantidad de Contactos por Grupo."
                "\n5. Archivo Log de sistema."
                "\n6. Salir." << endl;

        cin >> line;
        option1 = validateNum(line);

        switch (option1) {
            case 1:
                dataPerGroup();
                break;
            case 2:
                allData();
                break;
            case 3:
                report3();
                break;
            case 4:
                contactsPerGroup();
                break;
            case 5:
                logFile();
                break;
        }
    } while (option1 != 6);
}

int Reports::validateNum(const string& str) {
    try{
        return stoi(str);
    }
    catch(const invalid_argument& e){
        cout << "Escribe un numero porfavor\n" << endl;
        return -1;
    }
}