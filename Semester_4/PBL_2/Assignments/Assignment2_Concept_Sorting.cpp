#include <iostream>
using namespace std;

class SortArray {
private:
    int arr[100];
    int n;
    
public:
    SortArray() {
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
    
    void quickSort() {
        qSort(0, n-1);
        cout << "Quick Sort completed\n";
        display();
    }
    
private:
    void qSort(int p, int r) {
        if(p < r) {
            int q = partition(p, r);
            qSort(p, q-1);
            qSort(q+1, r);
        }
    }
    
    int partition(int p, int r) {
        int x = arr[r];
        int i = p - 1;
        
        for(int j = p; j < r; j++) {
            if(arr[j] <= x) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
        int temp = arr[i+1];
        arr[i+1] = arr[r];
        arr[r] = temp;
        
        return i + 1;
    }
    
public:
    void mergeSort() {
        mSort(0, n-1);
        cout << "Merge Sort completed\n";
        display();
    }
    
private:
    void mSort(int p, int r) {
        if(p < r) {
            int q = (p + r) / 2;
            mSort(p, q);
            mSort(q+1, r);
            merge(p, q, r);
        }
    }
    
    void merge(int p, int q, int r) {
        int n1 = q - p + 1;
        int n2 = r - q;
        
        int L[50], R[50];
        
        for(int i = 0; i < n1; i++) {
            L[i] = arr[p + i];
        }
        
        for(int j = 0; j < n2; j++) {
            R[j] = arr[q + j + 1];
        }
        
        L[n1] = 999999;
        R[n2] = 999999;
        
        int i = 0, j = 0;
        
        for(int k = p; k <= r; k++) {
            if(L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
        }
    }
};

int main() {
    SortArray s;
    int choice;
    
    s.input();
    
    do {
        cout << "\n1. Display\n2. Quick Sort\n3. Merge Sort\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                s.display();
                break;
            case 2:
                s.quickSort();
                break;
            case 3:
                s.mergeSort();
                break;
            case 4:
                break;
            default:
                cout << "Invalid\n";
        }
    } while(choice != 4);
    
    return 0;
}
