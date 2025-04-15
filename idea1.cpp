#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream> 
#include<bits/stdc++.h>

using namespace std;

// Authentication System

map<string, pair<string, string>> users = {
    {"admin", {"admin123", "Admin"}},
    {"user", {"user123", "User"}}
};

string currentRole = "";

bool login() {
    string username, password;
    cout << "Enter username: "; cin >> username;
    cout << "Enter password: "; cin >> password;

    if (users.find(username) != users.end() && users[username].first == password) {
        currentRole = users[username].second;
        cout << "Login successful! Role: " << currentRole << "\n";
        return true;
    } else {
        cout << "Invalid credentials!\n";
        return false;
    }
}

// Base Class : ASSET

class Asset {
    protected:
        string assetID, name, owner, location, status;
    public:
        Asset(string assetID, string name, string owner, string location, string status) {
            this->assetID = assetID;
            this->name = name;
            this->owner = owner;
            this->location = location;
            this->status = status;
        }
};
    

// Child Class : HARDWARE CLASSES

class Hardware : public Asset {
    protected:
        double cost;
        string brand, model, buyDate, warrantyExpiry;
    public:
        Hardware(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry)
            : Asset(assetID, name, owner, location, status) {
            this->cost = cost;
            this->brand = brand;
            this->model = model;
            this->buyDate = buyDate;
            this->warrantyExpiry = warrantyExpiry;
        }
};

// ====================== LAPTOP CLASS ======================

class Laptop : public Hardware {
    private:
        string processor;
        int ram, storage;
        double speed;
        string displayType;
    public:
        Laptop(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry,
            string processor, int ram, int storage, double speed, string displayType)
            : Hardware(assetID, name, owner, location, status, cost, brand, model, buyDate, warrantyExpiry) {
            this->processor = processor;
            this->ram = ram;
            this->storage = storage;
            this->speed = speed;
            this->displayType = displayType;
        }
        void AddAsset(){
            ofstream LaptopFile("Laptop.csv", ios::app);  // Open file in append mode

            if (LaptopFile.is_open()) {
                LaptopFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                   << brand << "," << model << "," << buyDate << "," << warrantyExpiry << "," << cost << ","
                   << processor << "," << ram << "," << storage << "," << speed << "," << displayType << "\n";

                cout << "\nData Entered Sucessfully !!!\n";

                LaptopFile.close();
            }
            else {
                cout << "Error: Could not open Laptop.csv for writing." << endl;
            }
        }
};

// ====================== MONITOR CLASS ======================

class Monitor : public Hardware {
    private:
        int size;
        string resolution;
    public:
        Monitor(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry,
            int size, string resolution)
            : Hardware(assetID, name, owner, location, status, cost, brand, model, buyDate, warrantyExpiry) {
            this->size = size;
            this->resolution = resolution;
        }

    void AddAsset() {
        ofstream MonitorFile("Monitor.csv", ios::app);

        if (MonitorFile.is_open()) {
            MonitorFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                        << brand << "," << model << "," << buyDate << "," << warrantyExpiry << "," << cost << ","
                        << size << "," << resolution << "\n";
            
            MonitorFile.close();
            cout << "\nData Entered Sucessfully !!!\n";

        } else {
            cout << "Error: Could not open Monitor.csv for writing." << endl;
        }
    }
};
    
// ====================== KEYBOARD CLASS ======================

class Keyboard : public Hardware {
    private:
        bool mechanical;
    public:
        Keyboard(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry,
            bool mechanical)
            : Hardware(assetID, name, owner, location, status, cost, brand, model, buyDate, warrantyExpiry) {
            this->mechanical = mechanical;
        }
        void AddAsset() {
            ofstream KeyboardFile("Keyboard.csv", ios::app);
    
            if (KeyboardFile.is_open()) {
                KeyboardFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                             << brand << "," << model << "," << buyDate << "," << warrantyExpiry << "," << cost << ","
                             << (mechanical ? "Yes" : "No") << "\n";
                KeyboardFile.close();
                cout << "\nData Entered Sucessfully !!!\n";

            }
            else {
                cout << "Error: Could not open Keyboard.csv for writing." << endl;
            }
        }
};
    
// ====================== MOBILE PHONE CLASS ======================

class MobilePhone : public Hardware {
    private:
        string os;
        int storage;
    public:
        MobilePhone(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry,
            string os, int storage)
            : Hardware(assetID, name, owner, location, status, cost, brand, model, buyDate, warrantyExpiry) {
            this->os = os;
            this->storage = storage;
        }
        void AddAsset() {
            ofstream PhoneFile("Mobile.csv", ios::app);

            if (PhoneFile.is_open()) {
                PhoneFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                      << brand << "," << model << "," << buyDate << "," << warrantyExpiry << "," << cost << ","
                      << os << "," << storage << "\n";

                PhoneFile.close();
            cout << "\nData Entered Sucessfully !!!\n";

            }
            else {
                cout << "Error: Could not open Mobile.csv for writing." << endl;
            }
        }
};
    
// ====================== TABLET CLASS ======================

class Tablet : public Hardware {
    private:
        string os;
        bool stylusSupport;
    public:
        Tablet(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry,
            string os, bool stylusSupport)
            : Hardware(assetID, name, owner, location, status, cost, brand, model, buyDate, warrantyExpiry) {
            this->os = os;
            this->stylusSupport = stylusSupport;
        }

        void AddAsset() {
            ofstream TabletFile("Tablet.csv", ios::app);

            if (TabletFile.is_open()) {
            TabletFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                   << brand << "," << model << "," << buyDate << "," << warrantyExpiry << "," << cost << ","
                   << os << "," << (stylusSupport ? "Yes" : "No") << "\n";
            
            TabletFile.close();
            cout << "\nData Entered Sucessfully !!!\n";

            }
            else {
                cout << "Error: Could not open Tablet.csv for writing." << endl;
            }
        }
};



// ====================== MOUSE CLASS ======================

class Mouse : public Hardware {
    private:
        int dpi;
        bool wireless;
        int buttons;
    public:
        Mouse(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry,
            int dpi, bool wireless, int buttons)
            : Hardware(assetID, name, owner, location, status, cost, brand, model, buyDate, warrantyExpiry) {
            this->dpi = dpi;
            this->wireless = wireless;
            this->buttons = buttons;
        }

        void AddAsset() {
            ofstream MouseFile("Mouse.csv", ios::app);

            if (MouseFile.is_open()) {
                MouseFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                    << brand << "," << model << "," << buyDate << "," << warrantyExpiry << "," << cost << ","
                    << dpi << "," << (wireless ? "Yes" : "No") << "," << buttons << "\n";
            
                MouseFile.close();
                cout << "\nData Entered Sucessfully !!!\n";

            }
            else {
                cout << "Error: Could not open Mouse.csv for writing." << endl;
            }
        }
};

// ====================== HEADPHONES CLASS ======================

class Headphones : public Hardware {
    private:
        bool wireless;
        bool noiseCancelling;
        int batteryLife;
    public:
        Headphones(string assetID, string name, string owner, string location, string status,
            double cost, string brand, string model, string buyDate, string warrantyExpiry,
            bool wireless, bool noiseCancelling, int batteryLife)
            : Hardware(assetID, name, owner, location, status, cost, brand, model, buyDate, warrantyExpiry) {
            this->wireless = wireless;
            this->noiseCancelling = noiseCancelling;
            this->batteryLife = batteryLife;
        }

        void AddAsset() {
            ofstream HeadphonesFile("Headphone.csv", ios::app);

            if (HeadphonesFile.is_open()) {
                HeadphonesFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                    << brand << "," << model << "," << buyDate << "," << warrantyExpiry << "," << cost << ","
                    << (wireless ? "Yes" : "No") << "," << (noiseCancelling ? "Yes" : "No") << "," << batteryLife<< "\n";

                HeadphonesFile.close();
                cout << "\nData Entered Sucessfully !!!\n";

            }
            else {
                cout << "Error: Could not open Headphone.csv for writing." << endl;
            }
        }
};

// ====================== SOFTWARE CLASSES ======================

class Software : public Asset {
    private:
        string vendor, version, licenseType, expiryDate;
        bool autoRenewal;
        int licensesOwned, users;
    public:
        Software(string assetID, string name, string owner, string location, string status,
            string vendor, string version, string licenseType, string expiryDate,
            bool autoRenewal, int licensesOwned, int users)
            : Asset(assetID, name, owner, location, status){
            this->vendor = vendor;
            this->version = version;
            this->licenseType = licenseType;
            this->expiryDate = expiryDate;
            this->autoRenewal = autoRenewal;
            this->licensesOwned = licensesOwned;
            this->users = users;
        }

        void AddAsset() {
            ofstream SoftwareFile("Software.csv", ios::app);

            if (SoftwareFile.is_open()) {
                SoftwareFile << assetID << "," << name << "," << owner << "," << location << "," << status << ","
                    << vendor << "," << version << "," << licenseType << "," << expiryDate << ","
                    << (autoRenewal ? "Yes" : "No") << "," << licensesOwned << "," << users << "\n";
            
                    SoftwareFile.close();
            cout << "\nData Entered Sucessfully !!!\n";

            }
            else {
                cout << "Error: Could not open Software.csv for writing." << endl;
            }
        }
};
    

// ====================== INVENTORY MANAGER ======================

// Showing Inventory

void getFileData(const string& filename){
    ifstream File(filename);

    if (!File) {
        cerr << "Could not open the file!" << endl;
    }
    if (File.peek() == ifstream::traits_type::eof()) {
        cout << "File is empty." << endl;
        return;
    }

    string line;

    while (getline(File, line)) {
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            cout << cell << " ";
        }
        cout << endl;
    }
    File.close();
}

void showInventory(int choice) {
    
    if(choice == 1) getFileData("Laptop.csv");
    else if(choice == 2) getFileData("Mouse.csv");
    else if(choice == 3) getFileData("Headphone.csv");
    else if(choice == 4) getFileData("Monitor.csv");
    else if(choice == 5) getFileData("Keyboard.csv");
    else if(choice == 6) getFileData("Mobile.csv");
    else if(choice == 7) getFileData("Tablet.csv");
    else if(choice == 8) getFileData("Software.csv");
    else cout << "Invalid Choice";
}

vector<string> split(string line) {
    vector<string> result;
    string word;
    stringstream ss(line);
    while (getline(ss, word, ',')) {
        result.push_back(word);
    }
    return result;
}

// Editing Inventory Data

string join(vector<string> data) {
    string line = "";
    for (int i = 0; i < data.size(); i++) {
        line += data[i];
        if (i != data.size() - 1) line += ",";
    }
    return line;
}
    
void editAsset(string filename, vector<string> headers) {
            
    ifstream inFile(filename);
    vector<string> allLines;
    string line, id;
    bool found = false;

    cout << "Enter ID to edit: ";
    cin >> id;

    while (getline(inFile, line)) {
        vector<string> row = split(line);
        if (row[0] == id) {
            found = true;
            cout << "\nCurrent data:\n";
            for (int i = 0; i < headers.size(); i++) {
                cout << headers[i] << ": " << row[i] << endl;
            }

            cout << "\nEnter new data:\n";
            vector<string> newRow;
            string value;
            cin.ignore();
            for (int i = 0; i < headers.size(); i++) {
                cout << headers[i] << ": ";
                getline(cin, value);
                newRow.push_back(value);
            }

            allLines.push_back(join(newRow));
        }
        else {
            allLines.push_back(line);
        }
    }

    inFile.close();

    if (!found) {
        cout << "ID not found!\n";
        return;
    }

    ofstream outFile(filename);
    for (string updatedLine : allLines) {
        outFile << updatedLine << "\n";
    }
    outFile.close();

    cout << "Data updated successfully!\n";
}

// Deleting Data From Inventory

void deleteAsset(string filename) {

    ifstream inFile(filename);
    vector<string> allLines;
    string line, id;
    bool deleted = false;

    cout << "Enter ID to delete: ";
    cin >> id;

    while (getline(inFile, line)) {
        vector<string> row = split(line);
        if (row[0] == id) {
            deleted = true;
            continue;
        }
        allLines.push_back(line);
    }

    inFile.close();

    if (!deleted) {
        cout << "ID not found!\n";
        return;
    }

    ofstream outFile(filename);
    for (string updatedLine : allLines) {
        outFile << updatedLine << "\n";
    }
    outFile.close();

    cout << "Asset with ID '" << id << "' deleted successfully.\n";
}

// Searching Asset From Inventory

void advancedSearch(const string& filename, const string& searchKey, const vector<string>& headers) {

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file \"" << filename << "\"" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string firstCol;
        getline(ss, firstCol, ',');

        if (firstCol == searchKey) {
            cout << "\nMatch found in file: " << filename << "\n" << endl;

            vector<string> row;
            string cell;
            stringstream rowStream(line);

            while (getline(rowStream, cell, ',')) {
                row.push_back(cell);
            }

            for (size_t i = 0; i < headers.size(); ++i) {
                cout << left << setw(15) << headers[i] << ": " << row[i] << endl;
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No matching record found for ID: " << searchKey << endl;
    }

    file.close();
}

// Checking Expiry of Data

bool isExpired(const string& expiryDate) {

    int year, month, day;
    if (sscanf(expiryDate.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return false;
        
    time_t now = time(0);
    tm* current = localtime(&now);
        
    if (year < (1900 + current->tm_year)) return true;
    if (year == (1900 + current->tm_year) && month < (1 + current->tm_mon)) return true;
    if (year == (1900 + current->tm_year) && month == (1 + current->tm_mon) && day < current->tm_mday) return true;
        
    return false;
}
   
        
void checkExpirations(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    if (file.peek() == ifstream::traits_type::eof()) {
        cout << "\nFile is empty." << endl;
        return;
    }
    else{
        cout << "\nChecking: " << filename << endl;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (!row.empty()) {
            if (8 < row.size()) {
                if (isExpired(row[8])) {
                    cout << "ID: " << row[0] << " [EXPIRED] ";
                }
                else{
                    cout << "ID: " << row[0] << " [NOT EXPIRED] ";
                }
            }
            cout << endl;
        }
    }

    file.close();
    }
}

void displayMenu() {
        cout << "\n=== IT INVENTORY MANAGEMENT SYSTEM ===\n";
        cout << "1. Add Hardware\n";
        cout << "2. Add Software\n";
        cout << "3. Show Inventory\n";
        cout << "4. Edit Asset\n";
        cout << "5. Delete Asset\n";
        cout << "6. Search Asset\n";
        cout << "7. Check Expiration\n";
        cout << "8. Exit\n";
        cout << "\nEnter choice: ";
    }

// ========== MAIN FUNCTION ==========

int main() {
    
    if (!login()) return 0;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }

            string id, name, owner, location, brand, model, buyDate, warrantyExpiry;
            
            int cost;
            int hardwareType;

            cout << "Select Hardware Type:\n"; 
            cout << "1. Laptop\n2. Mouse\n3. Headphones\n4. monitor\n5. Keyboard\n6. Mobile\n7. Tablets\nEnter choice: ";
            cin >> hardwareType;
            cin.ignore();
            cout << "Enter Hardware ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Owner: "; getline(cin, owner);
            cout << "Enter Location: "; getline(cin, location);
            cout << "Enter Brand: "; getline(cin, brand);
            cout << "Enter Model: "; getline(cin, model);
            cout << "Enter Buy Date (YYYY-MM-DD): "; getline(cin, buyDate);
            cout << "Enter Warranty Expiry (YYYY-MM-DD): "; getline(cin, warrantyExpiry);
            cout << "Enter Cost: "; cin >> cost;

            if (hardwareType == 1) {  // Laptop
                string processor, displayType;
                int ram, storage;
                double speed;

                cout << "Enter Processor: "; cin >> processor;
                cout << "Enter RAM (GB): "; cin >> ram;
                cout << "Enter Storage (GB): "; cin >> storage;
                cout << "Enter Speed (GHz): "; cin >> speed;
                cout << "Enter Display Type: "; cin >> displayType;
                
                Laptop l1(id, name, owner, location, "In Use", cost, brand, model, buyDate, warrantyExpiry, processor, ram, storage, speed, displayType);
                l1.AddAsset();
            }

            else if (hardwareType == 2) {  // Mouse
                int dpi, buttons;
                bool wireless;

                cout << "Enter DPI: "; cin >> dpi;
                cout << "Wireless (1 for Yes, 0 for No): "; cin >> wireless;
                cout << "Enter Number of Buttons: "; cin >> buttons;
                
                Mouse m1(id, name, owner, location, "In Use", cost, brand, model, buyDate, warrantyExpiry, dpi, wireless, buttons);
                m1.AddAsset();
            }

            else if (hardwareType == 3) {  // Headphones
                bool wireless, noiseCancelling;
                int batteryLife;

                cout << "Wireless (1 for Yes, 0 for No): "; cin >> wireless;
                cout << "Noise Cancelling (1 for Yes, 0 for No): "; cin >> noiseCancelling;
                cout << "Enter Battery Life (hours): "; cin >> batteryLife;
            
                Headphones h1(id, name, owner, location, "In Use", cost, brand, model, buyDate, warrantyExpiry, wireless, noiseCancelling, batteryLife);
                h1.AddAsset();
            }

            if (hardwareType == 4) {  // Monitor
                int size;
                string resolution;
                cout << "Enter Size (in inches): "; cin >> size;
                cout << "Enter Resolution: "; cin >> resolution;
            
                Monitor m1(id, name, owner, location, "In Use", cost, brand, model, buyDate, warrantyExpiry, size, resolution);
                m1.AddAsset();
            }
            
            else if (hardwareType == 5) {  // Keyboard
                bool mechanical;
                cout << "Mechanical (1 for Yes, 0 for No): "; cin >> mechanical;
                
                Keyboard k1(id, name, owner, location, "In Use", cost, brand, model, buyDate, warrantyExpiry, mechanical);
                k1.AddAsset();
            }
            
            else if (hardwareType == 6) {  // Mobile Phone
                string os;
                int storage;
                cout << "Enter OS: "; cin >> os;
                cout << "Enter Storage (GB): "; cin >> storage;
            
                MobilePhone p1(id, name, owner, location, "In Use", cost, brand, model, buyDate, warrantyExpiry, os, storage);
                p1.AddAsset();
            }
            
            else if (hardwareType == 7) {  // Tablet
                string os;
                bool stylusSupport;
                cout << "Enter OS: "; cin >> os;
                cout << "Stylus Support (1 for Yes, 0 for No): "; cin >> stylusSupport;
            
                Tablet t1(id, name, owner, location, "In Use", cost, brand, model, buyDate, warrantyExpiry, os, stylusSupport);
                t1.AddAsset();
            }
        }

        else if (choice == 2) {
            if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }
            
            string id, name, owner, location, vendor, version, licenseType, expiryDate;
            bool autoRenewal;
            int licensesOwned, users;
            
            cout << "Enter Software ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Product Name: "; getline(cin, name);
            cout << "Enter Owner: "; getline(cin, owner);
            cout << "Enter Location: "; getline(cin, location);
            cout << "Enter Vendor: "; getline(cin, vendor);
            cout << "Enter Version: "; getline(cin, version);
            cout << "Enter License Type: "; getline(cin, licenseType);
            cout << "Enter Expiry Date (YYYY-MM-DD): "; getline(cin, expiryDate);
            cout << "Auto-Renewal (1 for Yes, 0 for No): "; cin >> autoRenewal;
            cout << "Enter Number of Licenses Owned: "; cin >> licensesOwned;
            cout << "Enter Number of Users: "; cin >> users;
    
            Software s1(id, name, owner, location, "In Use", vendor, version, licenseType, expiryDate, autoRenewal, licensesOwned, users);
            s1.AddAsset();
        }

        else if (choice == 3) {
            int inventoryChoice;

            cout << "\nSelect Which Inventory To Show\n";
            cout << "1. Laptop\n";
            cout << "2. Mouse\n";
            cout << "3. Headphones\n";
            cout << "4. Monitor\n";
            cout << "5. Keyboard\n";
            cout << "6. Mobile\n";
            cout << "7. Tablet\n";
            cout << "8. Software\n";
            cout << "Enter choice: "; cin >> inventoryChoice;
            
            showInventory(inventoryChoice);
        }
        else if (choice == 4) {
          if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }
            int editChoice;
            string filename;
            vector<string> headers;
            
            cout << "\nSelect Which Asset To Edit\n";
            cout << "1. Laptop\n";
            cout << "2. Mouse\n";
            cout << "3. Headphones\n";
            cout << "4. Monitor\n";
            cout << "5. Keyboard\n";
            cout << "6. Mobile\n";
            cout << "7. Tablet\n";
            cout << "8. Software\n";
            cout << "Enter choice: "; cin >> editChoice;
            
            if(editChoice == 1){
                filename = "Laptop.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Processor", "RAM", "Storage", "Speed", "Display Type"};
            } 
                
            else if(editChoice == 2){
                filename = "Mouse.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "DPI", "Wireless ?", "Buttons"};

            } 

            else if(editChoice == 3){
                filename = "Headphone.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Wireless ?", "Noise Cancelling ?"};

            } 

            else if(editChoice == 4){
                filename = "Monitor.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Size", "Resolution"};

            } 

            else if(editChoice == 5){
                filename = "Keyboard.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Mechanical ?"};

            } 
            
            else if(editChoice == 6){
                filename = "Mobile.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Storage"};

            } 

            else if(editChoice == 7){
                filename = "Tablet.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Stylus Support ?"};

            } 

            else if(editChoice == 8){
                filename = "Software.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Vendor", "Version", "License Type", "Expiry Date", "Auto Renewal ?", "Licenses Owned", "Users"};

            } 

            else cout << "Invalid Choice";

            editAsset(filename, headers);
        }

        else if (choice == 5) {
            if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }

            int deleteChoice;
            string filename;

            cout << "\nSelect Which Asset To Delete\n";
            cout << "1. Laptop\n";
            cout << "2. Mouse\n";
            cout << "3. Headphones\n";
            cout << "4. Monitor\n";
            cout << "5. Keyboard\n";
            cout << "6. Mobile\n";
            cout << "7. Tablet\n";
            cout << "8. Software\n";
            cout << "Enter choice: "; cin >> deleteChoice;
            
            if(deleteChoice == 1) filename = "Laptop.csv";
            else if(deleteChoice == 2) filename = "Mouse.csv";
            else if(deleteChoice == 3) filename = "Headphone.csv";
            else if(deleteChoice == 4) filename = "Monitor.csv";
            else if(deleteChoice == 5) filename = "Keyboard.csv";
            else if(deleteChoice == 6) filename = "Mobile.csv";
            else if(deleteChoice == 7) filename = "Tablet.csv";
            else if(deleteChoice == 8) filename = "Software.csv";
            else cout << "Invalid Choice";

            deleteAsset(filename);
        }

        else if (choice == 6) {

            int searchChoice;
            string filename, searchKey;
            vector<string> headers;

            cout << "\nSelect Which Asset To Searchn\n";
            cout << "1. Laptop\n";
            cout << "2. Mouse\n";
            cout << "3. Headphones\n";
            cout << "4. Monitor\n";
            cout << "5. Keyboard\n";
            cout << "6. Mobile\n";
            cout << "7. Tablet\n";
            cout << "8. Software\n";
            cout << "Enter choice: "; cin >> searchChoice;
            
            if(searchChoice == 1){
                filename = "Laptop.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Processor", "RAM", "Storage", "Speed", "Display Type"};
            } 
                
            else if(searchChoice == 2){
                filename = "Mouse.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "DPI", "Wireless ?", "Buttons"};

            } 

            else if(searchChoice == 3){
                filename = "Headphone.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Wireless ?", "Noise Cancelling ?"};

            } 

            else if(searchChoice == 4){
                filename = "Monitor.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Size", "Resolution"};

            } 

            else if(searchChoice == 5){
                filename = "Keyboard.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Mechanical ?"};

            } 
            
            else if(searchChoice == 6){
                filename = "Mobile.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Storage"};

            } 

            else if(searchChoice == 7){
                filename = "Tablet.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Stylus Support ?"};

            } 

            else if(searchChoice == 8){
                filename = "Software.csv";
                headers = {"ID", "Name", "Owner", "Location", "Status", "Vendor", "Version", "License Type", "Expiry Date", "Auto Renewal ?", "Licenses Owned", "Users"};

            } 

            else cout << "Invalid Choice";

            cout << "Enter ID to search: "; cin >> searchKey;
            
            advancedSearch(filename, searchKey, headers);
        }

        else if (choice == 7){
            
            int ExpiryChoice;
            string filename;

            cout << "\nSelect Which Asset To Check Expiry\n";
            cout << "1. Laptop\n";
            cout << "2. Mouse\n";
            cout << "3. Headphones\n";
            cout << "4. Monitor\n";
            cout << "5. Keyboard\n";
            cout << "6. Mobile\n";
            cout << "7. Tablet\n";
            cout << "8. Software\n";
            cout << "Enter choice: "; cin >> ExpiryChoice;
            
            if(ExpiryChoice == 1) filename = "Laptop.csv";
            else if(ExpiryChoice == 2) filename = "Mouse.csv";
            else if(ExpiryChoice == 3) filename = "Headphone.csv";
            else if(ExpiryChoice == 4) filename = "Monitor.csv";
            else if(ExpiryChoice == 5) filename = "Keyboard.csv";
            else if(ExpiryChoice == 6) filename = "Mobile.csv";
            else if(ExpiryChoice == 7) filename = "Tablet.csv";
            else if(ExpiryChoice == 8) filename = "Software.csv";
            else cout << "Invalid Choice";

            checkExpirations(filename);
        }

        else if (choice == 8) {
            cout << "Exiting...\n";
            break;
        }
    }

    return 0;
}
