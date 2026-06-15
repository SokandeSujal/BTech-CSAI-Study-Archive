#include <iostream>
using namespace std;

template <class T>
class StudentPerformance
{
    T data[100];
    int size;
    int count;

public:
    StudentPerformance()
    {
        size = 100;
        count = 0;
    }

    StudentPerformance(int s)
    {
        size = s;
        count = 0;
    }

    void addPerformance(T p)
    {
        if (count < size)
        {
            data[count] = p;
            count++;
        }
        else
        {
            cout << "Array is full." << endl;
        }
    }

    void displayPerformance()
    {
        cout << "Performance values: ";
        for (int i = 0; i < count; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    T getMinPerformance()
    {
        T min = data[0];
        for (int i = 1; i < count; i++)
        {
            if (data[i] < min)
            {
                min = data[i];
            }
        }
        return min;
    }

    T getMaxPerformance()
    {
        T max = data[0];
        for (int i = 1; i < count; i++)
        {
            if (data[i] > max)
            {
                max = data[i];
            }
        }
        return max;
    }

    double getAveragePerformance()
    {
        double sum = 0;
        for (int i = 0; i < count; i++)
        {
            sum = sum + data[i];
        }
        if (count == 0)
        {
            return 0;
        }
        else
        {
            return sum / count;
        }
    }

    bool searchPerformance(T p)
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i] == p)
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    StudentPerformance<float> s1(5);

    s1.addPerformance(80.5);
    s1.addPerformance(90.2);
    s1.addPerformance(75.4);
    s1.addPerformance(88.8);

    s1.displayPerformance();
    cout << "Minimum: " << s1.getMinPerformance() << endl;
    cout << "Maximum: " << s1.getMaxPerformance() << endl;
    cout << "Average: " << s1.getAveragePerformance() << endl;
    if (s1.searchPerformance(90.2))
    {
        cout << "Search 90.2: Found" << endl;
    }
    else
    {
        cout << "Search 90.2: Not Found" << endl;
    }

    if (s1.searchPerformance(91.2))
    {
        cout << "Search 91.2: Found" << endl;
    }
    else
    {
        cout << "Search 91.2: Not Found" << endl;
    }

    cout << endl;

    StudentPerformance<char> s2(3);

    s2.addPerformance('A');
    s2.addPerformance('B');
    s2.addPerformance('C');

    s2.displayPerformance();
    cout << "Minimum: " << s2.getMinPerformance() << endl;
    cout << "Maximum: " << s2.getMaxPerformance() << endl;
    if (s2.searchPerformance('B'))
    {
        cout << "Search B: Found" << endl;
    }
    else
    {
        cout << "Search B: Not Found" << endl;
    }

    if (s2.searchPerformance('D'))
    {
        cout << "Search D: Found" << endl;
    }
    else
    {
        cout << "Search D: Not Found" << endl;
    }

    return 0;
}
