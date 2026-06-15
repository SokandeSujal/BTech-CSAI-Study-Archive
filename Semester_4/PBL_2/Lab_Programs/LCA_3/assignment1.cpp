#include <iostream>
using namespace std;

class MobileUser
{
public:
    long long mobileNo;
    string name;
    float billAmount;
};

int linearSearch(MobileUser arr[], int n, long long key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i].mobileNo == key)
        {
            return i;
        }
    }
    return -1;
}

int binarySearchInterative(MobileUser arr[], int n, long long key)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2; 

        if (arr[mid].mobileNo == key)
        {
            return mid;
        }
        else if (arr[mid].mobileNo < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int binarySearchRecursive(MobileUser arr[], int low, int high, long long key)
{
    if (low > high)
    {
        return -1;
    }

    int mid = (low + high) / 2;

    if (arr[mid].mobileNo == key)
    {
        return mid;
    }
    else if (arr[mid].mobileNo < key)
    {
        return binarySearchRecursive(arr, mid + 1, high, key);
    }
    else
    {
        return binarySearchRecursive(arr, low, mid - 1, key);
    }
}

void sortUsers(MobileUser arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].mobileNo > arr[j + 1].mobileNo)
            {
                MobileUser temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void displayUser(MobileUser u)
{
    cout << "\nMobile No: " << u.mobileNo << endl;
    cout << "Name: " << u.name << endl;
    cout << "Bill Amount: " << u.billAmount << endl;
}

int main()
{
    int n;
    cout << "Enter Number of users: ";
    cin >> n;

    MobileUser arr[100];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter Details of the user " << i + 1 << endl;
        cout << "Mobile No: ";
        cin >> arr[i].mobileNo;
        cout << "Name: ";
        cin >> arr[i].name;
        cout << "Bill Amount: ";
        cin >> arr[i].billAmount;
    }

    sortUsers(arr, n);

    long long key;
    cout << "Enter Mobile number to search: ";
    cin >> key;

    cout << "\n\n------Iterative Search------\n\n";
    int index = linearSearch(arr, n, key);
    if (index != -1)
    {
        displayUser(arr[index]);
    }
    else
    {
        cout << "\nUser not found!\n";
    }

    cout << "\n\n------Binary Search Recursive------\n\n";
    index = binarySearchRecursive(arr, 0, n - 1, key);
    if (index != -1)
    {
        displayUser(arr[index]);
    }
    else
    {
        cout << "\nUser not found!\n";
    }

    cout << "\n\n------Binary Search Iterative------\n\n";
    index = binarySearchInterative(arr, n, key);
    if (index != -1)
    {
        displayUser(arr[index]);
    }
    else
    {
        cout << "\nUser not found!\n";
    }

    return 0;
}