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

class SortOperations {
private:
    MobileUser users[100];
    int n;
    
public:
    SortOperations() {
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
        cout << "\nRecords:\n";
        for(int i = 0; i < n; i++) {
            cout << (i+1) << ". ";
            users[i].display();
        }
    }
    
    void quickSortDescending() {
        quickSort(0, n-1);
        cout << "\nSorted (Descending by MobileNo):\n";
        displayRecords();
    }
    
private:
    void quickSort(int p, int r) {
        if(p < r) {
            int q = partition(p, r);
            quickSort(p, q - 1);
            quickSort(q + 1, r);
        }
    }
    
    int partition(int p, int r) {
        long x = users[r].mobileNo;
        int i = p - 1;
        
        for(int j = p; j < r; j++) {
            if(users[j].mobileNo >= x) {
                i = i + 1;
                swap(users[i], users[j]);
            }
        }
        swap(users[i+1], users[r]);
        return i + 1;
    }
    
    void swap(MobileUser &a, MobileUser &b) {
        MobileUser temp = a;
        a = b;
        b = temp;
    }
    
public:
    void mergeSortAscending() {
        mergeSort(0, n-1);
        cout << "\nSorted (Ascending by BillAmount):\n";
        displayRecords();
    }
    
private:
    void mergeSort(int p, int r) {
        if(p < r) {
            int q = (p + r) / 2;
            mergeSort(p, q);
            mergeSort(q + 1, r);
            merge(p, q, r);
        }
    }
    
    void merge(int p, int q, int r) {
        int n1 = q - p + 1;
        int n2 = r - q;
        
        MobileUser L[50], R[50];
        
        for(int i = 0; i < n1; i++) {
            L[i] = users[p + i];
        }
        
        for(int j = 0; j < n2; j++) {
            R[j] = users[q + j + 1];
        }
        
        L[n1].billAmount = 999999;
        R[n2].billAmount = 999999;
        
        int i = 0, j = 0;
        
        for(int k = p; k <= r; k++) {
            if(L[i].billAmount <= R[j].billAmount) {
                users[k] = L[i];
                i = i + 1;
            }
            else {
                users[k] = R[j];
                j = j + 1;
            }
        }
    }
};

int main() {
    SortOperations db;
    int choice;
    
    db.acceptRecords();
    
    do {
        cout << "\n1. Display Records\n";
        cout << "2. Quick Sort (Descending by MobileNo)\n";
        cout << "3. Merge Sort (Ascending by BillAmount)\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                db.displayRecords();
                break;
                
            case 2:
                db.quickSortDescending();
                break;
                
            case 3:
                db.mergeSortAscending();
                break;
                
            case 4:
                cout << "Exiting\n";
                break;
                
            default:
                cout << "Invalid choice\n";
        }
        
    } while(choice != 4);
    
    return 0;
}
