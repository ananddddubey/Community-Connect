#include <iostream>
#include <string>

using namespace std;

// Admin structure to store admin information
struct Admin {
    string adminNo;   // Admin number
    string password;  // Admin password
    string name;
    string phoneNumber;
    string email;

    Admin* next;  // Pointer to the next admin in the linked list

    // Constructor to initialize the admin
    Admin(const string& adminNo, const string& password, const string& name,
          const string& phoneNumber, const string& email)
        : adminNo(adminNo), password(password), name(name),
          phoneNumber(phoneNumber), email(email), next(nullptr) {}
};

// AdminDatabase class to manage the linked list of admins
class AdminDatabase {
private:
    Admin* head; // Head of the linked list

public:
    // Constructor
    AdminDatabase() : head(nullptr) {
        // Adding an example entry for admin
        addAdmin("admin0", "pass1234", "First", "0123456789", "admin123@gmail.com");
    }

    // Destructor to free allocated memory
    ~AdminDatabase() {
        clearDatabase();
    }

    // Function to add an admin to the database
    void addAdmin(const string& adminNo, const string& password, const string& name,
                  const string& phoneNumber, const string& email) {
        Admin* newAdmin = new Admin(adminNo, password, name, phoneNumber, email);
        newAdmin->next = head;
        head = newAdmin;
    }

    // Function to retrieve an admin based on admin number
    Admin* getAdmin(const string& adminNo) {
        Admin* current = head;
        while (current != nullptr) {
            if (current->adminNo == adminNo) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Admin not found
    }

    // Function to update admin information based on admin number
    void updateAdmin(const string& adminNo, const string& name,
                     const string& phoneNumber, const string& email) {
        Admin* adminToUpdate = getAdmin(adminNo);
        if (adminToUpdate != nullptr) {
            adminToUpdate->name = name;
            adminToUpdate->phoneNumber = phoneNumber;
            adminToUpdate->email = email;
        } else {
            cout << "Admin not found.\n";
        }
    }

    // Function to display all admins in the database
    void displayAllAdmins() {
        Admin* current = head;
        while (current != nullptr) {
            // Display admin details
            cout << "Admin No.: " << current->adminNo << "; ";
            cout << "Name: " << current->name << "; ";
            cout << "Phone Number: " << current->phoneNumber << "; ";
            cout << "Email: " << current->email << "\n";

            cout << "---------------------\n";

            current = current->next;
        }
    }

    // Function to delete an admin based on admin number
    void deleteAdmin(const string& adminNo) {
        Admin* current = head;
        Admin* previous = nullptr;

        while (current != nullptr) {
            if (current->adminNo == adminNo) {
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

        cout << "Admin not found.\n";
    }

    // Function to clear the entire database
    void clearDatabase() {
        while (head != nullptr) {
            Admin* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Example usage
/*int main() {
    AdminDatabase adminDB;

    // Example: Retrieving an admin
    Admin* retrievedAdmin = adminDB.getAdmin("admin0");
    if (retrievedAdmin != nullptr) {
        // Display admin details or perform other operations
    } else {
        cout << "Admin not found.\n";
    }

    // Example: Updating admin information
    adminDB.updateAdmin("admin0", "UpdatedName", "9876543210", "updatedemail@example.com");

    // Example: Deleting an admin
    adminDB.deleteAdmin("admin0");

    return 0;
}*/