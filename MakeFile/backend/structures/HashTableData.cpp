
#include "HashTableData.h"

HashTableData::HashTableData() {
    size = 0;
    keys = new string[tableSize];
    values = new AVLTree *[tableSize];
    for(int i = 0; i < tableSize; i++){
        keys[i] = "";
        values[i] = nullptr;
    }
}

HashTableData::~HashTableData() {
    delete[] valuesTree;
    delete[] keys;
    delete[] values;
}

int HashTableData::hash(string &key, int sizeT) {
    int sum = 0;
    for(char c : key){
        sum+= static_cast<int>(c);
    }
    return sum % sizeT;
}

void HashTableData::rehash() {
    const int NEW_SIZE = tableSize * 2;
    auto* newKeys =  new string[NEW_SIZE];
    auto** newValues = new AVLTree*[NEW_SIZE];

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

void HashTableData::insert(string key, int type) {
    if(static_cast<double>(size) / tableSize > 0.6){
        cout << "Realizo rehash" << endl;
        rehash();
    }
    string line;
    int option;
    int index = hash(key, tableSize);

    if(!keys[index].empty()) {
        cout << "La funcion hash devuelve un valor ya ocupado. ¿Deseas reemplazarlo?\n1: Si    Cualquiero otro: No"
             << endl;
        cin >> line;
        option = validateNum(line);
        if(option == 1){
            keys[index] = key;
            values[index] = new AVLTree(type);
            size++;

            cout << "CONTACTOS <" << key << ", " << index << ">" << endl;
        }
    }
    else{
        keys[index] = key;
        values[index] = new AVLTree(type);
        size++;

        cout << "CONTACTOS <" << key << ", " << index << ">" << endl;
    }

}

void HashTableData::insertContact(string *data) {
    AVLTree *aux;
    cout << "Contacto añadido correctamente. -> ";
    for(int i = 0; i < sizeValuesTree; i++) {
        aux = search(valuesTree[i]);
        cout << valuesTree[i] << " " << data[i] << " ";
        if (aux) {
            aux->insert(contacts, data[i]);
            if(aux->getType() == 1) integers++;
            else if(aux->getType() == 2) strings++;
            else if(aux->getType() == 3) chars++;
            else if(aux->getType() == 4) dates++;
        }
    }
    cout << endl;
    contacts++;
}

AVLTree *HashTableData::search(string key) {
    int index = hash(key, tableSize);

    if(keys[index] == key) return values[index];
    else cout << "No se encontro la llave (campos): " << key << endl;
    return nullptr;
}

void HashTableData::all() {
    for(int i = 0; i < sizeValuesTree; i++) {
        if (search(valuesTree[i])) {
            cout << valuesTree[i] << endl;
            search(valuesTree[i])->print();
        }
    }
}
void HashTableData::searchContacts(const string& key, const string& value) {
    if(search(key)){
        int arrKeys[100];
        int arrSize = 0;
        search(key)->inOrderComparison(value, arrKeys, arrSize);
        string info;
        for(int i = 0; i < arrSize; i++){
            cout << "Contacto " << i+1 << endl;
            for(int j = 0; j < sizeValuesTree; j++) {
                if (search(valuesTree[j])) {
                    info = search(valuesTree[j])->search(arrKeys[i]);
                    cout << "\t" << valuesTree[j] << ": " << info << endl;
                }
            }
        }
    }
}

void HashTableData::setArrValues(string *arr, int s) {
    valuesTree = new string[s];
    sizeValuesTree = s;
    for(int i = 0; i < sizeValuesTree; i++) {
        valuesTree[i] = arr[i];
    }
}
int HashTableData::getContacts() {
    return contacts;
}
int HashTableData::getSizeValuesTree() {
    return sizeValuesTree;
}

//GRAPHS
void HashTableData::graphHashTable(ofstream &file, int index, const string &k) {
    for (int i = 0; i < tableSize; i++) {
        if (values[i] != nullptr) {
            file << "  " << index << " -> \n";
            file << "  " << k << "_" << keys[i] << " -> index"<< k << i << " -> \n";
            values[i]->printTree(file, k);
            file << "\n";
        }
    }
}
void HashTableData::graphHashTable1(ofstream &file, int index) {
    for (int i = tableSize - 1; i >= 0; --i) {
        if (values[i] != nullptr) {
            file << "  " << index << " -> \n";
            file << "  " << keys[i] << " -> index" << i << ";\n";
            file << "\n";
        }
    }
}
void HashTableData::graphHashTable2(ofstream &file, int index, const string &k) {
    for (int i = 0; i < tableSize; i++) {
        if (values[i] != nullptr) {
            file << "  " << index << " -> \n";
            file << "  " << keys[i] << " -> index"<< i << " -> \n";
            values[i]->printTree(file, k);
            file << "\n";
        }
    }
}

//EXPORT
void HashTableData::exportContacts(const string& fileName) {
    int arrKeys[100];
    int arrSize = 0;
    for(int i = 0; i < sizeValuesTree; i++) {
        if (search(valuesTree[i])) {
            search(valuesTree[i])->inOrder(arrKeys, arrSize);
            break;
        }
    }

    string info;
    string txt;
    for(int i = 0; i < arrSize; i++){
        txt = "Contacto " + to_string(i+1);
        for(int j = 0; j < sizeValuesTree; j++) {
            if (search(valuesTree[j])) {
                info = search(valuesTree[j])->search(arrKeys[i]);
                txt += "\n\t" + valuesTree[j] + ": " + info;
            }
        }
        createTxt(fileName, txt, i+1);
    }
}
void HashTableData::createTxt(const string &fileName, const string &content, int index) {
    string path = "../" + fileName;
    if (!fs::exists(path)) {
        fs::create_directory(path);
    }

    string filePath = path + "/contacto" + to_string(index) + ".txt";
    ofstream file(filePath);
    if (file.is_open()) {
        file << content;
        file.close();
    } else {
       cerr << "No se pudo abrir el archivo " << filePath << endl;
    }

    cout << "Archivo creado exitosamente." << endl;
}

int HashTableData::validateNum(const string& str) {
    try{
        return stoi(str);
    }
    catch(const invalid_argument& e){
        cout << "Escribe un numero porfavor\n" << endl;
        return -1;
    }
}
