#include "Menu.h"


void Menu::menu() {
    string commands[100];
    for(int i = 0; i < 100; i++){
        commands[i] = "";
    }
    Parser parser = *new Parser(&contactsGroup, commands);
    Reports reports = *new Reports(&contactsGroup, commands);

    string line, line2;
    int option;
    do{
        cout << "\nSISTEMA DE GESTION DE CONTACTOS______________________________________" << endl;
        cout << "1. Terminal\n2. Reportes\n3. Graficas\n4. Exportacion\n5. Salir" << endl;
        cin >> line;
        option = validateNum(line);

        switch (option) {
            case 1:
                parser.console();
                break;
            case 2:
                reports.reportsMenu();
                break;
            case 3:
                graphs();
                break;
            case 4:
                exportation();
                break;
        }
    } while (option != 5);
}

void Menu::graphs() {
    int option;
    string line;
    cout << "1. Grafica global.\n2. Grafica simple de un grupo\n3. Grafica de un grupo"  << endl;
    cin >> line;
    option = validateNum(line);
    if(option == 1){
        contactsGroup.graphviz();
        cout << "Grafica global generada." << endl;
    }
    else if(option == 2){
        cout << "Ingresa la llave del grupo de contacto: "  << endl;
        cin >> line;
        contactsGroup.graphviz2(line);
        cout << "Grafica de grupo simple generada." << endl;
    }
    else if(option == 3){
        cout << "Ingresa la llave del grupo de contacto: "  << endl;
        cin >> line;
        contactsGroup.graphviz3(line);
        cout << "Grafica de grupo." << endl;
    }
}

void Menu::exportation() {
    string line;
    cout << "Ingresa la llave del grupo de contactos que quieres exportar: " << endl;
    cin >> line;
    if(contactsGroup.search(line)) contactsGroup.search(line)->exportContacts(line);
}

int Menu::validateNum(const string& str) {
    try{
        return stoi(str);
    }
    catch(const invalid_argument& e){
        cout << "Escribe un numero porfavor\n" << endl;
        return -1;
    }
}