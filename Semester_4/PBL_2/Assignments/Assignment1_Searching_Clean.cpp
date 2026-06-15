#include <iostream>
#include <string>
using namespace std;

class MobileUser {
public:
    long mobileNo;
    string name;
    float billAmount;
    
    void input() {
        cout << "Enter Mobile Number: ";
        cin >> mobileNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Bill Amount: ";
        cin >> billAmount;
    }
    
    void display() {
        cout << mobileNo << " | " << name << " | Rs." << billAmount << endl;
    }
};

class SearchOperations {
private:
    MobileUser users[100];
    int n;
    
public:
    SearchOperations() {
        n = 0;
    }
    
    void acceptRecords() {
        cout << "Enter number of records: ";
        cin >> n;
        
        for(int i = 0; i < n; i++) {
            cout << "\nRecord " << (i+1) << ":\n";
            users[i].input();
        }
    }
    
    void displayRecords() {
        cout << "\nAll Records:\n";
        for(int i = 0; i < n; i++) {
            cout << (i+1) << ". ";
            users[i].display();
        }
    }
    
    int linearSearch(long key) {
        for(int i = 0; i < n; i++) {
            if(users[i].mobileNo == key) {
                return i;
            }
        }
        return -1;
    }
    
    int binarySearchIterative(long key) {
        sortByMobileNo();
        
        int low = 0;
        int high = n - 1;
        
        while(low <= high) {
            int mid = (low + high) / 2;
            
            if(users[mid].mobileNo == key) {
                return mid;
            }
            else if(key < users[mid].mobileNo) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return -1;
    }
    
    int binarySearchRecursive(long key) {
        sortByMobileNo();
        return binaryRecursive(0, n-1, key);
    }
    
private:
    int binaryRecursive(int low, int high, long key) {
        if(low > high) {
            return -1;
        }
        
        int mid = (low + high) / 2;
        
        if(users[mid].mobileNo == key) {
            return mid;
        }
        else if(key < users[mid].mobileNo) {
            return binaryRecursive(low, mid - 1, key);
        }
        else {
            return binaryRecursive(mid + 1, high, key);
        }
    }
    
    void sortByMobileNo() {
        for(int i = 0; i < n-1; i++) {
            for(int j = 0; j < n-i-1; j++) {
                if(users[j].mobileNo > users[j+1].mobileNo) {
                    MobileUser temp = users[j];
                    users[j] = users[j+1];
                    users[j+1] = temp;
                }
            }
        }
    }
};

int main() {
    SearchOperations db;
    int choice;
    long searchKey;
    int result;
    
    db.acceptRecords();
    
    do {
        cout << "\n1. Display Records\n";
        cout << "2. Linear Search\n";
        cout << "3. Binary Search (Iterative)\n";
        cout << "4. Binary Search (Recursive)\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                db.displayRecords();
                break;
                
            case 2:
                cout << "Enter Mobile Number: ";
                cin >> searchKey;
                result = db.linearSearch(searchKey);
                if(result != -1) {
                    cout << "Found at position " << (result+1) << endl;
                } else {
                    cout << "Not found\n";
                }
                break;
                
            case 3:
                cout << "Enter Mobile Number: ";
                cin >> searchKey;
                result = db.binarySearchIterative(searchKey);
                if(result != -1) {
                    cout << "Found at position " << (result+1) << endl;
                } else {
                    cout << "Not found\n";
                }
                break;
                
            case 4:
                cout << "Enter Mobile Number: ";
                cin >> searchKey;
                result = db.binarySearchRecursive(searchKey);
                if(result != -1) {
                    cout << "Found at position " << (result+1) << endl;
                } else {
                    cout << "Not found\n";
                }
                break;
                
            case 5:
                cout << "Exiting\n";
                break;
                
            default:
                cout << "Invalid choice\n";
        }
        
    } while(choice != 5);
    
    return 0;
}
