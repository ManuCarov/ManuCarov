#include <iostream>
#include <string>
using namespace std;

class Node
{
private:
    string dato1;
    string dato2;
    Node *sgte;

public:
    Node(string, string);
    Node();
    ~Node();
    Node *getNext();
    void insertInList(Node *);
    Node deleteInList(string, string);
    bool searchInList(string, string);
    void printList();
};

Node::Node(string _dato1, string _dato2)
{
    this->dato1 = _dato1;
    this->dato2 = _dato2;
}
Node::Node()
{
}
Node::~Node()
{
}

Node *Node::getNext()
{
    return this->sgte;
}

void Node::printList()
{
    Node *temp = this;
    while (temp != NULL)
    {
        cout << temp->dato1 << endl;
        temp = temp->sgte;
    }
}

void Node::insertInList(Node* nodeToInsert)
{
    Node *last = this;
    nodeToInsert->sgte = NULL; 
   
    if (this == NULL) 
    {
        *this = *nodeToInsert;
        return; 
    } 
   
    while (last->sgte != NULL)
    {
        last = last->sgte; 
    }
   
    last->sgte = nodeToInsert; 
    return;
}

Node Node::deleteInList(string user, string pass)
{
    Node *head_ref = this;
    Node *temp = head_ref;
    Node *prev = NULL;

    // Si la cabeza sostiene los datos a eliminar
    if (temp != NULL && temp->dato1 == user && temp->dato2 == pass)
    {
        head_ref = temp->sgte; // Cambiar cabeza
        delete temp;        // Eliminar cabeza vieja
        return *head_ref;
    }

    // Si no, buscar la key a ser deleteada
    else
    {
        while (temp != NULL && temp->dato1 != user && temp->dato2 != pass)
        {
            prev = temp;
            temp = temp->sgte;
        }

        // Si lo que buscamos no estaba en la lista
        if (temp == NULL)
        {
            cout << endl
                 << "No se encontraron los datos suministrados" << endl;
            return *head_ref;
        }

        // Separar el nodo de la lista enlazada
        prev->sgte = temp->sgte;
        delete temp;
        return *head_ref;
    }
}

bool Node::searchInList(string userToSearch, string passwordToSearch)
{
    Node *temp = this;

    while (temp != NULL)
    {
        if (temp->dato1 == userToSearch && temp->dato2 == passwordToSearch)
        {
            return true;
        }
        temp = temp->sgte;
    }
    return false;
}