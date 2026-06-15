#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    list<string> items;

    items.push_back("eggs");
    items.push_back("milk");
    items.push_back("sugar");
    items.push_back("chocolate");
    items.push_back("flour");

    cout << "Shopping list:\n";
    for (auto i : items)
        cout << i << " ";
    cout << "\n\n";

    items.pop_front();
    cout << "After removing first item:\n";
    for (auto i : items)
        cout << i << " ";
    cout << "\n\n";

    items.push_front("coffee");
    cout << "After adding coffee at start:\n";
    for (auto i : items)
        cout << i << " ";
    cout << "\n\n";

    auto it = find(items.begin(), items.end(), "sugar");
    if (it != items.end())
    {
        *it = "honey";
        cout << "Replaced 'sugar' with 'honey'.\n";
    }
    else
    {
        cout << "'sugar' not found.\n";
    }

    it = find(items.begin(), items.end(), "milk");
    if (it != items.end())
    {
        items.insert(it, "baking powder");
        cout << "Inserted 'baking powder' before 'milk'.\n";
    }

    cout << "\nUpdated list:\n";
    for (auto i : items)
        cout << i << " ";
    cout << "\n\n";

    items.sort();
    cout << "Sorted list:\n";
    for (auto i : items)
        cout << i << " ";
    cout << "\n\n";

    string name;
    cout << "Enter item to search: ";
    cin >> name;

    it = find(items.begin(), items.end(), name);
    if (it != items.end())
        cout << name << " found in list.\n";
    else
        cout << name << " not found.\n";

    return 0;
}
