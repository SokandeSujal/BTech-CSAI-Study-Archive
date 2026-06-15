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

    // Unary minus operator overloading
    Complex operator-()
    {
        Complex temp;
        temp.real = -real;
        temp.imaginary = -imaginary;
        return temp;
    }
};

int main()
{
    Complex c1(5, 10);
    Complex c2;

    c1.display();

    // Apply unary minus
    c2 = -c1;
    c2.display();

    return 0;
}
