#include <iostream>
using namespace std;

// Function Templates
template <typename T>
T functionToAddAnything(T n1, T n2)
{
    return n1 + n2;
}

template <class T>
class Calculator
{
    T n1, n2;

public:
    Calculator(T number1, T number2)
    {
        n1 = number1;
        n2 = number2;
    }

    T add()
    {
        return n1 + n2;
    }

    T sub()
    {
        return n1 - n2;
    }

    T mul()
    {
        return n1 * n2;
    }

    T div()
    {
        if (n2 != 0)
        {
            return n1 / n2;
        }
        else
        {
            return -1;
        }
    }
};

int main()
{
    cout << "============== Function Templates ==============\n";
    cout << "Add (INT): " << functionToAddAnything(5, 5) << endl;
    cout << "Add (float): " << functionToAddAnything(5.5, 5.78) << endl;
    cout << "Add (string): " << functionToAddAnything(string("Hello "), string("World!")) << endl;

    cout << "\n\n============== Class Templates ==============\n";
    cout << "\n======= INT Class Templates =======\n";
    Calculator<int> calInt(5, 10);

    cout << "Addition: " << calInt.add() << endl;
    cout << "Subtraction: " << calInt.sub() << endl;
    cout << "Multiplication: " << calInt.mul() << endl;
    cout << "Division: " << calInt.div() << endl;

    cout << "\n======= FLOAT Class Templates =======\n";
    Calculator<float> calFloat(34.8, 6.8);

    cout << "Addition: " << calFloat.add() << endl;
    cout << "Subtraction: " << calFloat.sub() << endl;
    cout << "Multiplication: " << calFloat.mul() << endl;
    cout << "Division: " << calFloat.div() << endl;

    return 0;
}