#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void list_files(const string& directory) {
    try {
        // Attempt to iterate through the directory
        for (const fs::directory_entry& entry : fs::directory_iterator(directory)) {
            // Print the filename of each entry in the directory
            cout << entry.path().filename().string() << endl;
        }
    }
    catch (const fs::filesystem_error& exception_error) // exception error to catch errors such as (permission errors, file not found, etc)
    {
        cerr << "Error: " << exception_error.what() << endl;
    }
}

int main(int files_count, char* files[]) // We use char* array instead of strings because command - line arguments are passed as C - style strings(char arrays), ensuring compatibility across different compilers and operating systems.
{
    if (files_count < 2) // exception error if no directory is given
    {
        cerr << "Error: No directory provided. Please enter a valid directory." << endl;
        return 1;
    }

    for (int i = 1; i < files_count; i++) // loop through files in directory and run our function 
    {
        cout << files[i] << ":" << endl;
        list_files(files[i]);
        cout << endl;
    }

    return 0;
}