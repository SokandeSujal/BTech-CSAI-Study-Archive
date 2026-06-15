#include <iostream>
using namespace std;

int comparisons = 0;
int passes = 0;

class MobileUser
{
public:
    long long mobileNo;
    string name;
    int billAmount;
};

void swap(MobileUser &a, MobileUser &b)
{
    MobileUser temp = a;
    a = b;
    b = temp;
}

int partition(MobileUser arr[], int p, int q)
{
    long long x = arr[p].mobileNo;
    int i = p;

    passes++;

    for (int j = i + 1; j <= q; j++)
    {
        comparisons++;
        if (arr[j].mobileNo >= x)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i], arr[p]);
    return i;
}

int quickSort(MobileUser arr[], int p, int q)
{
    if (p < q)
    {
        int m = partition(arr, p, q);
        partition(arr, p, m - 1);
        partition(arr, m + 1, q);
    }
    
}

void display(MobileUser arr[], int n)
{
    cout << "\nSorted Data (Descending):\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nMobile No: " << arr[i].mobileNo;
        cout << "\nName: " << arr[i].name;
        cout << "\nBill: " << arr[i].billAmount << endl;
    }
}

int main()
{

    int n;
    cout << "Enter number of users: ";
    cin >> n;

    MobileUser A[100];

    // Input
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter details of user " << i + 1 << endl;
        cout << "Mobile No: ";
        cin >> A[i].mobileNo;
        cout << "Name: ";
        cin >> A[i].name;
        cout << "Bill Amount: ";
        cin >> A[i].billAmount;
    }

    // Quick Sort
    quickSort(A, 0, n - 1);

    // Output
    display(A, n);

    // Performance
    cout << "\nNumber of passes: " << passes;
    cout << "\nNumber of comparisons: " << comparisons;

    return 0;
}