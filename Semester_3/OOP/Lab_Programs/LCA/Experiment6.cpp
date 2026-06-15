#include <iostream>
#include <string>

using namespace std;

class TrainJourney
{
    int pnr;
    string name;
    string id;
    int age;
    string gender;
    string phone;
    string doj;
    string dob;
    string source;
    string dest;
    float amount;
    int travellers;

public:
    void input()
    {
        cout << "Enter PNR: ";
        cin >> pnr;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "ID: ";
        getline(cin, id);
        cout << "Age: ";
        cin >> age;
        cin.ignore();
        cout << "Gender (M/F): ";
        getline(cin, gender);
        cout << "Phone No: ";
        getline(cin, phone);
        cout << "Date of Journey (DD-MM-YYYY): ";
        getline(cin, doj);
        cout << "Date of Booking (DD-MM-YYYY): ";
        getline(cin, dob);
        cout << "Source Station: ";
        getline(cin, source);
        cout << "Destination Station: ";
        getline(cin, dest);
        cout << "Ticket Amount: ";
        cin >> amount;
        cout << "Number of Travellers: ";
        cin >> travellers;
    }

    void checkAge()
    {
        if (age < 18 || age > 60)
            throw "Invalid Age! Must be 18-60.";
    }

    void checkPhone()
    {
        if (phone.length() != 10)
            throw "Invalid Phone Number! Must be 10 digits.";
    }

    void checkDate(string date)
    {
        if (date.length() != 10 || date[2] != '-' || date[5] != '-')
            throw "Invalid Date Format! Use DD-MM-YYYY.";
    }

    void checkTravellers()
    {
        if (travellers > 6)
            throw "Too many travellers! Max allowed is 6.";
    }

    void validate()
    {
        try
        {
            checkAge();
            checkPhone();
            checkDate(doj);
            checkDate(dob);
            checkTravellers();
        }
        catch (const char *msg)
        {
            cout << "Exception: " << msg << endl;
            throw;
        }
    }

    void printTicket()
    {
        cout << "\n--- TICKET DETAILS ---\n";
        cout << "PNR: " << pnr << "\nName: " << name << "\nID: " << id
             << "\nAge: " << age << "\nGender: " << gender
             << "\nPhone: " << phone << "\nDate of Journey: " << doj
             << "\nDate of Booking: " << dob << "\nFrom: " << source
             << "\nTo: " << dest << "\nAmount: " << amount
             << "\nTravellers: " << travellers << "\n-------------------\n";
    }
};

int main()
{

    TrainJourney t;
    t.input();

    try
    {
        t.validate();
        cout << "\nTicket booked successfully!\n";
        t.printTicket();
    }
    catch (const char *e)
    {
        cout << "Booking failed: " << e << endl;
    }

    return 0;
}