#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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

// Resident database class
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

// Binary search tree node
struct BSTNode {
    string name;
    string email;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const string& _name, const string& _email)
        : name(_name), email(_email), left(nullptr), right(nullptr) {}
};

// Binary search tree class for searching residents by name
class ResidentBST {
public:
    BSTNode* root;

    ResidentBST() : root(nullptr) {}

    // Add a resident to the BST
    void insert(const string& name, const string& email) {
        root = insertRecursive(root, name, email);
    }

    // Recursive method to insert a resident into the BST
    BSTNode* insertRecursive(BSTNode* node, const string& name, const string& email) {
        if (node == nullptr) {
            return new BSTNode(name, email);
        }

        if (name < node->name) {
            node->left = insertRecursive(node->left, name, email);
        } else if (name > node->name) {
            node->right = insertRecursive(node->right, name, email);
        }

        return node;
    }

    // Search for a resident by name in the BST
    BSTNode* search(const string& name) {
        return searchRecursive(root, name);
    }

    // Recursive method to search for a resident in the BST
    BSTNode* searchRecursive(BSTNode* node, const string& name) {
        if (node == nullptr || node->name == name) {
            return node;
        }

        if (name < node->name) {
            return searchRecursive(node->left, name);
        }

        return searchRecursive(node->right, name);
    }

    // Delete a resident from the BST
    BSTNode* deleteResident(BSTNode* node, const string& name) {
        if (node == nullptr) {
            return node;
        }

        if (name < node->name) {
            node->left = deleteResident(node->left, name);
        } else if (name > node->name) {
            node->right = deleteResident(node->right, name);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: get the in-order successor (smallest in the right subtree)
            BSTNode* temp = minValueNode(node->right);

            // Copy the in-order successor's content to this node
            node->name = temp->name;
            node->email = temp->email;

            // Delete the in-order successor
            node->right = deleteResident(node->right, temp->name);
        }
        return node;
    }

    // Helper function to find the node with the smallest value
    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
};

int main() {
    ResidentDatabase database;
    ResidentBST bst;

    // Populate the database with 40 dummy data
    for (char block = 'A'; block <= 'J'; ++block) {
        for (int i = 1; i <= 4; ++i) {
            string name = "Resident " + to_string(i) + " from Block " + block;
            string email = "resident" + to_string(i) + "@block" + block + ".com";
            string address = "Block " + string(1, block) + ", Street " + to_string(i);
            database.addResident(name, email, address, "Block " + string(1, block));

            // Add residents to the binary search tree for easy lookup
            bst.insert(name, email);
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

                // Ask the user to enter the block number
                cin.ignore();
                string blockToSearch;
                cout << "Enter the block name to send the soft survey: ";
                getline(cin, blockToSearch);

                // Create a vector to store residents in the specified block
                vector<Resident> residentsToSurvey;

                // Search for residents in the specified block and add them to the vector
                Resident* current = database.head;
                while (current) {
                    if (current->blockName == blockToSearch) {
                        residentsToSurvey.push_back(*current);
                    }
                    current = current->next;
                }

                // Send the soft survey email to all residents in the vector
                if (!residentsToSurvey.empty()) {
                    cout << "Sending a soft survey email to residents in Block " << blockToSearch
                         << " for the emergency type: " << emergencyTypes[emergencyChoice - 1] << endl;
                } else {
                    cout << "No residents found in Block " << blockToSearch << endl;
                }

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
                // Add the new resident to the binary search tree
                bst.insert(name, email);
                cout << "New resident added to the database.\n";
                break;
            }
            case '3':
                // Sort residents by name and display
                database.displayResidents();
                break;
            case '4': {
                cin.ignore();
                string name;
                cout << "Enter the name of the resident to delete: ";
                getline(cin, name);

                // Delete the resident from the binary search tree
                bst.root = bst.deleteResident(bst.root, name);

                cout << "Resident '" << name << "' has been deleted from the database." << endl;
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

    // Clean up memory for the binary search tree
    // You can add memory deallocation for the BST here, if needed.

    return 0;
}