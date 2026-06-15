#include <iostream>
using namespace std;

template <class T1, class T2>
class sample
{
    T1 a;
    T2 b;

public:
    void getData()
    {
        cout << "Enter value for a: ";
        cin >> a;
        cout << "Enter value for b: ";
        cin >> b;
    }

    void displayData()
    {
        cout << "Value of a: " << a << endl;
        cout << "Value of b: " << b << endl
             << endl;
    }
};

int main()
{
    sample<int, int> ob1;
    sample<int, char> ob2;
    sample<int, float> ob3;

    cout << "For object ob1 (int, int):" << endl;
    ob1.getData();
    ob1.displayData();
    cout << "For object ob2 (int, char):" << endl;
    ob2.getData();
    ob2.displayData();
    cout << "For object ob3 (int, float):" << endl;
    ob3.getData();
    ob3.displayData();

    return 0;
}