// Constructor and Destructor implementations

#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
private:
    int acc_id;
    string acc_type;
    string acc_name;
    string cust_address;
    string cust_contactno;
    double balance;
    static int total_accounts;
    static int saving_accounts;
    static int current_accounts;

public:
    BankAccount()
    {
        acc_id = 0;
        acc_type = "Unknown";
        acc_name = "Not Set";
        cust_address = "Not Set";
        cust_contactno = "Not Set";
        balance = 0.0;

        cout << "Default Constructor called. Account created with default values." << endl;
    }

    BankAccount(int id, string acc_type, string acc_name, string cust_address, string cust_contactno, double balance)
    {
        this->acc_id = id;
        this->acc_type = acc_type;
        this->acc_name = acc_name;
        this->cust_address = cust_address;
        this->cust_contactno = cust_contactno;
        this->balance = balance;

        total_accounts++;
        if (acc_type == "Saving")
            saving_accounts++;
        else if (acc_type == "Current")
            current_accounts++;

        cout << "Parameterized Constructor called. Account created with ID: " << acc_id << endl;
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposited: " << amount << ". New Balance: " << balance << endl;
        }
        else
        {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Withdrew: " << amount << ". New Balance: " << balance << endl;
        }
        else
        {
            cout << "Invalid withdrawal amount." << endl;
        }
    }

    double getBalance() const
    {
        return balance;
    }

    void displayAccountDetails()
    {
        cout << "Account ID: " << acc_id << endl;
        cout << "Account Type: " << acc_type << endl;
        cout << "Account Name: " << acc_name << endl;
        cout << "Customer Address: " << cust_address << endl;
        cout << "Customer Contact No: " << cust_contactno << endl;
        cout << "Balance: " << balance << endl;
    }

    static void displayAccountCounts()
    {
        cout << "Total Accounts: " << total_accounts << endl;
        cout << "Saving Accounts: " << saving_accounts << endl;
        cout << "Current Accounts: " << current_accounts << endl;
    }

    ~BankAccount()
    {
        cout << "Destroying Account ID: " << acc_id << endl;
    }
};

int BankAccount::total_accounts = 0;
int BankAccount::saving_accounts = 0;
int BankAccount::current_accounts = 0;

int main()
{
    BankAccount acc1;

    BankAccount acc2(101, "Saving", "Sujal Sokande", "Kothrud, Pune", "9876543210", 0.0);
    BankAccount acc3(102, "Current", "Anjali Patil", "Baner, Pune", "9123456780", 5000.0);

    acc2.deposit(1500.0);
    acc2.withdraw(500.0);

    acc3.deposit(2000.0);
    acc3.withdraw(8000.0);

    acc2.displayAccountDetails();
    acc3.displayAccountDetails();

    BankAccount::displayAccountCounts();

    return 0;
}
