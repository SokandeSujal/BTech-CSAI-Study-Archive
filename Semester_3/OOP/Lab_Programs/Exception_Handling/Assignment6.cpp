#include <iostream>
#include <string>

using namespace std;

class TrainJourney
{
private:
    string PNR_no;
    string applicant_name;
    int age;
    string phone_no;
    string date_of_journey;
    string date_of_booking;
    string source_station;
    string destination_station;
    double ticket_amount;
    int num_travelers;

public:
    TrainJourney(string PNR, string name, int age, string phone, string travel_date, string booking_date, string source, string dest, double amount, int travelers)
    {
        PNR_no = PNR;
        applicant_name = name;
        this->age = age;
        phone_no = phone;
        date_of_journey = travel_date;
        date_of_booking = booking_date;
        source_station = source;
        destination_station = dest;
        ticket_amount = amount;
        num_travelers = travelers;
    }

    void checkAge()
    {
        if (age < 18 || age > 60)
        {
            throw string("Error: Age must be between 18 and 60 years.");
        }
    }

    void checkPhoneNo()
    {
        if (phone_no.length() != 10 || phone_no.find_first_not_of("0123456789") != string::npos)
        {
            throw string("Error: Phone number must be exactly 10 digits.");
        }
    }

    void checkDateFormat(const string &date)
    {
        if (date.length() != 10)
        {
            throw string("Error: Date must be exactly 10 characters long (DD-MM-YYYY).");
        }
        if (date[2] != '-' || date[5] != '-')
        {
            throw string("Error: Date format must be DD-MM-YYYY.");
        }
    }

    void checkTravellers()
    {
        if (num_travelers > 6)
        {
            throw string("Error: Number of travellers cannot exceed 6.");
        }
    }

    void printTicket()
    {
        cout << "Ticket booked successfully!" << endl;
        cout << "PNR Number: " << PNR_no << endl;
        cout << "Applicant Name: " << applicant_name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone Number: " << phone_no << endl;
        cout << "Date of Journey: " << date_of_journey << endl;
        cout << "Date of Booking: " << date_of_booking << endl;
        cout << "Source Station: " << source_station << endl;
        cout << "Destination Station: " << destination_station << endl;
        cout << "Ticket Amount: " << ticket_amount << endl;
        cout << "Number of Travelers: " << num_travelers << endl;
    }
};

int main()
{
    string PNR, name, phone, travel_date, booking_date, source, dest;
    int age, num_travelers;
    double amount;

    cout << "Enter PNR number: ";
    cin >> PNR;
    cout << "Enter applicant name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter phone number: ";
    cin >> phone;
    cout << "Enter date of journey (DD-MM-YYYY): ";
    cin >> travel_date;
    cout << "Enter date of booking (DD-MM-YYYY): ";
    cin >> booking_date;
    cout << "Enter source station: ";
    cin.ignore();
    getline(cin, source);
    cout << "Enter destination station: ";
    getline(cin, dest);
    cout << "Enter ticket amount: ";
    cin >> amount;
    cout << "Enter number of travelers: ";
    cin >> num_travelers;

    TrainJourney ticket(PNR, name, age, phone, travel_date, booking_date, source, dest, amount, num_travelers);

    try
    {
        ticket.checkAge();
        ticket.checkPhoneNo();
        ticket.checkDateFormat(travel_date);
        ticket.checkDateFormat(booking_date);
        ticket.checkTravellers();
        ticket.printTicket();
    }
    catch (const string &errorMsg)
    {
        cout << errorMsg << endl;
    }

    return 0;
}
