#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book
{
    int id;
    string title;
    string author;
    float price;
    int qty;

public:
    Book()
    {
        id = 0;
        title = "";
        author = "";
        price = 0;
        qty = 0;
    }

    void add()
    {
        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> qty;
    }

    void show()
    {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nPrice: " << price;
        cout << "\nQuantity: " << qty;
        if (qty == 0)
            cout << "\nStatus: Out of Stock";
        cout << endl;
    }

    void edit()
    {
        cout << "\nEnter new price: ";
        cin >> price;
        cout << "Enter new quantity: ";
        cin >> qty;
        cout << "Book updated.\n";
    }

    int getID()
    {
        return id;
    }

    void write(ofstream &f)
    {
        f << id << " " << title << " " << author << " " << price << " " << qty << endl;
    }

    void read(ifstream &f)
    {
        f >> id >> title >> author >> price >> qty;
    }
};

void addBook()
{
    ofstream f("books.txt", ios::app);
    if (!f)
    {
        cout << "File error!\n";
        return;
    }
    Book b;
    b.add();
    b.write(f);
    f.close();
    cout << "Book added.\n";
}

void showAll()
{
    ifstream f("books.txt");
    if (!f)
    {
        cout << "No file found!\n";
        return;
    }
    Book b;
    cout << "\n--- All Books ---\n";
    while (f.peek() != EOF)
    {
        b.read(f);
        if (f.eof())
            break;
        b.show();
    }
    f.close();
}

void searchBook()
{
    ifstream f("books.txt");
    if (!f)
    {
        cout << "No file found!\n";
        return;
    }
    int id;
    bool found = false;
    cout << "Enter book ID: ";
    cin >> id;
    Book b;
    while (f.peek() != EOF)
    {
        b.read(f);
        if (f.eof())
            break;
        if (b.getID() == id)
        {
            cout << "\nBook Found:\n";
            b.show();
            found = true;
            break;
        }
    }
    f.close();
    if (!found)
        cout << "Book not found.\n";
}

void editBook()
{
    ifstream fin("books.txt");
    ofstream fout("temp.txt");
    if (!fin || !fout)
    {
        cout << "File error!\n";
        return;
    }

    int id;
    bool found = false;
    cout << "Enter book ID to edit: ";
    cin >> id;

    Book b;
    while (fin.peek() != EOF)
    {
        b.read(fin);
        if (fin.eof())
            break;
        if (b.getID() == id)
        {
            b.edit();
            found = true;
        }
        b.write(fout);
    }

    fin.close();
    fout.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book updated.\n";
    else
        cout << "Book not found.\n";
}

void deleteBook()
{
    ifstream fin("books.txt");
    ofstream fout("temp.txt");
    if (!fin || !fout)
    {
        cout << "File error!\n";
        return;
    }

    int id;
    bool found = false;
    cout << "Enter book ID to delete: ";
    cin >> id;

    Book b;
    while (fin.peek() != EOF)
    {
        b.read(fin);
        if (fin.eof())
            break;
        if (b.getID() != id)
            b.write(fout);
        else
            found = true;
    }

    fin.close();
    fout.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book deleted.\n";
    else
        cout << "Book not found.\n";
}

int main()
{
    int ch;
    do
    {
        cout << "\n=== LIBRARY MENU ===";
        cout << "\n1. Add Book";
        cout << "\n2. Show All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Edit Book";
        cout << "\n5. Delete Book";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            addBook();
            break;
        case 2:
            showAll();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            editBook();
            break;
        case 5:
            deleteBook();
            break;
        case 6:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Wrong choice!\n";
        }
    } while (ch != 6);

    return 0;
}