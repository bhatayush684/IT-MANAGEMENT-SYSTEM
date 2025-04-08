#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include <iomanip>  // Required for std::get_time
#include <sstream>  // Required for std::istringstream

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
    
        // 🛠️ FIX: Add missing getter functions
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
    
        // 🛠️ FIX: Add missing getter function for brand
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
        // Preloaded sample assets
        addAsset(make_shared<Laptop>("LAP001", "Dell XPS 15", "Tanisha", "Office", 1500, "Dell", "XPS 15", "2023-01-10", "2025-05-01", "Intel i7",16, 512, 3.5, "LED"));
        addAsset(make_shared<Software>("SW001", "Microsoft Office", "IT Dept", "Server Room", "Microsoft", "2021", "Subscription", "2025-03-31", true, 10, 20));
        addAsset(make_shared<Laptop>("LAP002", "Dell Experion", "Ayush", "Office", 1500, "Dell", "16", "2023-01-12", "2025-01-05", "Intel i9", 16, 512, 3.5, "LD"));
        addAsset(make_shared<Software>("SW002", "windows", "IT Dept", "Server Room", "Microsoft", "2021", "Subscription", "2025-05-30", true, 10, 20));
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

    void showInventory() {
            cout << "========== INVENTORY ==========" << endl;
            if (assets.empty()) {
                cout << "No assets in inventory." << endl;
                return;
            }
            for (auto &it : assets) {
                it.second->displayInfo();
            }
        }
    
        void editAsset(string assetID, string newName) {
            if (assets.find(assetID) != assets.end()) {
                assets[assetID]->setName(newName);
                cout << "Asset " << assetID << " updated successfully!" << endl;
            } else {
                cout << "Asset ID not found!" << endl;
            }
        }
    
        void deleteAsset(string assetID) {
            if (assets.erase(assetID)) {
                cout << "Asset " << assetID << " deleted successfully!" << endl;
            } else {
                cout << "Asset ID not found!" << endl;
            }
        }
    
        class Hardware : public Asset {
            protected:
                double cost;
                string brand, model, buyDate, warrantyExpiry;
            public:
                Hardware(string id, string n, string o, string loc, double c, string b, string m, string bd, string we)
                    : Asset(id, n, o, loc), cost(c), brand(b), model(m), buyDate(bd), warrantyExpiry(we) {}
            
                virtual void displayInfo() override = 0;
            
                string getWarrantyExpiry() { return warrantyExpiry; }
            
                // 🛠️ FIX: Add missing getter function for brand
                string getBrand() { return brand; }
            };
            
            void advancedSearch() {
                string searchType;
                cout << "\nSearch by: [name, owner, location, type, brand, status]: ";
                cin >> searchType;
                cin.ignore();
                
                string query;
                cout << "Enter search query: ";
                getline(cin, query);
                
                bool found = false;
                cout << "\n=== Search Results ===\n";
                for (const auto& it : assets) {
                    shared_ptr<Asset> asset = it.second;
                    shared_ptr<Hardware> hardware = dynamic_pointer_cast<Hardware>(asset);
                    shared_ptr<Software> software = dynamic_pointer_cast<Software>(asset);
                    
                    if (searchType == "name" && asset->getAssetID() == query) found = true;
                    else if (searchType == "owner" && asset->getOwner() == query) found = true;
                    else if (searchType == "location" && asset->getLocation() == query) found = true;
                    else if (searchType == "status" && asset->getStatus() == query) found = true;
                    else if (searchType == "brand" && hardware && hardware->getBrand() == query) found = true;
                    else if (searchType == "type") {
                        if ((query == "Laptop" && dynamic_pointer_cast<Laptop>(asset)) ||
                            (query == "Mouse" && dynamic_pointer_cast<Mouse>(asset)) ||
                            (query == "Headphones" && dynamic_pointer_cast<Headphones>(asset)) ||
                            (query == "Monitor" && dynamic_pointer_cast<Monitor>(asset)) ||
                            (query == "Keyboard" && dynamic_pointer_cast<Keyboard>(asset)) ||
                            (query == "Phones" && dynamic_pointer_cast<MobilePhone>(asset)) ||
                            (query == "Tablets" && dynamic_pointer_cast<Tablet>(asset)) ||
                            (query == "Software" && software)) {
                            found = true;
                        }
                    }
                    
                    if (found) {
                        asset->displayInfo();
                        found = false;
                    }
                     
                }
               if (!found) cout << "No matching assets found.\n";
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
                };
        
                if (!found) {
                    cout << " No upcoming expirations.\n";
                }
            }
        };
InventoryManager* InventoryManager::instance = nullptr;

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
            }
            else if (hardwareType == 2) {  // Mouse
                int dpi, buttons;
                bool wireless;
                cout << "Enter DPI: "; cin >> dpi;
                cout << "Wireless (1 for Yes, 0 for No): "; cin >> wireless;
                cout << "Enter Number of Buttons: "; cin >> buttons;
                hardware = make_shared<Mouse>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, dpi, wireless, buttons);
            }
            else if (hardwareType == 3) {  // Headphones
                bool wireless, noiseCancelling;
                int batteryLife;
                cout << "Wireless (1 for Yes, 0 for No): "; cin >> wireless;
                cout << "Noise Cancelling (1 for Yes, 0 for No): "; cin >> noiseCancelling;
                cout << "Enter Battery Life (hours): "; cin >> batteryLife;
                hardware = make_shared<Headphones>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, wireless, noiseCancelling, batteryLife);
            } 
            if (hardwareType == 4) {  // Monitor
                int size;
                string resolution;
                cout << "Enter Size (in inches): "; cin >> size;
                cout << "Enter Resolution: "; cin >> resolution;
                hardware = make_shared<Monitor>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, size, resolution);
            } else if (hardwareType == 5) {  // Keyboard
                bool mechanical;
                cout << "Mechanical (1 for Yes, 0 for No): "; cin >> mechanical;
                hardware = make_shared<Keyboard>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, mechanical);
            } else if (hardwareType == 6) {  // Mobile Phone
                string os;
                int storage;
                cout << "Enter OS: "; cin >> os;
                cout << "Enter Storage (GB): "; cin >> storage;
                hardware = make_shared<MobilePhone>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, os, storage);
            } else if (hardwareType == 7) {  // Tablet
                string os;
                bool stylusSupport;
                cout << "Enter OS: "; cin >> os;
                cout << "Stylus Support (1 for Yes, 0 for No): "; cin >> stylusSupport;
                hardware = make_shared<Tablet>(id, name, owner, location, cost, brand, model, buyDate, warrantyExpiry, os, stylusSupport);
            }

            inventory->addAsset(hardware);
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
        }
        else if (choice == 3) {
            inventory->showInventory();
        }
        else if (choice == 4) {
          if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }
            string assetID, newName;
            cout << "Enter Asset ID to edit: "; cin >> assetID;
            cin.ignore();
            cout << "Enter new name: "; getline(cin, newName);
            inventory->editAsset(assetID, newName);
        } 
        else if (choice == 5) {
          if (currentRole != "Admin") {
                cout << "Access Denied! Admins only.\n";
                continue;
            }
            string assetID;
            cout << "Enter Asset ID to delete: "; cin >> assetID;
            inventory->deleteAsset(assetID);
        }
        else if (choice == 6) {
            inventory->advancedSearch();
        }
        else if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }
       
    }
    return 0;
}
