#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Structure to store item details
struct Item {
    int id;
    string itemName;
    string category;
    string description;
    string status; // "Lost" or "Found"
    string reportedBy;
    string contact;
};

// Global variables (acting as our database in memory)
const int MAX_ITEMS = 100;
Item items[MAX_ITEMS];
int itemCount = 0;
const string FILE_NAME = "records.txt";

// Function Declarations
void loadFromFile();
void saveToFile();
bool studentLogin();
void reportLostItem();
void reportFoundItem();
void searchItem();
void autoMatch();
void viewAllRecords();
void deleteRecord();
void itemStatistics();
void exportReport();
void displayMenu();

int main() {
    cout << "======================================================\n";
    cout << "    Smart Campus Lost & Found Management System       \n";
    cout << "======================================================\n";

    if (!studentLogin()) {
        cout << "Login failed! Exiting system...\n";
        return 0;
    }

    loadFromFile(); // Load existing records from file

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice (1-10): ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice) {
            case 1: cout << "\nAlready Logged In.\n"; break;
            case 2: reportLostItem(); break;
            case 3: reportFoundItem(); break;
            case 4: searchItem(); break;
            case 5: autoMatch(); break;
            case 6: viewAllRecords(); break;
            case 7: deleteRecord(); break;
            case 8: itemStatistics(); break;
            case 9: exportReport(); break;
            case 10: 
                saveToFile();
                cout << "Data saved. Exiting the system. Goodbye!\n"; 
                break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}

// 1. Student Login Module
bool studentLogin() {
    string username, password;
    cout << "\n--- Student Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Hardcoded for demonstration (you can expand this)
    if (username == "student" && password == "1234") {
        cout << "Login Successful!\n";
        return true;
    }
    return false;
}

// Menu Display
void displayMenu() {
    cout << "\n----------------- MAIN MENU -----------------\n";
    cout << "1. Student Login\n";
    cout << "2. Report Lost Item\n";
    cout << "3. Report Found Item\n";
    cout << "4. Search Item\n";
    cout << "5. Auto Match Lost & Found\n";
    cout << "6. View All Records\n";
    cout << "7. Delete Record\n";
    cout << "8. Item Statistics\n";
    cout << "9. Export Report\n";
    cout << "10. Exit\n";
    cout << "---------------------------------------------\n";
}

// 2. Report Lost Item
void reportLostItem() {
    if (itemCount >= MAX_ITEMS) {
        cout << "Storage full! Cannot add more items.\n";
        return;
    }
    Item newItem;
    newItem.id = itemCount + 1;
    newItem.status = "Lost";

    cout << "\n--- Report Lost Item ---\n";
    cout << "Enter Item Name: "; getline(cin, newItem.itemName);
    cout << "Enter Category (e.g., Electronics, ID, Wallet): "; getline(cin, newItem.category);
    cout << "Enter Description: "; getline(cin, newItem.description);
    cout << "Your Name: "; getline(cin, newItem.reportedBy);
    cout << "Contact Info: "; getline(cin, newItem.contact);

    items[itemCount] = newItem;
    itemCount++;
    saveToFile();
    cout << "Lost item reported successfully! ID: " << newItem.id << "\n";
}

// 3. Report Found Item
void reportFoundItem() {
    if (itemCount >= MAX_ITEMS) {
        cout << "Storage full! Cannot add more items.\n";
        return;
    }
    Item newItem;
    newItem.id = itemCount + 1;
    newItem.status = "Found";

    cout << "\n--- Report Found Item ---\n";
    cout << "Enter Item Name: "; getline(cin, newItem.itemName);
    cout << "Enter Category: "; getline(cin, newItem.category);
    cout << "Enter Description: "; getline(cin, newItem.description);
    cout << "Your Name (Finder): "; getline(cin, newItem.reportedBy);
    cout << "Contact Info: "; getline(cin, newItem.contact);

    items[itemCount] = newItem;
    itemCount++;
    saveToFile();
    cout << "Found item reported successfully! ID: " << newItem.id << "\n";
}

// 4. Search Item
void searchItem() {
    string keyword;
    cout << "\n--- Search Item ---\n";
    cout << "Enter item name or category to search: ";
    getline(cin, keyword);

    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (items[i].itemName.find(keyword) != string::npos || items[i].category.find(keyword) != string::npos) {
            cout << "\nID: " << items[i].id << " | " << items[i].itemName << " (" << items[i].status << ")\n";
            cout << "Category: " << items[i].category << "\nDescription: " << items[i].description << "\n";
            cout << "Reported By: " << items[i].reportedBy << " | Contact: " << items[i].contact << "\n";
            found = true;
        }
    }
    if (!found) cout << "No items found matching '" << keyword << "'.\n";
}

// 5. Auto Match Lost & Found
void autoMatch() {
    cout << "\n--- Auto Match Results ---\n";
    bool matchFound = false;
    for (int i = 0; i < itemCount; i++) {
        if (items[i].status == "Lost") {
            for (int j = 0; j < itemCount; j++) {
                if (items[j].status == "Found" && items[i].category == items[j].category && items[i].itemName == items[j].itemName) {
                    cout << "Possible Match Found!\n";
                    cout << "Lost Item ID: " << items[i].id << " matches Found Item ID: " << items[j].id << "\n";
                    cout << "Item Name: " << items[i].itemName << "\n";
                    cout << "Contact Finder: " << items[j].contact << "\n--------------------------\n";
                    matchFound = true;
                }
            }
        }
    }
    if (!matchFound) cout << "No automatic matches found at this time.\n";
}

// 6. View All Records
void viewAllRecords() {
    cout << "\n--- All Records ---\n";
    if (itemCount == 0) {
        cout << "No records available.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Category" << setw(10) << "Status" << "Contact\n";
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < itemCount; i++) {
        cout << left << setw(5) << items[i].id << setw(15) << items[i].itemName 
             << setw(15) << items[i].category << setw(10) << items[i].status 
             << items[i].contact << "\n";
    }
}

// 7. Delete Record
void deleteRecord() {
    int idToDelete;
    cout << "\n--- Delete Record ---\n";
    cout << "Enter the ID of the record to delete: ";
    cin >> idToDelete;

    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == idToDelete) {
            found = true;
            // Shift elements left
            for (int j = i; j < itemCount - 1; j++) {
                items[j] = items[j + 1];
            }
            itemCount--;
            cout << "Record deleted successfully.\n";
            saveToFile();
            break;
        }
    }
    if (!found) cout << "Record with ID " << idToDelete << " not found.\n";
}

// 8. Item Statistics
void itemStatistics() {
    int lostCount = 0, foundCount = 0;
    for (int i = 0; i < itemCount; i++) {
        if (items[i].status == "Lost") lostCount++;
        else if (items[i].status == "Found") foundCount++;
    }
    cout << "\n--- Item Statistics ---\n";
    cout << "Total Records: " << itemCount << "\n";
    cout << "Total Items Lost: " << lostCount << "\n";
    cout << "Total Items Found: " << foundCount << "\n";
}

// 9. Export Report
void exportReport() {
    ofstream outFile("System_Report.txt");
    if (!outFile) {
        cout << "Error creating export file!\n";
        return;
    }
    
    int lostCount = 0, foundCount = 0;
    outFile << "--- Smart Campus Lost & Found Report ---\n\n";
    outFile << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Status" << "Reported By\n";
    outFile << "------------------------------------------------\n";
    
    for (int i = 0; i < itemCount; i++) {
        outFile << left << setw(5) << items[i].id << setw(15) << items[i].itemName 
                << setw(10) << items[i].status << items[i].reportedBy << "\n";
        
        if (items[i].status == "Lost") lostCount++;
        else foundCount++;
    }
    
    outFile << "\n--- Statistics ---\n";
    outFile << "Total Lost: " << lostCount << "\n";
    outFile << "Total Found: " << foundCount << "\n";
    
    outFile.close();
    cout << "Report exported successfully to 'System_Report.txt'\n";
}

// File Handling: Load
void loadFromFile() {
    ifstream inFile(FILE_NAME);
    if (!inFile) return; // File doesn't exist yet, which is fine

    itemCount = 0;
    while (inFile >> items[itemCount].id) {
        inFile.ignore(); // ignore newline
        getline(inFile, items[itemCount].itemName);
        getline(inFile, items[itemCount].category);
        getline(inFile, items[itemCount].description);
        getline(inFile, items[itemCount].status);
        getline(inFile, items[itemCount].reportedBy);
        getline(inFile, items[itemCount].contact);
        itemCount++;
    }
    inFile.close();
}

// File Handling: Save
void saveToFile() {
    ofstream outFile(FILE_NAME);
    if (!outFile) {
        cout << "Error saving database!\n";
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        outFile << items[i].id << "\n"
                << items[i].itemName << "\n"
                << items[i].category << "\n"
                << items[i].description << "\n"
                << items[i].status << "\n"
                << items[i].reportedBy << "\n"
                << items[i].contact << "\n";
    }
    outFile.close();
}