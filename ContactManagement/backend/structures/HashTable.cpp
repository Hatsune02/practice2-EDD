#include "HashTable.h"

HashTable::HashTable() {
    size = 0;
    keys = new string[tableSize];
    values = new HashTableData*[tableSize];
    for(int i = 0; i < tableSize; i++){
        keys[i] = "";
        values[i] = nullptr;
    }
}

HashTable::~HashTable() {
    delete[] keys;
    delete[] values;
}

int HashTable::hash(string &key, int sizeT) {
    int sum = 0;
    for(char c : key){
        sum+= static_cast<int>(c);
    }
    return sum % sizeT;
}

void HashTable::rehash() {
    const int NEW_SIZE = tableSize * 2;
    auto* newKeys =  new string[NEW_SIZE];
    auto** newValues = new HashTableData*[NEW_SIZE];

    for(int i = 0; i < tableSize; i++){
        if(!keys[i].empty()){
            int newIndex = hash(keys[i], NEW_SIZE);
            newKeys[newIndex] = keys[i];
            newValues[newIndex] = values[i];
        }
    }

    delete[] keys;
    delete[] values;

    keys = newKeys;
    values = newValues;
    size = tableSize;
    tableSize = NEW_SIZE;
}

void HashTable::insert(string key) {
    if(static_cast<double>(size) / tableSize > 0.6){
        rehash();
    }
    string line;
    int option;
    int index = hash(key, tableSize);

    if(!keys[index].empty()){
        cout << "La funcion hash devuelve un valor ya ocupado. ¿Deseas reemplazarlo?\n1: Si    Cualquiero otro: No" << endl;
        cin >> line;
        option = validateNum(line);
        if(option == 1){
            keys[index] = key;
            values[index] = new HashTableData();
            size++;
            cout << "GRUPO <" << key << ", " << index << ">" << endl;
        }
    }
    else{
        keys[index] = key;
        values[index] = new HashTableData();
        size++;
        cout << "GRUPO <" << key << ", " << index << ">" << endl;
    }

}

HashTableData *HashTable::search(string key) {
    int index = hash(key, tableSize);

    if(keys[index] == key) return values[index];
    else cout << "Llave no encontrada (grupos): " << key << endl;
    return nullptr;
}

//REPORTS
void HashTable::printContactsPerGroup() {
    for (int i = 0; i < tableSize; ++i) {
        if (values[i] != nullptr) {
            cout << keys[i] << ": " << (values[i]->getContacts() - 1) << " contactos" << endl;
        }
    }
}
void HashTable::printDataPerGroup() {
    int x;
    for (int i = 0; i < tableSize; ++i) {
        if (values[i] != nullptr) {
            x = (values[i]->getContacts() - 1) * values[i]->getSizeValuesTree();
            cout << "El grupo <" << keys[i] << "> posee " << x << " datos" << endl;
        }
    }
}
void HashTable::printDataPerType() {
    int aux;
    int integers = 0, strings = 0, chars = 0, dates = 0;
    for (int i = 0; i < tableSize; ++i) {
        if (values[i] != nullptr) {
            aux = values[i]->integers;
            integers += aux;
            cout << "El grupo <" << keys[i] << "> posee:\n\t" << aux << " datos INTEGER" << endl;
            aux = values[i]->strings;
            strings += aux;
            cout << "\t" << aux << " datos STRING" << endl;
            aux = values[i]->chars;
            chars += aux;
            cout << "\t" << aux << " datos CHAR" << endl;
            aux = values[i]->dates;
            dates += aux;
            cout << "\t" << aux << " datos DATE\n" << endl;
        }
    }
    cout << "La cantidad de datos de todo el sistema es de: " << (integers+strings+chars+dates) << endl;
    cout << "\t" << integers << " datos INTEGER" << endl;
    cout << "\t" << strings << " datos STRING" << endl;
    cout << "\t" << chars << " datos CHAR" << endl;
    cout << "\t" << dates << " datos DATE" << endl;

}
void HashTable::printAllData() {
    int x = 0;
    for (int i = 0; i < tableSize; ++i) {
        if (values[i] != nullptr) {
            x += (values[i]->getContacts() - 1) * values[i]->getSizeValuesTree();
        }
    }
    cout << "La cantidad de datos de todo el sistema es de: " << x << endl;
}

//GRAPHICS
void HashTable::graphviz() {
    ofstream file("../EstructuraTotal.dot");
    if (!file) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    file << "digraph HashTable {\n";
    file << "  rankdir=LR;\n";

    for (int i = tableSize - 1; i >= 0; --i) {
        if (values[i] != nullptr) {
            file << "  " << keys[i] << " -> " << i << "\n";
            values[i]->graphHashTable(file, i, keys[i]);
            file << "\n";
        }
    }
    file << "  Key -> Index -> Key2 -> Index2 -> AVL\n";
    file << "}\n";
    file.close();

    string command = "dot -Tpng ../EstructuraTotal.dot -o ../EstructuraTotal.png";
    system(command.c_str());
}
void HashTable::graphviz2(const string& key) {
    if(search(key)){
        ofstream file("../" + key + "_2.dot");
        if (!file) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return;
        }

        file << "digraph HashTable {\n";
        file << "  rankdir=LR;\n";

        for (int i = tableSize - 1; i >= 0; --i) {
            if (values[i] == search(key)) {
                file << "  " << keys[i] << " -> " << i << "\n";
                values[i]->graphHashTable1(file, i);
                file << "\n";
                break;
            }
        }
        file << "  Key -> Index -> Key2 -> Index2\n";
        file << "}\n";
        file.close();

        string command = "dot -Tpng ../"+key+"_2.dot -o ../"+key+"_2.png";
        system(command.c_str());
    }
}
void HashTable::graphviz3(const string& key) {
    if(search(key)){
        ofstream file("../" + key + "_3.dot");
        if (!file) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return;
        }

        file << "digraph HashTable {\n";
        file << "  rankdir=LR;\n";


        for (int i = tableSize - 1; i >= 0; --i) {
            if (values[i] == search(key)) {
                file << "  " << keys[i] << " -> " << i << "\n";
                values[i]->graphHashTable2(file, i, keys[i]);
                file << "\n";
                break;
            }
        }
        file << "  Key -> Index -> Key2 -> Index2 -> AVL\n";
        file << "}\n";
        file.close();

        string command = "dot -Tpng ../"+key+"_3.dot -o ../"+key+"_3.png";
        system(command.c_str());
    }
}


int HashTable::validateNum(const string& str) {
    try{
        return stoi(str);
    }
    catch(const invalid_argument& e){
        cout << "Escribe un numero porfavor\n" << endl;
        return -1;
    }
}