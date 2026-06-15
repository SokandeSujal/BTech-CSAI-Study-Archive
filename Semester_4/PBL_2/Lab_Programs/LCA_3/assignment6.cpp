#include <iostream>
using namespace std;

#define SIZE 10

// -------- Student Record --------
class Student
{
public:
    int roll;
    string name;
    float marks;

    Student()
    {
        roll = -1; // empty
    }
};

class Hash
{
    Student table[SIZE];

public:
    // -------- Hash Function --------
    int hashFunc(int key)
    {
        return key % SIZE;
    }

    // -------- Insert WITHOUT Replacement --------
    void insertWithoutReplacement(Student s)
    {
        int index = hashFunc(s.roll);

        int start = index;
        while (table[index].roll != -1)
        {
            index = (index + 1) % SIZE;

            if (index == start)
            {
                cout << "Table Full!\n";
                return;
            }
        }

        table[index] = s;
    }

    // -------- Insert WITH Replacement --------
    void insertWithReplacement(Student s)
    {
        int index = hashFunc(s.roll);

        if (table[index].roll == -1)
        {
            table[index] = s;
        }
        else
        {
            int existingHash = hashFunc(table[index].roll);

            if (existingHash != index)
            {
                // replace
                Student temp = table[index];
                table[index] = s;

                insertWithoutReplacement(temp);
            }
            else
            {
                insertWithoutReplacement(s);
            }
        }
    }

    // -------- Display --------
    void display()
    {
        cout << "\nIndex\tRoll\tName\tMarks\n";
        for (int i = 0; i < SIZE; i++)
        {
            if (table[i].roll != -1)
                cout << i << "\t" << table[i].roll << "\t" << table[i].name << "\t" << table[i].marks << endl;
            else
                cout << i << "\t---\n";
        }
    }

    // -------- Search --------
    int search(int roll)
    {
        int index = hashFunc(roll);
        int start = index;

        while (table[index].roll != -1)
        {
            if (table[index].roll == roll)
                return index;

            index = (index + 1) % SIZE;

            if (index == start)
                break;
        }
        return -1;
    }

    // -------- Modify --------
    void modify(int roll)
    {
        int index = search(roll);

        if (index == -1)
        {
            cout << "Record not found!\n";
            return;
        }

        cout << "Enter new name: ";
        cin >> table[index].name;
        cout << "Enter new marks: ";
        cin >> table[index].marks;

        cout << "Record updated!\n";
    }
};

// -------- Main --------
int main()
{
    Hash h;
    int choice, method;
    Student s;

    cout << "Choose Method:\n1.With Replacement\n2.Without Replacement\nEnter: ";
    cin >> method;

    do
    {
        cout << "\n1.Add\n2.Display\n3.Search\n4.Modify\n5.Exit\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Roll, Name, Marks: ";
            cin >> s.roll >> s.name >> s.marks;

            if (method == 1)
                h.insertWithReplacement(s);
            else
                h.insertWithoutReplacement(s);
            break;

        case 2:
            h.display();
            break;

        case 3:
        {
            int roll;
            cout << "Enter roll to search: ";
            cin >> roll;

            int index = h.search(roll);
            if (index != -1)
                cout << "Found at index: " << index << endl;
            else
                cout << "Not found\n";
            break;
        }

        case 4:
        {
            int roll;
            cout << "Enter roll to modify: ";
            cin >> roll;
            h.modify(roll);
            break;
        }
        }

    } while (choice != 5);

    return 0;
}