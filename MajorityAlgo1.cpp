#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const string csvData = "response\nyes\nno\nyes\nyes\nno\nyes\n";

// Function to calculate the probability of "yes" responses
double calculateProbability(const vector<string>& responses) {
    int totalResponses = responses.size();
    int yesCount = 0;

    for (const string& response : responses) {
        if (response == "yes") {
            yesCount++;
        }
    }

    // Calculate the probability of "yes" responses
    return static_cast<double>(yesCount) / totalResponses;
}

// Function to determine if emergency message should be sent
bool shouldSendEmergencyMessage(double probabilityThreshold, const vector<string>& responses) {
    double probability = calculateProbability(responses);
    return probability >= probabilityThreshold;
}

int main() {
    // Set the threshold for sending the emergency message
    double probabilityThreshold = 0.5;

    istringstream csvStream(csvData);
    vector<string> responses;

    // Read responses from CSV data
    string line;
    getline(csvStream, line); // Skip the header line
    while (getline(csvStream, line)) {
        responses.push_back(line);
    }

    // Calculate the probability of "yes" responses
    double probability = calculateProbability(responses);

    // Determine if emergency message should be sent
    bool sendEmergencyMessage = shouldSendEmergencyMessage(probabilityThreshold, responses);

    // Print the probability and decision
    cout << "Probability of 'yes' responses: " << probability << endl;
    if (sendEmergencyMessage) {
        cout << "Sending emergency message!" << endl;
    } else {
        cout << "No need to send emergency message." << endl;
    }

    return 0;
}