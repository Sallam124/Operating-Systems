#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

// Class representing a single page
class Page {
public:
    int id;
    unsigned int age; 

    // Constructor initializing the page with an ID and resetting the age
    Page(int id = -1) {
        this->id = id;
        this->age = 0;
    }
};

// Class implementing the aging page replacement algorithm
class AgingAlgorithm {
private:
    int numFrames; // Number of available frames
    vector<Page> frames; // List of frames storing pages
    unordered_map<int, int> pageMap; // Mapping of page ID to frame index

public:
    // Constructor initializing the algorithm with a given number of frames
    AgingAlgorithm(int framesCount) : numFrames(framesCount), frames(framesCount) {}

    // Checks if a page is already in memory
    bool pageExists(int pageId) {
        return pageMap.find(pageId) != pageMap.end();
    }

    // Updates the aging counter for each page by right-shifting its age
    void updateAges() {
        for (Page& frame : frames) {
            frame.age >>= 1; // Shift age to the right, decreasing its priority
        }
    }

    // Inserts a page into memory using the aging algorithm
    void insertPage(int pageId, int& pageFaults) {
        updateAges(); 

        if (pageExists(pageId)) {
            // If the page is already in memory, set the most significant bit
            frames[pageMap[pageId]].age |= (1 << 7);
        }
        else {
            // Page fault occurs since the page is not in memory
            pageFaults++;
            int victimIndex = 0;

            // Find the page with the lowest age (least recently used)
            for (int i = 1; i < numFrames; i++) {
                if (frames[i].age < frames[victimIndex].age) {
                    victimIndex = i;
                }
            }

            // Replace the victim page with the new page
            pageMap.erase(frames[victimIndex].id);
            frames[victimIndex] = Page(pageId);
            frames[victimIndex].age = (1 << 7); // Assign highest priority to the new page
            pageMap[pageId] = victimIndex;
        }
    }
};

// Reads page references from a file
void readPagesFromFile(const string& filename, vector<int>& pageReferences) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    int pageId;
    while (file >> pageId) {
        pageReferences.push_back(pageId);
    }
    file.close();
}

int main() {
    string filename = "C:\\Users\\salla\\OneDrive\\Desktop\\Paging_Sim\\paging_text.txt";
    vector<int> pageReferences;

    readPagesFromFile(filename, pageReferences);

    // Define different frame sizes to test the algorithm
    vector<int> framesSizes = { 2, 4, 8, 16 };

    // Simulate the aging algorithm for each frame size
    for (int frames : framesSizes) {
        AgingAlgorithm aging(frames);
        int pageFaults = 0;

        // Process each page reference
        for (int pageId : pageReferences) {
            aging.insertPage(pageId, pageFaults);
        }

        cout << "Page Faults with " << frames << " frames: " << pageFaults << endl;
    }
    return 0;
}
