#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Function to read parameters from file
void read_parameters(const string& filename, int& num_process, int& resource_types, int num_resources[], int matrix_allocation[][10], int matrix_requests[][10]) {
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string line;

    // Read number of processes and resource types
    getline(file, line, '.');
    stringstream ss1(line);
    ss1 >> num_process >> resource_types;

    // Read available resources
    getline(file, line, '.');
    stringstream ss2(line);
    for (int i = 0; i < resource_types; i++) {
        ss2 >> num_resources[i];
    }

    // Read allocation matrix
    for (int i = 0; i < num_process; i++) {
        getline(file, line, '.');
        stringstream ss3(line);
        for (int j = 0; j < resource_types; j++) {
            ss3 >> matrix_allocation[i][j];
        }
    }

    // Read request matrix
    for (int i = 0; i < num_process; i++) {
        getline(file, line, '.');
        stringstream ss4(line);
        for (int j = 0; j < resource_types; j++) {
            ss4 >> matrix_requests[i][j];
        }
    }

    file.close();
}

// Function to determine if a deadlock exists
void determine_deadlock(int num_process, int resource_types, int num_resources[], int matrix_allocation[][10], int matrix_requests[][10]) {
    bool finished[10] = { false }; // Tracks completed processes
    int finished_count = 0;

    // Calculate available resources
    for (int i = 0; i < resource_types; i++) {
        for (int j = 0; j < num_process; j++) {
            num_resources[i] -= matrix_allocation[j][i];
        }
    }

    while (finished_count < num_process) {
        bool any_process_completed = false;

        for (int i = 0; i < num_process; i++) {
            if (!finished[i]) {
                bool have_enough_resources = true;

                // Check if the process can be satisfied
                for (int j = 0; j < resource_types; j++) {
                    if (matrix_requests[i][j] > num_resources[j]) {
                        have_enough_resources = false;
                        break;
                    }
                }

                // If resources are sufficient, mark process as finished
                if (have_enough_resources) {
                    for (int j = 0; j < resource_types; j++) {
                        num_resources[j] += matrix_allocation[i][j];
                    }
                    finished[i] = true;
                    finished_count++;
                    any_process_completed = true;
                }
            }
        }

        // If no process completed, deadlock detected
        if (!any_process_completed) {
            cout << "Deadlock detected!" << endl;
            return;
        }
    }

    cout << "No Deadlock detected!" << endl;
}

int main() {
    int num_process, resource_types;
    int num_resources[10], matrix_allocation[10][10], matrix_requests[10][10];

    string filename = "Deadlock.txt";
    read_parameters(filename, num_process, resource_types, num_resources, matrix_allocation, matrix_requests);

    determine_deadlock(num_process, resource_types, num_resources, matrix_allocation, matrix_requests);

    return 0;
}
