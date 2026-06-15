#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
    float a, b;

    cout << "Enter Number 1: ";
    cin >> a;
    cout << "Enter Number 2: ";
    cin >> b;

    try
    {
        if (b != 0)
        {
            cout << "Division: " << a / b << endl;
        }
        else
        {
            throw runtime_error("");
        }
    }
    catch (const exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}