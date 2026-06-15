#include <iostream>
using namespace std;

class Complex
{
private:
    int real;
    int imaginary;

public:
    Complex()
    {
        real = 0;
        imaginary = 0;
    }

    Complex(int r, int i)
    {
        real = r;
        imaginary = i;
    }

    void display()
    {
        cout << "Complex Number: " << real << " + " << imaginary << "i" << endl;
    }

    friend Complex operator+(Complex c1, Complex c2);
};

Complex operator+(Complex c1, Complex c2)
{
    Complex result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}

int main()
{
    Complex c1(5, 10);
    Complex c2(5, 6);

    Complex results;

    results = c1 + c2;

    c1.display();
    c2.display();
    results.display();

    return 0;
}