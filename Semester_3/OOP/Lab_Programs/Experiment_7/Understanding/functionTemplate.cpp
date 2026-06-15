#include <iostream>
using namespace std;

template <class T>
void max1(T x, T y)
{
    if (x > y)
    {
        cout << x << " is greater than " << y << endl;
    }
    else
    {
        cout << y << " is greater than " << x << endl;
    }
}

int main()
{

    max1(3, 7);
    max1(33.65, 67.32);
    max1('A', 'B');
    max1("AB", "BA");

    return 0;
}