#include <iostream>
#include <vector>
#include <string>

// Data structure to represent resident information
struct Resident {
    std::string name;
    std::string contact;
    std::string location;
};

// Resident database
std::vector<Resident> residentDatabase;

// Function to report an emergency
void reportEmergency() {
    // Gather emergency information (location, description, type)
    std::string location, description, type;
    
    // Populate the emergency report
    // You can use user input or other methods to collect this data
    // For simplicity, we assume direct assignment here.
    location = "123 Main St";
    description = "Suspicious activity";
    type = "Security";

    // Send the emergency report to the admin system
    // You can implement this part using email functionality.
    // For simplicity, we'll print the report.
    std::cout << "Emergency Report: " << location << ", " << description << ", " << type << std::endl;

    // The admin system will handle the verification and alerting process.
}

// Function to verify the emergency report
bool verifyEmergency() {
    // Implement your verification logic here, e.g., using probabilities and responses.
    // For simplicity, we assume the report is always verified.
    return true;
}

// Function to alert residents
void alertResidents() {
    // Notify all residents about the emergency
    for (const Resident& resident : residentDatabase) {
        // Implement email functionality to send alerts to residents.
        // For simplicity, we'll print the alert.
        std::cout << "Alert sent to " << resident.name << " at " << resident.contact << std::endl;
    }
}

int main() {
    // Populate the resident database (for testing purposes)
    Resident resident1 = {"John Doe", "john@example.com", "123 Main St"};
    Resident resident2 = {"Jane Smith", "jane@example.com", "456 Elm St"};
    // Add more residents as needed.

    residentDatabase.push_back(resident1);
    residentDatabase.push_back(resident2);

    // Main program loop
    char choice;
    do {
        std::cout << "1. Report an emergency\n2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                reportEmergency();
                if (verifyEmergency()) {
                    alertResidents();
                }
                break;
            case '2':
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != '2');

    return 0;
}