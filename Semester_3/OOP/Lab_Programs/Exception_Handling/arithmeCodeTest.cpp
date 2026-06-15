#include <iostream>
using namespace std;
int main()
{
    int opr1, opr2;
    float result;

    cout << "Enter two integers: ";
    cin >> opr1 >> opr2;

    try
    {
        if (opr2 == 0)
        {
            throw(opr2);
        }
        result = (float)opr1 / opr2;
        cout << "Result: " << result << endl;
    }
    catch (int i)
    {
        cout << "Caught an integer exception: " << i << endl;
    }

    // without try catch block
    cout << "Any number divided by zero is infinity: " << 10 / 0 << endl;
    return 0;
}