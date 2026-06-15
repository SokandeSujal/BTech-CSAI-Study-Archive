#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Book
{
private:
    int book_id;
    string title;
    string author;
    float price;
    int quantity;

public:
    Book()
    {
        book_id = 0;
        title = "Unknown";
        author = "Unknown";
        price = 0.0;
        quantity = 0;
    }

    Book(int bi, string t, string a, float p, int qua)
    {
        book_id = bi;
        title = t;
        author = a;
        price = p;
        quantity = qua;
    }

    int getBookId()
    {
        return book_id;
    }

    string getTitle()
    {
        return title;
    }

    void inputBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> book_id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;
    }

    void displayBook()
    {
        cout << "===== Books Deatils =====\n";
        cout << "Book ID: " << book_id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Price: " << price << endl;
        cout << "Quantity: " << quantity << endl;
        if (quantity < 0)
            cout << " [OUT OF STOCK]\n";
        cout << "========================" << endl;
    }

    void modifyBook()
    {
        cout << "\nModifying Book ID: " << book_id << endl;
        cout << "Current Title: " << title << endl;
        cout << "Enter New Title (or press enter to keep current): ";

        cin.ignore();
        string newTitle;
        getline(cin, newTitle);
        if (!newTitle.empty())
        {
            title = newTitle;
        }

        cout << "Current Price: $" << price << endl;
        cout << "Enter New Price (or 0 to keep current): ";
        float newPrice;
        cin >> newPrice;
        if (newPrice > 0)
        {
            price = newPrice;
        }

        cout << "Current Quantity: " << quantity << endl;
        cout << "Enter New Quantity (or -1 to keep current): ";
        int newQuantity;
        cin >> newQuantity;
        if (newQuantity >= 0)
        {
            quantity = newQuantity;
        }

        cout << "\nBook modified successfully!" << endl;
    }

    void writeToFile(ofstream &out)
    {
        out << book_id << endl;
        out << title << endl;
        out << author << endl;
        out << price << endl;
        out << quantity << endl;
    }

    void readFromFile(ifstream &in)
    {
        in >> book_id;
        in.ignore();
        getline(in, title);
        getline(in, author);
        in >> price;
        in >> quantity;
        in.ignore();
    }
};

void addBook()
{
    Book b;
    b.inputBook();

    ofstream out("Library.txt", ios::app);
    if (!out)
    {
        cout << "Error Reading the file!" << endl;
        return;
    }

    b.writeToFile(out);
    out.close();
    cout << "\nBook added successfully!\n";
}

void displayAllBooks()
{
    ifstream in("Library.txt");
    if (!in)
    {
        cout << "No books found! File doesn't exist." << endl;
        return;
    }

    Book b;
    cout << "\n===== LIBRARY BOOK LIST =====" << endl;
    bool found = false;

    while (in.peek() != EOF)
    {
        b.readFromFile(in);
        b.displayBook();
        found = true;
    }

    if (!found)
    {
        cout << "No books in the library!" << endl;
    }

    in.close();
}

void searchBookById()
{
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;

    ifstream in("Library.txt");
    if (!in)
    {
        cout << "No books found! File doesn't exist." << endl;
        return;
    }

    Book b;
    bool found = false;

    while (in.peek() != EOF)
    {
        b.readFromFile(in);
        if (b.getBookId() == id)
        {
            cout << "\nBook Found!" << endl;
            b.displayBook();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nBook with ID " << id << " not found!" << endl;
    }

    in.close();
}

void searchBookByTitle()
{
    string searchTitle;
    cout << "\nEnter Book Title to search: ";
    cin.ignore();
    getline(cin, searchTitle);

    ifstream in("Library.txt");
    if (!in)
    {
        cout << "No books found! File doesn't exist." << endl;
        return;
    }

    Book b;
    bool found = false;

    while (in.peek() != EOF)
    {
        b.readFromFile(in);
        if (b.getTitle() == searchTitle)
        {
            cout << "\nBook Found!" << endl;
            b.displayBook();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nBook with title '" << searchTitle << "' not found!" << endl;
    }

    in.close();
}

void deleteBook()
{
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    ifstream in("Library.txt");
    if (!in)
    {
        cout << "No books found! File doesn't exist." << endl;
        return;
    }

    ofstream temp("temp.txt");
    Book b;
    bool found = false;

    while (in.peek() != EOF)
    {
        b.readFromFile(in);
        if (b.getBookId() != id)
        {
            b.writeToFile(temp);
        }
        else
        {
            found = true;
            cout << "\nBook deleted successfully!" << endl;
        }
    }

    in.close();
    temp.close();

    remove("Library.txt");
    rename("temp.txt", "Library.txt");

    if (!found)
    {
        cout << "\nBook with ID " << id << " not found!" << endl;
    }
}

void modifyBookRecord()
{
    int id;
    cout << "\nEnter Book ID to modify: ";
    cin >> id;

    ifstream in("Library.txt");
    if (!in)
    {
        cout << "No books found! File doesn't exist." << endl;
        return;
    }

    ofstream temp("temp.txt");
    Book b;
    bool found = false;

    while (in.peek() != EOF)
    {
        b.readFromFile(in);
        if (b.getBookId() == id)
        {
            found = true;
            b.displayBook();
            b.modifyBook();
        }
        b.writeToFile(temp);
    }

    in.close();
    temp.close();

    remove("Library.txt");
    rename("temp.txt", "Library.txt");

    if (!found)
    {
        cout << "\nBook with ID " << id << " not found!" << endl;
    }
}

int main()
{
    int choice;

    cout << "===== LIBRARY MANAGEMENT SYSTEM =====" << endl;

    while (true)
    {
        cout << "\n----- MENU -----" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Search Book by ID" << endl;
        cout << "4. Search Book by Title" << endl;
        cout << "5. Modify Book Record" << endl;
        cout << "6. Delete Book Record" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            displayAllBooks();
            break;
        case 3:
            searchBookById();
            break;
        case 4:
            searchBookByTitle();
            break;
        case 5:
            modifyBookRecord();
            break;
        case 6:
            deleteBook();
            break;
        case 7:
            cout << "\nThank you for using Library Management System!" << endl;
            return 0;
        default:
            cout << "\nInvalid choice! Please try again." << endl;
        }
    }

    return 0;
}