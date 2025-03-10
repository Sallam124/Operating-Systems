#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

using namespace std;

// Function to generate page sequences with locality of reference
vector<vector<int>> generate_page(int page_size, float probability, int length_of_sequence, int num_of_page_sequences, int lower_range, int higher_range) {
    vector<vector<int>> pages(num_of_page_sequences);
    srand(time(0)); // Ensure different sequences each run
    int range_size = higher_range - lower_range + 1; // Total valid numbers

    for (int i = 0; i < num_of_page_sequences; i++) {
        int current_num = rand() % range_size + lower_range; // Start with a random number in range
        pages[i].push_back(current_num);

        for (int j = 1; j < length_of_sequence; j++) {
            if ((rand() % 100) < (probability * 100)) {
                // Stay on the same number based on probability
                pages[i].push_back(current_num);
            }
            else {
                // Pick a new number in range (different from the current one)
                int new_num;
                do {
                    new_num = rand() % range_size + lower_range;
                } while (new_num == current_num); // Ensure it's different

                pages[i].push_back(new_num);
                current_num = new_num; // Update current number
            }
        }
    }
    return pages;
}

// Function to simulate FIFO page replacement for a single process
int fifo_page_replacement(const vector<int>& pages, int frame_size) {
    int page_faults = 0;
    queue<int> frame;                     // FIFO queue for maintaining order
    unordered_set<int> current_pages;      // Set for quick page lookups

    for (int page : pages) {
        // If the page is NOT already in memory
        if (current_pages.find(page) == current_pages.end()) {
            // If frame is full, remove the oldest page (FIFO)
            if (frame.size() == frame_size) {
                int oldest_element = frame.front(); // Save the element before deleting so we can remove it from the set
                frame.pop();
                current_pages.erase(oldest_element);  // Remove from the set
            }

            // Add the new page
            frame.push(page);
            current_pages.insert(page);
            page_faults++;
        }
    }
    return page_faults;
}

// Function to simulate FIFO page replacement using a global frame pool shared by all processes
int fifo_global(const vector<vector<int>>& processes, int frame_size) {
    int page_faults = 0;
    queue<int> frame;                     // FIFO queue for global replacement
    unordered_set<int> current_pages;      // Set for tracking pages in memory

    for (const vector<int>& pages : processes) {
        for (int page : pages) {
            if (current_pages.find(page) == current_pages.end()) {
                // If frame is full, remove the oldest page (FIFO)
                if (frame.size() == frame_size) {
                    int oldest = frame.front();
                    frame.pop();
                    current_pages.erase(oldest);
                }

                // Add the new page
                frame.push(page);
                current_pages.insert(page);
                page_faults++;
            }
        }
    }
    return page_faults;
}

int main() {
    int length_of_sequence = 10;
    int num_of_page_sequences = 3;
    int lower_range = 0;
    int higher_range = 9;
    float probability = 0.3; // 30% chance to stay on the same number
    int local_frame_size = 3; // Each process has 3 frames in local FIFO
    int global_frame_size = 4; // All processes share 4 frames in global FIFO

    // Generate page sequences
    vector<vector<int>> pages = generate_page(10, probability, length_of_sequence, num_of_page_sequences, lower_range, higher_range);

    // Print the generated sequences
    cout << "\nGenerated Page Sequences:\n";
    for (int i = 0; i < pages.size(); i++) {
        cout << "Sequence " << i << ": ";
        for (int num : pages[i]) {
            cout << num << " ";
        }
        cout << endl;
    }

    // Calculate and print page faults for local FIFO
    cout << "\nLocal FIFO Page Faults:\n";
    for (int i = 0; i < num_of_page_sequences; i++) {
        cout << "Process " << i << " Page Faults: " << fifo_page_replacement(pages[i], local_frame_size) << endl;
    }

    // Calculate and print page faults for global FIFO
    cout << "\nGlobal FIFO Page Faults:\n";
    cout << "Total Page Faults: " << fifo_global(pages, global_frame_size) << endl;

    return 0;
}
