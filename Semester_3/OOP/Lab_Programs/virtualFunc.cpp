#include <iostream>
using namespace std;

class A1
{
public:
    virtual void useA()
    {
        cout << "useA() of A1 class" << endl;
    }
};

class B1 : public A1
{
    int y;

public:
    void useA()
    {
        cout << "useA() of B1 class" << endl;
    }
};

int main()
{
    A1 *a = new A1();
    a->useA();
    a = new B1();
    a->useA();

    return 0;
}