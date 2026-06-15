#include <iostream>
using namespace std;

class Calculator
{
private:
    float num1;
    float num2;

public:
    Calculator()
    {
        num1 = 0;
        num2 = 0;
    }

    Calculator(float n1, float n2)
    {
        num1 = n1;
        num2 = n2;
    }

    friend Calculator operator+(Calculator c1, Calculator c2);
    friend Calculator operator-(Calculator c1, Calculator c2);
    friend Calculator operator*(Calculator c1, Calculator c2);
    friend Calculator operator/(Calculator c1, Calculator c2);

    friend Calculator operator++(Calculator &c1);
    friend istream &operator>>(istream &in, Calculator &c);

    void display()
    {
        cout << "Num1: " << num1 << " Num2: " << num2 << endl;
    }

    float getNum1()
    {
        return num1;
    }

    float getNum2()
    {
        return num2;
    }
};

Calculator operator+(Calculator c1, Calculator c2)
{
    Calculator temp;
    temp.num1 = c1.num1 + c2.num1;
    temp.num2 = c1.num2 + c2.num2;
    return temp;
}

Calculator operator-(Calculator c1, Calculator c2)
{
    Calculator temp;
    temp.num1 = c1.num1 - c2.num1;
    temp.num2 = c1.num2 - c2.num2;
    return temp;
}

Calculator operator*(Calculator c1, Calculator c2)
{
    Calculator temp;
    temp.num1 = c1.num1 * c2.num1;
    temp.num2 = c1.num2 * c2.num2;
    return temp;
}

Calculator operator/(Calculator c1, Calculator c2)
{
    Calculator temp;
    temp.num1 = c1.num1 / c2.num1;
    temp.num2 = c1.num2 / c2.num2;
    return temp;
}

Calculator operator++(Calculator &c)
{
    c.num1++;
    c.num2++;
    return c;
}

istream &operator>>(istream &in, Calculator &c)
{
    cout << "Enter two values: ";
    in >> c.num1 >> c.num2;
    return in;
}

int main()
{
    Calculator c1, c2, results;

    cout << "===== Mini Calculator using Operator Overloading =====" << endl;

    // Take input using overloaded >> operator
    cin >> c1;
    cin >> c2;

    cout << "\nValues entered:" << endl;
    cout << "First object -> ";
    c1.display();
    cout << "Second object -> ";
    c2.display();

    cout << "\n===== Performing Operations Using Overloaded Operators =====" << endl;

    // Addition
    results = c1 + c2;
    cout << "After operator+ : ";
    results.display();

    // Subtraction
    results = c1 - c2;
    cout << "After operator- : ";
    results.display();

    // Multiplication
    results = c1 * c2;
    cout << "After operator* : ";
    results.display();

    // Division
    results = c1 / c2;
    cout << "After operator/ : ";
    results.display();

    // Increment operator demonstration
    cout << "\n===== Increment Operator (++) =====" << endl;
    cout << "Before increment: ";
    c1.display();

    ++c1; // calls overloaded ++
    cout << "After increment (++): ";
    c1.display();

    cout << "\n===== End of Program =====" << endl;

    return 0;
}
