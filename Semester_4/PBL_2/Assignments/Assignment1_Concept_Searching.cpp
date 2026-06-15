#include <iostream>
using namespace std;

class SearchArray {
private:
    int arr[100];
    int n;
    
public:
    SearchArray() {
        n = 0;
    }
    
    void input() {
        cout << "Enter size: ";
        cin >> n;
        cout << "Enter elements:\n";
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }
    
    void display() {
        cout << "Array: ";
        for(int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    int linearSearch(int key) {
        for(int i = 0; i < n; i++) {
            if(arr[i] == key) {
                return i;
            }
        }
        return -1;
    }
    
    int binarySearchIterative(int key) {
        sort();
        
        int low = 0;
        int high = n - 1;
        
        while(low <= high) {
            int mid = (low + high) / 2;
            
            if(arr[mid] == key) {
                return mid;
            }
            else if(key < arr[mid]) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return -1;
    }
    
    int binarySearchRecursive(int key) {
        sort();
        return binRecursive(0, n-1, key);
    }
    
private:
    int binRecursive(int low, int high, int key) {
        if(low > high) {
            return -1;
        }
        
        int mid = (low + high) / 2;
        
        if(arr[mid] == key) {
            return mid;
        }
        else if(key < arr[mid]) {
            return binRecursive(low, mid - 1, key);
        }
        else {
            return binRecursive(mid + 1, high, key);
        }
    }
    
    void sort() {
        for(int i = 0; i < n-1; i++) {
            for(int j = 0; j < n-i-1; j++) {
                if(arr[j] > arr[j+1]) {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
};

int main() {
    SearchArray s;
    int choice, key, result;
    
    s.input();
    
    do {
        cout << "\n1. Display\n2. Linear Search\n3. Binary Search (Iterative)\n";
        cout << "4. Binary Search (Recursive)\n5. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                s.display();
                break;
            case 2:
                cout << "Enter key: ";
                cin >> key;
                result = s.linearSearch(key);
                if(result != -1)
                    cout << "Found at index " << result << endl;
                else
                    cout << "Not found\n";
                break;
            case 3:
                cout << "Enter key: ";
                cin >> key;
                result = s.binarySearchIterative(key);
                if(result != -1)
                    cout << "Found at index " << result << endl;
                else
                    cout << "Not found\n";
                break;
            case 4:
                cout << "Enter key: ";
                cin >> key;
                result = s.binarySearchRecursive(key);
                if(result != -1)
                    cout << "Found at index " << result << endl;
                else
                    cout << "Not found\n";
                break;
            case 5:
                break;
            default:
                cout << "Invalid\n";
        }
    } while(choice != 5);
    
    return 0;
}
