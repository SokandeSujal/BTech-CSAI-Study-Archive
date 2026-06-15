// Testing array out of bounds exception handling in C++

#include <iostream>
using namespace std;
int main()
{

    int arr[] = {1, 2, 3, 4, 5};
    cout << "Accessing arr[3]: " << arr[3] << endl;

    int index = 0;

    cout << "Enter Array Element Index to Access: ";
    cin >> index;

    cout << "Accessing arr[" << index << "]: " << arr[index] << endl;

    try
    {
        if (index < 0 || index >= 5)
        {
            throw out_of_range("Index out of bounds");
        }
        cout << "Element at index " << index << " is " << arr[index] << endl;
    }
    catch (const out_of_range &e)
    {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}