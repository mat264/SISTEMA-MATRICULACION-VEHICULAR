#include <iostream>
#include <cstring>
using namespace std;

#define MAX_CONTACTS 50

// Estructura de un contacto
typedef struct Contact {
	char name[50];
	char phone[15];
	char email[50];
} Contact;

// Variables globales
Contact contactList[MAX_CONTACTS];
int contactCount = 0;

// Parte 1: Inicializar lista de contactos
void initializeContacts() {
	for (int i = 0; i < MAX_CONTACTS; i++) {
		strcpy(contactList[i].name, "");
		strcpy(contactList[i].phone, "");
		strcpy(contactList[i].email, "");
	}
	contactCount = 0;
}

// Parte 2: Agregar un contacto usando recursividad
void addContactRecursive(Contact newContact, int index) {
	if (index >= MAX_CONTACTS) {
		cout << "Lista de contactos llena." << endl;
		return;
	}
	if (strlen(contactList[index].name) == 0) {
		contactList[index] = newContact;
		contactCount++;
		cout << "Contacto agregado correctamente." << endl;
		return;
	}
	addContactRecursive(newContact, index + 1);
}

// Parte 2: Mostrar contactos usando recursividad
void showContactsRecursive(int index) {
	if (index >= MAX_CONTACTS) return;
	if (strlen(contactList[index].name) != 0) {
		cout << "Nombre: " << contactList[index].name << endl;
		cout << "Teléfono: " << contactList[index].phone << endl;
		cout << "Correo: " << contactList[index].email << endl;
		cout << "---------------------------" << endl;
	}
	showContactsRecursive(index + 1);
}

// Parte 3: Buscar contacto por nombre usando recursividad
int searchContactRecursive(const char* name, int index) {
	if (index >= MAX_CONTACTS) return -1;
	if (strcmp(contactList[index].name, name) == 0) {
		return index;
	}
	return searchContactRecursive(name, index + 1);
}

// Parte 3: Eliminar contacto usando recursividad
void deleteContactRecursive(int index) {
	if (index >= MAX_CONTACTS - 1) {
		strcpy(contactList[index].name, "");
		strcpy(contactList[index].phone, "");
		strcpy(contactList[index].email, "");
		return;
	}
	contactList[index] = contactList[index + 1];
	deleteContactRecursive(index + 1);
}

// Parte 4: Menú interactivo
void menu() {
	int option;
	do {
		cout << "\n--- Menú de Gestión de Contactos ---" << endl;
		cout << "1. Agregar un contacto" << endl;
		cout << "2. Mostrar todos los contactos" << endl;
		cout << "3. Buscar un contacto" << endl;
		cout << "4. Eliminar un contacto" << endl;
		cout << "5. Salir" << endl;
		cout << "Seleccione una opción: ";
		cin >> option;
		cin.ignore();
		
		if (option == 1) {
			if (contactCount >= MAX_CONTACTS) {
				cout << "No se pueden agregar más contactos." << endl;
				continue;
			}
			Contact newContact;
			cout << "Ingrese nombre: ";
			cin.getline(newContact.name, 50);
			cout << "Ingrese teléfono: ";
			cin.getline(newContact.phone, 15);
			cout << "Ingrese correo: ";
			cin.getline(newContact.email, 50);
			
			addContactRecursive(newContact, 0);
		}
		else if (option == 2) {
			cout << "\n--- Lista de Contactos ---" << endl;
			showContactsRecursive(0);
		}
		else if (option == 3) {
			char searchName[50];
			cout << "Ingrese nombre a buscar: ";
			cin.getline(searchName, 50);
			int foundIndex = searchContactRecursive(searchName, 0);
			if (foundIndex != -1) {
				cout << "Contacto encontrado:" << endl;
				cout << "Nombre: " << contactList[foundIndex].name << endl;
				cout << "Teléfono: " << contactList[foundIndex].phone << endl;
				cout << "Correo: " << contactList[foundIndex].email << endl;
			}
			else {
				cout << "Contacto no encontrado." << endl;
			}
		}
		else if (option == 4) {
			char deleteName[50];
			cout << "Ingrese nombre a eliminar: ";
			cin.getline(deleteName, 50);
			int deleteIndex = searchContactRecursive(deleteName, 0);
			if (deleteIndex != -1) {
				deleteContactRecursive(deleteIndex);
				contactCount--;
				cout << "Contacto eliminado." << endl;
			}
			else {
				cout << "Contacto no encontrado." << endl;
			}
		}
		else if (option == 5) {
			cout << "Saliendo del programa..." << endl;
		}
		else {
			cout << "Opción inválida." << endl;
		}
		
	} while (option != 5);
}

int main() {
	initializeContacts();
	menu();
	return 0;
}
