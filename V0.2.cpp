#include <iostream>
#include <string>

using namespace std;

struct Resident {
    string name;
    string email;
    string address;
    string blockName;
    Resident* next;

    Resident(const string& _name, const string& _email, const string& _address, const string& _blockName)
        : name(_name), email(_email), address(_address), blockName(_blockName), next(nullptr) {}
};

class ResidentDatabase {
public:
    Resident* head;

    ResidentDatabase() : head(nullptr) {}

    void addResident(const string& name, const string& email, const string& address, const string& blockName) {
        Resident* newResident = new Resident(name, email, address, blockName);
        if (!head) {
            head = newResident;
        } else {
            Resident* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newResident;
        }
    }

    void displayResidents() {
        Resident* current = head;
        cout << "Resident Database:\n";
        while (current) {
            cout << "Name: " << current->name << "\nEmail: " << current->email << "\nAddress: " << current->address << "\nBlock Name: " << current->blockName << "\n\n";
            current = current->next;
        }
    }
};

int main() {
    ResidentDatabase database;

    char choice;
    string name, email, address, blockName; // Declare the variables outside the switch

    do {
        cout << "1. Report an emergency\n2. Add a new resident\n3. Display Resident Database\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Emergency reporting feature is not implemented in this example.\n";
                break;
            case '2':
                cin.ignore();
                cout << "Enter resident's name: ";
                getline(cin, name);
                cout << "Enter resident's email: ";
                getline(cin, email);
                cout << "Enter resident's address: ";
                getline(cin, address);
                cout << "Enter resident's block name: ";
                getline(cin, blockName);
                database.addResident(name, email, address, blockName);
                cout << "New resident added to the database.\n";
                break;
            case '3':
                database.displayResidents();
                break;
            case '4':
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != '4');

    Resident* current = database.head;
    while (current) {
        Resident* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}