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

// Simple authentication system
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

// Function to check if a date is within a given number of days from today


bool isExpiringSoon(string expiryDate, int daysThreshold = 30) {
    struct tm expiry = {};
    istringstream ss(expiryDate);
    ss >> get_time(&expiry, "%Y-%m-%d"); // Using std::get_time instead of strptime
    
    if (ss.fail()) {
        cout << "Error parsing date: " << expiryDate << endl;
        return false;
    }

    time_t now = time(nullptr);
    time_t expiryTime = mktime(&expiry);
    double diffDays = difftime(expiryTime, now) / (60 * 60 * 24);

    return diffDays >= 0 && diffDays <= daysThreshold;
}

// ========== BASE CLASS: ASSET ==========

class Asset {
    protected:
        string assetID, name, owner, location, status;
    public:
        Asset(string id, string n, string o, string loc) 
            : assetID(id), name(n), owner(o), location(loc), status("Active") {}
    
        virtual void displayInfo() = 0;
    
        string getAssetID() { return assetID; }
        string getStatus() { return status; }
        void updateStatus(string newStatus) { status = newStatus; }
        void setName(string newName) { name = newName; }
    
        // 🛠 FIX: Add missing getter functions
        string getOwner() { return owner; }
        string getLocation() { return location; }
};
    

// ====================== HARDWARE CLASSES ======================

class Hardware : public Asset {
    protected:
        double cost;
        string brand, model, buyDate, warrantyExpiry;
    public:
        Hardware(string id, string n, string o, string loc, double c, string b, string m, string bd, string we)
            : Asset(id, n, o, loc), cost(c), brand(b), model(m), buyDate(bd), warrantyExpiry(we) {}
    
        virtual void displayInfo() override = 0;
    
        string getWarrantyExpiry() { return warrantyExpiry; }
    
        // 🛠 FIX: Add missing getter function for brand
        string getBrand() { return brand; }
};

// ====================== MONITOR CLASS ======================

class Monitor : public Hardware {
    private:
        int size;
        string resolution;
    public:
        Monitor(string id, string n, string o, string loc, double c, string b, string m, string bd, string we, int s, string r)
            : Hardware(id, n, o, loc, c, b, m, bd, we), size(s), resolution(r) {}
        void displayInfo() override {
            cout << "[Monitor] " << name << " | Brand: " << brand << " | Size: " << size << " inches | Resolution: " << resolution << "\n";
        }
};
    
// ====================== KEYBOARD CLASS ======================

class Keyboard : public Hardware {
    private:
        bool mechanical;
    public:
        Keyboard(string id, string n, string o, string loc, double c, string b, string m, string bd, string we, bool mech)
            : Hardware(id, n, o, loc, c, b, m, bd, we), mechanical(mech) {}
        void displayInfo() override {
            cout << "[Keyboard] " << name << " | Brand: " << brand << " | Mechanical: " << (mechanical ? "Yes" : "No") << "\n";
        }
};
    
// ====================== MOBILE PHONE CLASS ======================

class MobilePhone : public Hardware {
    private:
        string os;
        int storage;
    public:
        MobilePhone(string id, string n, string o, string loc, double c, string b, string m, string bd, string we, string osType, int st)
            : Hardware(id, n, o, loc, c, b, m, bd, we), os(osType), storage(st) {}
        void displayInfo() override {
            cout << "[Mobile Phone] " << name << " | Brand: " << brand << " | OS: " << os << " | Storage: " << storage << "GB\n";
        }
};
    
// ====================== TABLET CLASS ======================

class Tablet : public Hardware {
    private:
        string os;
        bool stylusSupport;
    public:
        Tablet(string id, string n, string o, string loc, double c, string b, string m, string bd, string we, string osType, bool stylus)
            : Hardware(id, n, o, loc, c, b, m, bd, we), os(osType), stylusSupport(stylus) {}
        void displayInfo() override {
            cout << "[Tablet] " << name << " | Brand: " << brand << " | OS: " << os << " | Stylus Support: " << (stylusSupport ? "Yes" : "No") << "\n";
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
        Laptop(string id, string n, string o, string loc, double c, string b, string m, string bd, string we, 
               string proc, int r, int st, double s, string dt)
            : Hardware(id, n, o, loc, c, b, m, bd, we), processor(proc), ram(r), storage(st), speed(s), displayType(dt) {}
        
    
        void displayInfo() override {
            cout << "[Laptop] " << name << " | Brand: " << brand << " | Model: " << model 
                << " | Processor: " << processor << " | RAM: " << ram << "GB | Storage: " << storage << "GB | Speed: " << speed 
                << "GHz | Display: " << displayType << " | Cost: $" << cost
                << " | Buy Date: " << buyDate << " | Warranty Expiry: " << warrantyExpiry 
                << " | Status: " << status << endl;
    }
};

// ====================== MOUSE CLASS ======================

class Mouse : public Hardware {
    private:
        int dpi;
        bool wireless;
        int buttons;
    public:
        Mouse(string id, string n, string o, string loc, double c, string b, string m, string bd, string we,
            int d, bool w, int btns)
            : Hardware(id, n, o, loc, c, b, m, bd, we), dpi(d), wireless(w), buttons(btns) {}

    void displayInfo() override {
        cout << "[Mouse] " << name << " | Brand: " << brand << " | Model: " << model 
             << " | DPI: " << dpi << " | Wireless: " << (wireless ? "Yes" : "No") 
             << " | Buttons: " << buttons << " | Cost: $" << cost
             << " | Buy Date: " << buyDate << " | Warranty Expiry: " << warrantyExpiry 
             << " | Status: " << status << endl;
    }
};

// ====================== HEADPHONES CLASS ======================

class Headphones : public Hardware {
    private:
        bool wireless;
        bool noiseCancelling;
        int batteryLife;
    public:
        Headphones(string id, string n, string o, string loc, double c, string b, string m, string bd, string we,
                bool w, bool nc, int bl)
            : Hardware(id, n, o, loc, c, b, m, bd, we), wireless(w), noiseCancelling(nc), batteryLife(bl) {}

    void displayInfo() override {
        cout << "[Headphones] " << name << " | Brand: " << brand << " | Model: " << model 
             << " | Wireless: " << (wireless ? "Yes" : "No") 
             << " | Noise Cancelling: " << (noiseCancelling ? "Yes" : "No")
             << " | Battery Life: " << batteryLife << " hrs | Cost: $" << cost
             << " | Buy Date: " << buyDate << " | Warranty Expiry: " << warrantyExpiry 
             << " | Status: " << status << endl;
    }
};

// ====================== SOFTWARE CLASSES ======================

class Software : public Asset {
    private:
        string vendor, version, licenseType, expiryDate;
        bool autoRenewal;
        int licensesOwned, users;
    public:
        Software(string id, string n, string o, string loc, string v, string ver, string lt, string ed, bool ar, int lo, int u)
            : Asset(id, n, o, loc), vendor(v), version(ver), licenseType(lt), expiryDate(ed), autoRenewal(ar), licensesOwned(lo), users(u) {}
    
        void displayInfo() override {
            cout << "[Software] " << name << " | Vendor: " << vendor 
                 << " | Version: " << version 
                 << " | License Type: " << licenseType 
                 << " | Expiry: " << expiryDate
                 << " | Auto-Renewal: " << (autoRenewal ? "Yes" : "No") 
                 << " | Licenses: " << licensesOwned 
                 << " | Users: " << users << "\n";
        }
    
        string getExpiryDate() { return expiryDate; }
};
    

// ====================== INVENTORY MANAGER ======================

class InventoryManager {
    private:
        static InventoryManager* instance;
        map<string, shared_ptr<Asset>> assets;
        InventoryManager() {    
            
        }

    public:
        static InventoryManager* getInstance() {
            if (!instance)
                instance = new InventoryManager();
            return instance;
        }

        void addAsset(shared_ptr<Asset> a) {
            assets[a->getAssetID()] = a;
            cout << "Asset " << a->getAssetID() << " added to inventory!\n";
            
        }

        void getFileData(const string& filename){
            ifstream File(filename);

            if (!File) {
                cerr << "Could not open the file!" << endl;
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
                    cin.ignore(); // clear input buffer
                    for (int i = 0; i < headers.size(); i++) {
                        cout << headers[i] << ": ";
                        getline(cin, value);
                        newRow.push_back(value);
                    }

                    allLines.push_back(join(newRow)); // add updated row
                }
                else {
                    allLines.push_back(line); // keep old row
                }
            }

            inFile.close();

            if (!found) {
                cout << "ID not found!\n";
                return;
            }

            // Rewrite the file
            ofstream outFile(filename);
            for (string updatedLine : allLines) {
                outFile << updatedLine << "\n";
            }
            outFile.close();

            cout << "Data updated successfully!\n";


        }
    
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
                    continue; // Skip adding this row
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

                    // Split full line into cells
                    while (getline(rowStream, cell, ',')) {
                        row.push_back(cell);
                    }

                    // Display headers and data nicely
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
            
   
        
        void checkExpirations() {  // Now inside InventoryManager
            cout << "\n=== Expiration Alerts ===\n";
            bool found = false;
        
            for (auto &it : assets) {
                shared_ptr<Asset> asset = it.second;
        
                shared_ptr<Software> software = dynamic_pointer_cast<Software>(asset);
                if (software && isExpiringSoon(software->getExpiryDate())) {
                    cout << " ALERT: Software '" << software->getAssetID() 
                         << "' is expiring soon (" << software->getExpiryDate() << ").\n";
                    found = true;
                }
        
                shared_ptr<Hardware> hardware = dynamic_pointer_cast<Hardware>(asset);

                if (hardware && isExpiringSoon(hardware->getWarrantyExpiry())) {
                    cout << " ALERT: Hardware '" << hardware->getAssetID() 
                         << "' warranty is expiring soon (" << hardware->getWarrantyExpiry() << ").\n";
                    found = true;
                }
            }
        
            if (!found) {
                cout << " No upcoming expirations.\n";
            }
        }
};

InventoryManager* InventoryManager::instance = nullptr;

void addingToCsv(){

}



// ========== MAIN FUNCTION ==========
 void displayMenu() {
        cout << "\n=== IT INVENTORY MANAGEMENT SYSTEM ===\n";
        cout << "1. Add Hardware\n";
        cout << "2. Add Software\n";
        cout << "3. Show Inventory\n";
        cout << "4. Edit Asset\n";
        cout << "5. Delete Asset\n";
        cout << "6. Search Asset\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
    }





int main() {
    
    if (!login()) return 0;

    InventoryManager* inventory = InventoryManager::getInstance();
    int choice;

    


    while (true) {
        inventory->checkExpirations();  // Check expirations before menu
        displayMenu();
        cin >> choice;
        cin.ignore();

         if (choice == 1) {
            if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }
            string id, name, owner, location, brand, model, buyDate, warrantyExpiry;
            double cost;
            int hardwareType;

            cout << "Select Hardware Type:\n";
            cout << "1. Laptop\n2. Mouse\n3. Headphones\n4. monitor\n5. keyboard\n6. phone\n7. Tablets\nEnter choice: ";
            cin >> hardwareType;
            cin.ignore();

            cout << "Enter Hardware ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Owner: "; getline(cin, owner);
            cout << "Enter Location: "; getline(cin, location);
            cout << "Enter Brand: "; getline(cin, brand);
            cout << "Enter Model: "; getline(cin, model);
            cout << "Enter Buy Date: "; getline(cin, buyDate);
            cout << "Enter Warranty Expiry: "; getline(cin, warrantyExpiry);
            cout << "Enter Cost: "; cin >> cost;

            shared_ptr<Asset> hardware;

            if (hardwareType == 1) {  // Laptop
                string processor, displayType;
                int ram, storage;
                double speed;
                cout << "Enter Processor: "; cin >> processor;
                cout << "Enter RAM (GB): "; cin >> ram;
                cout << "Enter Storage (GB): "; cin >> storage;
                cout << "Enter Speed (GHz): "; cin >> speed;
                cout << "Enter Display Type: "; cin >> displayType;
                hardware = make_shared<Laptop>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, processor, ram, storage, speed, displayType);
            
                ofstream LaptopFile("Laptop.csv", ios::app);
                LaptopFile << id << "," << name << "," << owner << "," << location << "," << brand << "," << model 
                << "," << buyDate << "," << warrantyExpiry << "," << cost << "," << processor << "," << ram
                << "," << storage << "," << speed << "," << displayType<< "\n";
                LaptopFile.close();
            
            
            }
            else if (hardwareType == 2) {  // Mouse
                int dpi, buttons;
                bool wireless;
                cout << "Enter DPI: "; cin >> dpi;
                cout << "Wireless (1 for Yes, 0 for No): "; cin >> wireless;
                cout << "Enter Number of Buttons: "; cin >> buttons;
                hardware = make_shared<Mouse>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, dpi, wireless, buttons);
            
                ofstream MouseFile("Mouse.csv", ios::app);
                MouseFile << id << "," << name << "," << owner << "," << location << "," << brand << "," << model 
                << "," << buyDate << "," << warrantyExpiry << "," << cost << "," << dpi << "," << wireless
                << "," << buttons << "\n";
                MouseFile.close();
            
            }
            else if (hardwareType == 3) {  // Headphones
                bool wireless, noiseCancelling;
                int batteryLife;
                cout << "Wireless (1 for Yes, 0 for No): "; cin >> wireless;
                cout << "Noise Cancelling (1 for Yes, 0 for No): "; cin >> noiseCancelling;
                cout << "Enter Battery Life (hours): "; cin >> batteryLife;
                hardware = make_shared<Headphones>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, wireless, noiseCancelling, batteryLife);
            
                ofstream HeadphoneFile("Headphone.csv", ios::app);
                HeadphoneFile << id << "," << name << "," << owner << "," << location << "," << brand << "," << model 
                << "," << buyDate << "," << warrantyExpiry << "," << cost << "," << wireless << "," << noiseCancelling << "\n";
                HeadphoneFile.close();
            
            }

            if (hardwareType == 4) {  // Monitor
                int size;
                string resolution;
                cout << "Enter Size (in inches): "; cin >> size;
                cout << "Enter Resolution: "; cin >> resolution;
                hardware = make_shared<Monitor>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, size, resolution);
            
                ofstream MonitorFile("Monitor.csv", ios::app);
                MonitorFile << id << "," << name << "," << owner << "," << location << "," << brand << "," << model 
                << "," << buyDate << "," << warrantyExpiry << "," << cost << "," << size << "," << resolution << "\n";
                MonitorFile.close();
            }
            
            else if (hardwareType == 5) {  // Keyboard
                bool mechanical;
                cout << "Mechanical (1 for Yes, 0 for No): "; cin >> mechanical;
                hardware = make_shared<Keyboard>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, mechanical);
                
                ofstream LaptopFile("Keyboard.csv", ios::app);
                LaptopFile << id << "," << name << "," << owner << "," << location << "," << brand << "," << model 
                << "," << buyDate << "," << warrantyExpiry << "," << cost << "," << mechanical << "\n";
                LaptopFile.close();
            
            }
            
            else if (hardwareType == 6) {  // Mobile Phone
                string os;
                int storage;
                cout << "Enter OS: "; cin >> os;
                cout << "Enter Storage (GB): "; cin >> storage;
                hardware = make_shared<MobilePhone>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, os, storage);
            
                ofstream MobileFile("Mobile.csv", ios::app);
                MobileFile<< id << "," << name << "," << owner << "," << location << "," << brand << "," << model 
                << "," << buyDate << "," << warrantyExpiry << "," << cost << "," << os << "," << storage << "\n";
                MobileFile.close();
            
            }
            
            else if (hardwareType == 7) {  // Tablet
                string os;
                bool stylusSupport;
                cout << "Enter OS: "; cin >> os;
                cout << "Stylus Support (1 for Yes, 0 for No): "; cin >> stylusSupport;
                hardware = make_shared<Tablet>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, os, stylusSupport);
            
                ofstream TabletFile("Tablet.csv", ios::app);
                TabletFile << id << "," << name << "," << owner << "," << location << "," << brand << "," << model 
                << "," << buyDate << "," << warrantyExpiry << "," << cost << "," << os << "," << stylusSupport << "\n";
                TabletFile.close();
            
            }

            inventory->addAsset(hardware);
        }

        else if (choice == 2) {
            if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }

            ofstream SoftwareFile("Software.csv", ios::app);
            
            string id, name, owner, location, vendor, version, licenseType, expiryDate;
            bool autoRenewal;
            int licensesOwned, users;
            
            cout << "Enter Software ID: "; cin >> id;
            cin.ignore(); // Clear buffer
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
        
            shared_ptr<Software> software = make_shared<Software>(id, name, owner, location, vendor, version, licenseType, expiryDate, autoRenewal, licensesOwned, users);
            inventory->addAsset(software);

            
                SoftwareFile << id << "," << name << "," << owner << "," << location << "," << vendor<< "," << version 
                << "," << licenseType << "," << expiryDate << "," << autoRenewal << "," << licensesOwned << "," << users << "\n";
                SoftwareFile.close();
        }
        else if (choice == 3) {
            int inventoryChoice;
            cout << "1. Laptop\n";
            cout << "2. Mouse\n";
            cout << "3. Headphones\n";
            cout << "4. Monitor\n";
            cout << "5. Keyboard\n";
            cout << "6. Mobile\n";
            cout << "7. Tablet\n";
            cout << "8. Software\n";
            cout << "Enter choice: "; cin >> inventoryChoice;
            
            inventory->showInventory(inventoryChoice);
        }
        else if (choice == 4) {
          if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }
            int editChoice;
            string filename, searchKey;
            vector<string> headers;



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
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Processor", "RAM", "Storage", "Speed", "Display Type"};
            } 
                
            else if(editChoice == 2){
                filename = "Mouse.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "DPI", "Wireless ?", "Buttons"};

            } 

            else if(editChoice == 3){
                filename = "Headphone.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Wireless ?", "Noise Cancelling ?"};

            } 

            else if(editChoice == 4){
                filename = "Monitor.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Size", "Resolution"};

            } 

            else if(editChoice == 5){
                filename = "Keyboard.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Mechanical ?"};

            } 
            
            else if(editChoice == 6){
                filename = "Mobile.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Storage"};

            } 

            else if(editChoice == 7){
                filename = "Tablet.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Stylus Support ?"};

            } 

            else if(editChoice == 8){
                filename = "Software.csv";
                headers = {"ID", "Name", "Owner", "Location", "Vendor", "Version", "License Type", "Expiry Date", "Auto Renewal ?", "Licenses Owned", "Users"};

            } 

            else cout << "Invalid Choice";

            inventory->editAsset(filename, headers);
        } 
        else if (choice == 5) {
            if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }
            int searchChoice;
            string filename, searchKey;

            cout << "1. Laptop\n";
            cout << "2. Mouse\n";
            cout << "3. Headphones\n";
            cout << "4. Monitor\n";
            cout << "5. Keyboard\n";
            cout << "6. Mobile\n";
            cout << "7. Tablet\n";
            cout << "8. Software\n";
            cout << "Enter choice: "; cin >> searchChoice;
            
            if(searchChoice == 1) filename = "Laptop.csv";
            
                
            else if(searchChoice == 2) filename = "Mouse.csv";

            else if(searchChoice == 3) filename = "Headphone.csv";

            else if(searchChoice == 4) filename = "Monitor.csv";

            else if(searchChoice == 5) filename = "Keyboard.csv";
            
            else if(searchChoice == 6) filename = "Mobile.csv";

            else if(searchChoice == 7) filename = "Tablet.csv";

            else if(searchChoice == 8) filename = "Software.csv";

            else cout << "Invalid Choice";

            inventory->deleteAsset(filename);
        }
        else if (choice == 6) {

            int searchChoice;
            string filename, searchKey;
            vector<string> headers;



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
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Processor", "RAM", "Storage", "Speed", "Display Type"};
            } 
                
            else if(searchChoice == 2){
                filename = "Mouse.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "DPI", "RAM", "Wireless ?", "Buttons"};

            } 

            else if(searchChoice == 3){
                filename = "Headphone.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Wireless ?", "Noise Cancelling ?"};

            } 

            else if(searchChoice == 4){
                filename = "Monitor.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Size", "Resolution"};

            } 

            else if(searchChoice == 5){
                filename = "Keyboard.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "Mechanical ?"};

            } 
            
            else if(searchChoice == 6){
                filename = "Mobile.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Storage"};

            } 

            else if(searchChoice == 7){
                filename = "Tablet.csv";
                headers = {"ID", "Name", "Owner", "Location", "Brand", "Model", "Buy Date", "Warranty", "Cost", "OS", "Stylus Support ?"};

            } 

            else if(searchChoice == 8){
                filename = "Software.csv";
                headers = {"ID", "Name", "Owner", "Location", "Vendor", "Version", "License Type", "Expiry Date", "Auto Renewal ?", "Licenses Owned", "Users"};

            } 

            else cout << "Invalid Choice";

            cout << "Enter ID to search: "; cin >> searchKey;
            
            inventory->advancedSearch(filename, searchKey, headers);
        }
        else if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }
       
    }
    return 0;
}