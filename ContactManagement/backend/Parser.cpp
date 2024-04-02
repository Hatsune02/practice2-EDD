#include "Parser.h"

Parser::Parser(HashTable *ht, string *c) {
    contactGroups = ht;
    commands = c;
}

void Parser::split(const string &input, string *words, int &wordCount) {
    regex wordRegex("[^\\(\\),;\\s]+");
    smatch match;
    wordCount = 0;

    string::const_iterator searchStart(input.cbegin());
    while (regex_search(searchStart, input.cend(), match, wordRegex)) {
        words[wordCount++] = match[0];
        searchStart = match.suffix().first;
    }
}

void Parser::console() {
    string line;
    cout << "" << endl;
    getline(cin, line);
    cout << "Escribe el comando:" << endl;
    getline(cin, line);
    string words[100];
    int wordCount;
    for(int i = 0; i < 100; i++){
        if(commands[i].empty()) {
            commands[i] = line + " " + obtainDate();
            break;
        }
    }
    split(line, words, wordCount);
    if(!words[0].empty() && !words[1].empty() && !words[2].empty()){
        if(words[0] == "ADD" && words[1] == "NEW-GROUP"){
            addGroup(words[2] ,words);
        }
        else if(words[0] == "ADD" && words[1] == "CONTACT" && words[2] == "IN"){
            addContact(words[3], words);
        }
        else if(words[0] == "FIND" && words[1] == "CONTACT" && words[2] == "IN"){
            searchContact(words[3], words[5]);
        }

        else cout << "ERROR SINTACTICO" << endl;
    }
    else cout << "ERROR" << endl;

}

void Parser::addGroup(const string &name, string *values) {
    contactGroups->insert(name);
    HashTableData *data = contactGroups->search(name);
    if(data){
        int countValues = 0, aux = 0;
        cout << "Grupo agregado correctamente!" << endl;
        for(int i = 4; i < 80; i = i+2){
            if(values[i].empty()) break;
            data->insert(values[i], getType(values[i+1]));
            countValues++;
        }
        string arr[countValues];
        for(int i = 4; i < 80; i = i+2){
            if(values[i].empty()) break;
            arr[aux] = values[i];
            aux++;
        }
        data->setArrValues(arr, countValues);
    }

}

void Parser::addContact(const string &name, string *values) {
    HashTableData *data = contactGroups->search(name);
    if(data){
        int countValues = 0;
        for(int i = 5; i < 80; i++){
            if(values[i].empty()) break;
            countValues++;
        }
        string arr[countValues];
        for(int i = 5; i < 5 + countValues; i++){
            arr[i-5] = values[i];
        }

        data->insertContact(arr);
    }

}

void Parser::searchContact(const string &name, const string &comp) {
    HashTableData *data = contactGroups->search(name);
    if(data){
        string key, value;
        size_t pos = comp.find('=');

        key = comp.substr(0, pos);
        value = comp.substr(pos + 1);
        cout << "GRUPO: " << name << endl;
        data->searchContacts(key, value);
    }
}


int Parser::getType(const string& word) {
    if(word == "INTEGER") return 1;
    else if(word == "STRING") return 2;
    else if(word == "CHAR") return 3;
    else if(word == "DATE") return 4;
    else return -1;
}

string Parser::obtainDate() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    // Crear un buffer para almacenar la fecha y hora formateada
    char buffer[80];

    // Formatear la fecha y hora actual en el buffer
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);

    // Convertir el buffer a un string
    string dateTime(buffer);

    return dateTime;
}
