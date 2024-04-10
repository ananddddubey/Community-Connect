#include <iostream>
#include <string>

using namespace std;

// Emergency structure to store emergency information
struct Emergency {
    string reporter;  // Resident who reported the emergency (house no.)
    string location;  // Block name
    string type;      // Type of emergency
    string dateTime;  // Date and time of the emergency (to be implemented)

    Emergency* next;  // Pointer to the next emergency report in the linked list

    // Constructor to initialize the emergency
    Emergency(const string& reporter, const string& location,
              const string& type, const string& dateTime = "NULL")
        : reporter(reporter), location(location), type(type), dateTime(dateTime), next(nullptr) {}
};

// EmergencyDatabase class to manage the linked list of emergencies
class EmergencyDatabase {
private:
    Emergency* head; // Head of the linked list

public:
    // Constructor
    EmergencyDatabase() : head(nullptr) {}

    // Destructor to free allocated memory
    ~EmergencyDatabase() {
        clearDatabase();
    }

    // Function to add an emergency report to the database
    void addEmergency(const string& reporter, const string& location,
                      const string& type, const string& dateTime = "NULL") {
        Emergency* newEmergency = new Emergency(reporter, location, type, dateTime);
        newEmergency->next = head;
        head = newEmergency;
    }

    // Function to retrieve an emergency report based on reporter's house number
    Emergency* getEmergency(const string& reporter) {
        Emergency* current = head;
        while (current != nullptr) {
            if (current->reporter == reporter) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Emergency report not found
    }

    // Function to display all emergency reports in the database
    void displayAllEmergencies() {
        Emergency* current = head;
        while (current != nullptr) {
            // Display emergency details
            cout << "Reporter: " << current->reporter << "; ";
            cout << "Location: " << current->location << "; ";
            cout << "Type: " << current->type << "; ";
            cout << "Date and Time: " << current->dateTime << "\n";

            cout << "---------------------\n";

            current = current->next;
        }
    }

    // Function to delete an emergency report based on reporter's house number
    void deleteEmergency(const string& reporter) {
        Emergency* current = head;
        Emergency* previous = nullptr;

        while (current != nullptr) {
            if (current->reporter == reporter) {
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

        cout << "Emergency report not found.\n";
    }

    // Function to clear the entire database
    void clearDatabase() {
        while (head != nullptr) {
            Emergency* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Example usage
/*int main() {
    EmergencyDatabase emergencyDB;

    // Example: Adding an emergency report
    emergencyDB.addEmergency("A101", "BlockA", "Fire");

    // Example: Retrieving an emergency report
    Emergency* retrievedEmergency = emergencyDB.getEmergency("A101");
    if (retrievedEmergency != nullptr) {
        // Display emergency details or perform other operations
    } else {
        cout << "Emergency report not found.\n";
    }

    // Example: Deleting an emergency report
    emergencyDB.deleteEmergency("A101");

    return 0;
}*/