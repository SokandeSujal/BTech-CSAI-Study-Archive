// Vector Understanding in C++

#include <iostream>
#include <vector>
using namespace std;

int main()
{

    vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);
    cout << "Vector elements: ";
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;

    cout << "First element: " << vec.front() << endl;
    cout << "Last element: " << vec.back() << endl;
    cout << "Vector size: " << vec.size() << endl;

    vec.pop_back();
    cout << "After pop_back, vector elements: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;

    vec.emplace_back(60);
    cout << "Vector elements using iterators: ";
    for (auto it : vec)
    {
        cout << it << " ";
    }

    return 0;
}