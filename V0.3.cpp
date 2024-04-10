#include <iostream>
#include <string>
#include <curl/curl.h>

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

// Callback function to write data into the email
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int main() {
    ResidentDatabase database;

    char choice;
    string name, email, address, blockName;
    string emailRecipient, emailBody, emailContent;

    // Initialize libcurl
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the SMTP server details (replace with your actual SMTP server)
        string smtp_server = "smtp.gmail.com";
        string smtp_username = "rs1063144@gmail.com";
        string smtp_password = "umkz cvte mbej vkzp";
        struct curl_slist* recipients = NULL;

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

                    // Send a dummy email to test the email feature
                    emailRecipient = email; // Send the email to the new resident
                    emailBody = "This is a test email from the Crime Alert Program.\n";
                    emailBody += "Thank you for using the service.";

                    emailContent = "To: rachitkhurana40@gmail.com\r\n";
                    emailContent += "From: rs10631442gmail.com\r\n";
                    emailContent += "Subject: Test Email\r\n\r\n";
                    emailContent += emailBody;

                    // Set libcurl options for sending the email
                    curl_easy_setopt(curl, CURLOPT_URL, smtp_server.c_str());
                    curl_easy_setopt(curl, CURLOPT_USERNAME, smtp_username.c_str());
                    curl_easy_setopt(curl, CURLOPT_PASSWORD, smtp_password.c_str());
                    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "rs1063144@gmail.com");
                    recipients = curl_slist_append(recipients, emailRecipient.c_str());
                    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
                    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
                    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
                    curl_easy_setopt(curl, CURLOPT_READDATA, emailContent.c_str());
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &emailContent);

                    // Send the email
                    res = curl_easy_perform(curl);

                    if (res != CURLE_OK) {
                        cerr << "Error sending email: " << curl_easy_strerror(res) << endl;
                    } else {
                        cout << "Test email sent successfully to: " << emailRecipient << endl;
                    }

                    // Clean up libcurl
                    curl_slist_free_all(recipients);
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

        // Clean up libcurl
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    Resident* current = database.head;
    while (current) {
        Resident* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}