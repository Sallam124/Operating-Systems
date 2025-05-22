#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
using namespace std;

void print_file_sizes(int bandwidth_increments, string& directory)
{
    map<string, int> filename_size;
    int file_count = 0;
    int max_size = 0;

    for (const auto& entry : filesystem::directory_iterator(directory))
    {
        int file_size = filesystem::file_size(entry.path());
        filename_size[entry.path().string()] = file_size;
        file_count++;

        if (file_size > max_size)
        {
            max_size = file_size;
        }
    }

    for (int i = bandwidth_increments; i < max_size; i += bandwidth_increments)
    {
        int files_in_bandwidth = 0;
        auto it = filename_size.begin();

        while (it != filename_size.end()) {
            if (it->second < i) {
                files_in_bandwidth++;
                it = filename_size.erase(it);
            }
            else {
                ++it;
            }
        }
        cout << "Number of files in bandwidth " << i - bandwidth_increments << " to " << i << " is/are: " << files_in_bandwidth << endl;
    }
}

int main()
{
    string directory = "C:\\Users\\salla\\OneDrive\\Desktop\\Operating-Systems\\Task 5\\Test_dir";
    print_file_sizes(1024, directory);
    return 0;
}
