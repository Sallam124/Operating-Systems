#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx; // Mutex for thread safety

// Function to process each segment and count word frequencies
void countWords(const string& segment, map<string, int>& wordCount, int threadId) {
    auto start = chrono::high_resolution_clock::now(); // Start time

    stringstream ss(segment);
    string word;

    while (ss >> word) {
        // Process the word (e.g., convert to lowercase, remove punctuation)
        for (char& ch : word) {
            ch = tolower(ch);
        }

        // Increment word count
        {
            lock_guard<mutex> lock(mtx); // Lock the mutex to ensure thread-safe access
            wordCount[word]++;
        }
    }

    auto end = chrono::high_resolution_clock::now(); // End time
    chrono::duration<double> duration = end - start;
    cout << "Thread " << threadId << " execution time: " << duration.count() << " seconds." << endl;
}

vector<string> segment(const string& text) {
    vector<string> segments;
    string current_segment = "";

    for (char c : text) {
        current_segment += c; // Keep adding characters to the string
        if (c == '.') {
            segments.push_back(current_segment);
            current_segment = ""; // Reset the string for the next segment
        }
    }
    if (!current_segment.empty()) {
        segments.push_back(current_segment);
    }
    return segments;
}

string read_file(const string& file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Error: File could not be opened!" << endl;
        return "";
    }

    // Use stringstream to read the file content
    stringstream read;
    read << file.rdbuf(); // Read the entire file content

    return read.str(); // Return the content as a string
}

int main() {
    string text = read_file("C:\\Users\\salla\\OneDrive\\Desktop\\Text Parsing\\Text.txt"); // Read the file content

    vector<string> segments = segment(text);

    // Shared map to store word frequencies that the threads will work on
    map<string, int> wordCount;

    // Vector to hold threads
    vector<thread> threads;

    // Create and launch a thread for each segment
    for (int i = 0; i < segments.size(); ++i) {
        threads.push_back(thread(countWords, ref(segments[i]), ref(wordCount), i + 1));
    }

    // Join all threads (wait for all of them to finish)
    for (thread& t : threads) {
        t.join();
    }

    // Print the word frequencies
    cout << "Word frequencies:" << endl;
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
