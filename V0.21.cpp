#include <iostream>
#include <string>

using namespace std;

// Resident structure to store information
struct Resident {
    string name;
    string email;
    string address;
    string blockName;
    Resident* next;

    Resident(const string& _name, const string& _email, const string& _address, const string& _blockName)
        : name(_name), email(_email), address(_address), blockName(_blockName), next(nullptr) {}
};

// ResidentDatabase class to manage the linked list of residents
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

    // Display all residents in the database
    void displayResidents() {
        Resident* current = head;
        cout << "Resident Database:\n";
        while (current) {
            cout << "Name: " << current->name << "\nEmail: " << current->email << "\nAddress: " << current->address << "\nBlock Name: " << current->blockName << "\n\n";
            current = current->next;
        }
    }

    // Bubble sort algorithm to sort residents by name
    void sortResidentsByName() {
        bool swapped;
        Resident* current;
        Resident* lastPtr = nullptr;

        if (head == nullptr) {
            return;
        }

        do {
            swapped = false;
            current = head;

            while (current->next != lastPtr) {
                if (current->name > current->next->name) {
                    swap(current->name, current->next->name);
                    swap(current->email, current->next->email);
                    swap(current->address, current->next->address);
                    swap(current->blockName, current->next->blockName);
                    swapped = true;
                }
                current = current->next;
            }
            lastPtr = current;
        } while (swapped);
    }

    // Delete a resident by name
    void deleteResident(const string& name) {
        Resident* current = head;
        Resident* previous = nullptr;

        while (current != nullptr && current->name != name) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Resident not found in the database." << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        cout << "Resident '" << name << "' has been deleted from the database." << endl;
    }
};

int main() {
    ResidentDatabase database;

    // Populate the database with 40 dummy data
    for (char block = 'A'; block <= 'J'; ++block) {
        for (int i = 1; i <= 4; ++i) {
            string name = "Resident " + to_string(i) + " from Block " + block;
            string email = "resident" + to_string(i) + "@block" + block + ".com";
            string address = "Block " + string(1, block) + ", Street " + to_string(i);
            database.addResident(name, email, address, "Block " + string(1, block));
        }
    }

    char choice;
    do {
        cout << "1. Report an emergency\n2. Add a new resident\n3. Display Resident Database\n4. Delete a resident\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                string emergencyTypes[] = {"Accident", "Fire", "Theft", "Dispute", "Earthquake"};
                cout << "Choose the type of emergency:\n";
                for (int i = 0; i < 5; i++) {
                    cout << i + 1 << ". " << emergencyTypes[i] << "\n";
                }
                int emergencyChoice;
                cout << "Enter your choice (1-5): ";
                cin >> emergencyChoice;

                // Implement emergency reporting, verification, and soft survey here.

                // For this example, we'll just display the chosen emergency type.
                cout << "Emergency type: " << emergencyTypes[emergencyChoice - 1] << endl;
                break;
            }
            case '2': {
                cin.ignore();
                string name, email, address, blockName;
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
            }
            case '3':
                database.sortResidentsByName(); // Sort residents by name
                database.displayResidents();
                break;
            case '4': {
                cin.ignore();
                string name;
                cout << "Enter the name of the resident to delete: ";
                getline(cin, name);
                database.deleteResident(name);
                break;
            }
            case '5':
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != '5');

    // Clean up memory (deallocation)
    Resident* current = database.head;
    while (current) {
        Resident* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}