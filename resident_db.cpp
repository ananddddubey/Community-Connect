#include <iostream>
#include <string>

using namespace std;

// Resident structure to store resident information
struct Resident {
    string houseNo;  // Format: 'BLOCK_NAME HOUSE_NUMBER'
    string password; // Common password for family members
    string blockName;
    int numOfPeople;
    string* names;
    string* phoneNumbers;
    string* emailAddresses;
    string* gender;
    int* age;

    Resident* next; // Pointer to the next resident in the linked list

    // Constructor to initialize the resident
    Resident(const string& houseNo, const string& password, const string& blockName,
             int numOfPeople, const string* names, const string* phoneNumbers,
             const string* emailAddresses, const string* gender, const int* age)
        : houseNo(houseNo), password(password), blockName(blockName),
          numOfPeople(numOfPeople), names(new string[numOfPeople]),
          phoneNumbers(new string[numOfPeople]), emailAddresses(new string[numOfPeople]),
          gender(new string[numOfPeople]), age(new int[numOfPeople]), next(nullptr) {
        
        // Copy family member details
        for (int i = 0; i < numOfPeople; ++i) {
            this->names[i] = names[i];
            this->phoneNumbers[i] = phoneNumbers[i];
            this->emailAddresses[i] = emailAddresses[i];
            this->gender[i] = gender[i];
            this->age[i] = age[i];
        }
    }

    // Destructor to free allocated memory
    ~Resident() {
        delete[] names;
        delete[] phoneNumbers;
        delete[] emailAddresses;
        delete[] gender;
        delete[] age;
    }
};

// ResidentDatabase class to manage the linked list of residents
class ResidentDatabase {
private:
    Resident* head; // Head of the linked list

public:
    // Constructor
    ResidentDatabase() : head(nullptr) {}

    // Destructor to free allocated memory
    ~ResidentDatabase() {
        clearDatabase();
    }

    // Function to add a resident to the database
    void addResident(const string& houseNo, const string& password, const string& blockName,
                     int numOfPeople, const string* names, const string* phoneNumbers,
                     const string* emailAddresses, const string* gender, const int* age) {
        Resident* newResident = new Resident(houseNo, password, blockName, numOfPeople,
                                             names, phoneNumbers, emailAddresses, gender, age);
        newResident->next = head;
        head = newResident;
    }

    // Function to retrieve a resident based on house number
    Resident* getResident(const string& houseNo) {
        Resident* current = head;
        while (current != nullptr) {
            if (current->houseNo == houseNo) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Resident not found
    }

    // Function to update resident information based on house number
    void updateResident(const string& houseNo, int numOfPeople, const string* names,
                        const string* phoneNumbers, const string* emailAddresses,
                        const string* gender, const int* age) {
        Resident* residentToUpdate = getResident(houseNo);
        if (residentToUpdate != nullptr) {
            residentToUpdate->numOfPeople = numOfPeople;

            // Free existing memory
            delete[] residentToUpdate->names;
            delete[] residentToUpdate->phoneNumbers;
            delete[] residentToUpdate->emailAddresses;
            delete[] residentToUpdate->gender;
            delete[] residentToUpdate->age;

            // Allocate new memory and update details
            residentToUpdate->names = new string[numOfPeople];
            residentToUpdate->phoneNumbers = new string[numOfPeople];
            residentToUpdate->emailAddresses = new string[numOfPeople];
            residentToUpdate->gender = new string[numOfPeople];
            residentToUpdate->age = new int[numOfPeople];

            for (int i = 0; i < numOfPeople; ++i) {
                residentToUpdate->names[i] = names[i];
                residentToUpdate->phoneNumbers[i] = phoneNumbers[i];
                residentToUpdate->emailAddresses[i] = emailAddresses[i];
                residentToUpdate->gender[i] = gender[i];
                residentToUpdate->age[i] = age[i];
            }
        } else {
            cout << "Resident not found.\n";
        }
    }

    // Function to display all residents in the database
    void displayAllResidents() {
        Resident* current = head;
        while (current != nullptr) {
            // Display resident details
            cout << "House No.: " << current->houseNo << "; ";
            cout << "Block Name: " << current->blockName << "; ";
            cout << "Number of People: " << current->numOfPeople << "; ";
            cout << "Details of Family Members: ";
            for (int i = 0; i < current->numOfPeople; ++i) {
                cout << current->names[i] << ", ";
                cout << current->phoneNumbers[i] << ", ";
                cout << current->emailAddresses[i] << ", ";
                cout << current->gender[i] << ", ";
                cout << current->age[i] << "\n";
            }
            cout << "---------------------\n";

            current = current->next;
        }
    }

    // Function to display information of a specific resident based on house number
    void displayResident(const string& houseNo) {
        Resident* resident = getResident(houseNo);
        if (resident != nullptr) {
            // Display resident details
            cout << "House No.: " << resident->houseNo << "\n";
            cout << "Block Name: " << resident->blockName << "\n";
            cout << "Number of People: " << resident->numOfPeople << "\n";
            cout << "Details of Family Members: ";
            for (int i = 0; i < resident->numOfPeople; ++i) {
                cout << resident->names[i] << ", ";
                cout << resident->phoneNumbers[i] << ", ";
                cout << resident->emailAddresses[i] << ", ";
                cout << resident->gender[i] << ", ";
                cout << resident->age[i] << "\n";
            }
        } else {
            cout << "Resident not found.\n";
        }
    }

    // Function to delete a resident based on house number
    void deleteResident(const string& houseNo) {
        Resident* current = head;
        Resident* previous = nullptr;

        while (current != nullptr) {
            if (current->houseNo == houseNo) {
                if (previous == nullptr) {
                    // Deleting the head
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }

        cout << "Resident not found.\n";
    }

    // Function to clear the entire database
    void clearDatabase() {
        while (head != nullptr) {
            Resident* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Example usage
/*int main() {
    ResidentDatabase residentDB;

    // Example: Adding a resident
    string names[] = {"John", "Jane"};
    string phoneNumbers[] = {"1234567890", "9876543210"};
    string emailAddresses[] = {"john@example.com", "jane@example.com"};
    string gender[] = {"Male", "Female"};
    int age[] = {30, 28};

    residentDB.addResident("A101", "password123", "BlockA", 2, names, phoneNumbers, emailAddresses, gender, age);

    // Example: Retrieving a resident
    Resident* retrievedResident = residentDB.getResident("A101");
    if (retrievedResident != nullptr) {
        // Display resident details or perform other operations
    } else {
        cout << "Resident not found.\n";
    }

    // Example: Updating resident information
    residentDB.updateResident("A101", 3, names, phoneNumbers, emailAddresses, gender, age);

    // Example: Deleting a resident
    residentDB.deleteResident("A101");

    return 0;
}*/