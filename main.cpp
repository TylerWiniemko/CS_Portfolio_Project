#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// Class to encapsulate grocery item operations
class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    GroceryTracker() {
        LoadData("CS210_Project_Three_Input_File.txt");
        WriteBackup("frequency.dat");
    }

    void LoadData(const string& filename) {
        ifstream inFile(filename);
        string item;

        if (!inFile.is_open()) {
            cerr << "Error: Unable to open input file.\n";
            return;
        }

        while (inFile >> item) {
            itemFrequency[item]++;
        }

        inFile.close();
    }

    void WriteBackup(const string& filename) {
        ofstream outFile(filename);

        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
    }

    int GetItemFrequency(const string& item) const {
        auto it = itemFrequency.find(item);
        return (it != itemFrequency.end()) ? it->second : 0;
    }

    void PrintAllFrequencies() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void PrintHistogram() const {
        for (const auto& pair : itemFrequency) {
            cout << left << setw(12) << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

void PrintMenu() {
    cout << "\n=== Corner Grocer Menu ===\n";
    cout << "1. Search for an item\n";
    cout << "2. View all item frequencies\n";
    cout << "3. View histogram\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    GroceryTracker tracker;
    int choice;
    string item;

    do {
        PrintMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item to search: ";
                cin >> item;
                cout << item << " was purchased " << tracker.GetItemFrequency(item) << " time(s)." << endl;
                break;
            case 2:
                tracker.PrintAllFrequencies();
                break;
            case 3:
                tracker.PrintHistogram();
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 4);

    return 0;
}
