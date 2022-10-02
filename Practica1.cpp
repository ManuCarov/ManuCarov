#include <iostream>
#include <string>
#include <fstream>
#include "Node.h"
using namespace std;

void agregarUsuario(Node *_list, string _fileName)
{
    string user;
    string pass;

    cout << "Crea tu nombre de usuario:" << endl;
    cin >> user;
    cout << "Ingresa tu nueva contrasena:" << endl;
    cin >> pass;

    _list->insertInList(new Node(user, pass));
    cout << "Datos agregados a la lista";

    fstream file;
    string str;
    file.open(_fileName, ios_base::app);

    if (file.is_open())
    {
        file << "\n"
             << user;
        file << "\n"
             << pass;
        cout << "\nDatos agregados correctamente al archivo";
    }
    file.close();
}

void buscarUsuario(Node *_list)
{
    string user;
    string pass;

    cout << "Ingresa tu nombre de usuario a buscar:" << endl;
    cin >> user;
    cout << "Ingresa tu contraseña a buscar:" << endl;
    cin >> pass;

    if (_list->searchInList(user, pass))
    {
        cout << "Bienvenido " << user << endl;
    }
    else
    {
        cout << "No se encontró ese usuario" << endl;
    }
}

void eliminarUsuario(Node *_list, string _fileName)
{
    string user;
    string pass;
    string fileContent[100];
    int cont = 0;

    cout << "Ingresa nombre de usuario a eliminar:" << endl;
    cin >> user;
    cout << "Ingresa contraseña a eliminar:" << endl;
    cin >> pass;

    *_list = _list->deleteInList(user, pass);

    fstream file;
    file.open(_fileName, ios::in);

    if (file.is_open())
    {
        string line = "";
        while (getline(file, line))
        {
            fileContent[cont] = line;
            cont+=1;
        }
    }
    file.close();

    file.open(_fileName, ios::out);

    for (int i = 0; i < cont; i+=2)
    {
        if (fileContent[i] != user || fileContent[i+1] != pass){
            if (i != 0)
            {
                file << endl;
            }         
            file << fileContent[i] << endl;
            file << fileContent[i+1];
        }
    }
    
    file.close();
}

int main(int argc, char const *argv[])
{

#pragma region Creacion Lista con Datos del Txt

    int j = 0;
    fstream file;
    string fileName = "data.txt";
    string fileContent[100];

    file.open(fileName, ios::in);
    if (file.is_open()) // Ver si el archivo está abierto
    {
        string line = "";
        while (getline(file, line)) // Leer los datos y meterlos al string "line"
        {
            fileContent[j] = line;
            j += 1;
        }
    }
    else
    {
        cout << "Error al obtener el archivo";
        return 0;
    }

    file.close();

#pragma endregion

#pragma region Insertar Array en Lista Enlazada

    int fileLenght = j + 1;

    Node *head = new Node(fileContent[0], fileContent[1]);
    Node *list = head;

    for (int i = 2; i < fileLenght - 2; i += 2)
    {
        list->insertInList(new Node(fileContent[i], fileContent[i + 1]));
        list = list->getNext();
    }

#pragma endregion

#pragma region Menu

    string screenText = "";
    screenText += "=============================================\n";
    screenText += "Bienvenido. Que accion desea realizar?\n";
    screenText += "1. Ingresar un nuevo usuario\n";
    screenText += "2. Buscar usuario\n";
    screenText += "3. Eliminar usuario\n";
    screenText += "4. Mostrar lista\n";
    screenText += "=============================================\n";

    cout << screenText;

    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        cout << "ADICION USUARIO =============================================\n";
        agregarUsuario(head, fileName);
        break;

    case 2:
        cout << "BUSQUEDA USUARIO =============================================\n";
        buscarUsuario(head);
        break;

    case 3:
        cout << "ELIMINACION USUARIO =============================================\n";
        eliminarUsuario(head, fileName);
        break;

    case 4:
        cout << "IMPRESION USUARIOS =============================================\n";
        head->printList();
        break;

    default:
        cout << "Chistosito";
        break;
    }

#pragma endregion

    return 0;
}