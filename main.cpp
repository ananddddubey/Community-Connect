#include <iostream>
#include <string>

#include "resident_db.cpp"
#include "admin_db.cpp"
#include "emergency_db.cpp"

using namespace std;

// Resident and Admin database instances
ResidentDatabase residentDB;
AdminDatabase adminDB;
EmergencyDatabase emergencyDB;

// Function prototypes
void residentSignIn();
void residentSignUp();
void adminSignIn();
void adminSignUp();
void residentMenu(const string& residentID);
void adminMenu();

int main() {
    int choice;
    while (true) {
        cout << "Welcome to the Residential Society Emergency Alert System\n";
        cout << "1. Resident Sign In\n";
        cout << "2. Resident Sign Up\n";
        cout << "3. Admin Sign In\n";
        cout << "4. Admin Sign Up\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                residentSignIn();
                break;
            case 2:
                residentSignUp();
                break;
            case 3:
                adminSignIn();
                break;
            case 4:
                adminSignUp();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

void residentSignIn() {
    string houseNo, password;
    cout << "Enter your house number: ";
    cin >> houseNo;
    cout << "Enter your password: ";
    cin >> password;

    Resident* resident = residentDB.getResident(houseNo);

    if (resident != nullptr && resident->password == password) {
        cout << "Resident Sign In successful!\n";
        residentMenu(houseNo);
    } else {
        cout << "Invalid credentials. Sign In failed.\n";
    }
}

void residentSignUp() {
    string houseNo, password, blockName;
    int numOfPeople;

    cout << "Enter your house number (BLOCK_NAME HOUSE_NUMBER): ";
    cin >> houseNo;

    // Check if resident already exists
    if (residentDB.getResident(houseNo) != nullptr) {
        cout << "Resident with this house number already exists. Sign Up failed.\n";
        return;
    }

    cout << "Enter your password: ";
    cin >> password;
    cout << "Enter your block name: ";
    cin >> blockName;
    cout << "Enter the number of people in your house: ";
    cin >> numOfPeople;

    string* names = new string[numOfPeople];
    string* phoneNumbers = new string[numOfPeople];
    string* emailAddresses = new string[numOfPeople];
    string* gender = new string[numOfPeople];
    int* age = new int[numOfPeople];

    cout << "Enter details for each family member:\n";
    for (int i = 0; i < numOfPeople; ++i) {
        cout << "Details for family member " << i + 1 << ":\n";
        cout << "Name: ";
        cin >> names[i];
        cout << "Phone Number: ";
        cin >> phoneNumbers[i];
        cout << "Email Address: ";
        cin >> emailAddresses[i];
        cout << "Gender: ";
        cin >> gender[i];
        cout << "Age: ";
        cin >> age[i];
    }

    residentDB.addResident(houseNo, password, blockName, numOfPeople, names, phoneNumbers, emailAddresses, gender, age);

    cout << "Resident Sign Up successful!\n";
    residentMenu(houseNo);

    // Clean up allocated memory
    delete[] names;
    delete[] phoneNumbers;
    delete[] emailAddresses;
    delete[] gender;
    delete[] age;
}

void adminSignIn() {
    string adminNo, password;
    cout << "Enter your admin number: ";
    cin >> adminNo;
    cout << "Enter your password: ";
    cin >> password;

    Admin* admin = adminDB.getAdmin(adminNo);

    if (admin != nullptr && admin->password == password) {
        cout << "Admin Sign In successful!\n";
        adminMenu();
    } else {
        cout << "Invalid credentials. Sign In failed.\n";
    }
}

void adminSignUp() {
    string adminNo, password, name, phoneNumber, email;

    cout << "Enter admin number: ";
    cin >> adminNo;

    // Check if admin already exists
    if (adminDB.getAdmin(adminNo) != nullptr) {
        cout << "Admin with this number already exists. Sign Up failed.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    cout << "Enter email: ";
    cin >> email;

    adminDB.addAdmin(adminNo, password, name, phoneNumber, email);
    cout << "Admin Sign Up successful!\n";
}

void residentMenu(const string& residentID) {
    int choice;
    while (true) {
        cout << "Resident Menu\n";
        cout << "1. Report an Emergency\n";
        cout << "2. Update Information\n";
        cout << "3. View Family\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Implement emergency reporting
                break;
            case 2:
                /*string houseNo = residentID; // Fixed as the user's houseNo
                int numOfPeople;
                cout << "Enter the number of people in your house: ";
                cin >> numOfPeople;

                string* names = new string[numOfPeople];
                string* phoneNumbers = new string[numOfPeople];
                string* emailAddresses = new string[numOfPeople];
                string* gender = new string[numOfPeople];
                int* age = new int[numOfPeople];

                cout << "Enter details for each family member:\n";
                for (int i = 0; i < numOfPeople; ++i) {
                    cout << "Details for family member " << i + 1 << ":\n";
                    cout << "Name: ";
                    cin >> names[i];
                    cout << "Phone Number: ";
                    cin >> phoneNumbers[i];
                    cout << "Email Address: ";
                    cin >> emailAddresses[i];
                    cout << "Gender: ";
                    cin >> gender[i];
                    cout << "Age: ";
                    cin >> age[i];
                }
                residentDB.updateResident(houseNo, numOfPeople, names, phoneNumbers, emailAddresses, gender, age);
                cout << "Resident information updated!\n";*/
                break;
            case 3:
                residentDB.displayResident(residentID);
                break;
            case 4:
                cout << "Exiting Resident Menu.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void adminMenu() {
    int choice;
    while (true) {
        cout << "Admin Menu\n";
        cout << "1. View Residents\n";
        cout << "2. View Emergency History\n";
        cout << "3. Update Resident Data\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        string houseNo;

        switch (choice) {
            case 1:
                cout << "All Residents in the Database:\n";
                residentDB.displayAllResidents(); // Display all residents
                break;
            case 2:
                cout << "All Emergencies in the Database:\n";
                emergencyDB.displayAllEmergencies(); // Display all emergencies
                break;
            case 3:
                int numOfPeople;
                cout << "Enter the number of people in your house: ";
                cin >> numOfPeople;

                string* names = new string[numOfPeople];
                string* phoneNumbers = new string[numOfPeople];
                string* emailAddresses = new string[numOfPeople];
                string* gender = new string[numOfPeople];
                int* age = new int[numOfPeople];

                cout << "Enter details for each family member:\n";
                for (int i = 0; i < numOfPeople; ++i) {
                    cout << "Details for family member " << i + 1 << ":\n";
                    cout << "Name: ";
                    cin >> names[i];
                    cout << "Phone Number: ";
                    cin >> phoneNumbers[i];
                    cout << "Email Address: ";
                    cin >> emailAddresses[i];
                    cout << "Gender: ";
                    cin >> gender[i];
                    cout << "Age: ";
                    cin >> age[i];
                }
                residentDB.updateResident(houseNo, numOfPeople, names, phoneNumbers, emailAddresses, gender, age);
                cout << "Resident information updated!\n";
                break;
            case 4:
                cout << "Exiting Admin Menu.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}