#include <iostream>
using namespace std;

class Employee
{
private:
    string Ename;
    int EmpID;

public:
    Employee()
    {
        Ename = "DEFAULT";
        EmpID = 0;
    }

    Employee(string name, int id)
    {
        Ename = name;
        EmpID = id;
    }

    void display()
    {
        cout << "Employee Deatils:\n";
        cout << "Name: " << Ename << " || ID: " << EmpID << endl;
    }

    virtual void earnings() {};
};

class SalariedEmployee : public Employee
{
private:
    double weeklysalary;

public:
    SalariedEmployee()
    {
        weeklysalary = 0;
    }

    SalariedEmployee(string name, int id, double salary) : Employee(name, id)
    {
        weeklysalary = salary;
    }

    void earnings()
    {
        cout << "Weekly Salary: " << weeklysalary << endl;
    }

    void displayDetails()
    {
        cout << "\n----- Salaried Employee -----" << endl;
        display();
        earnings();
        cout << "-----------------------------\n"
             << endl;
    }
};

class HourlyEmployee : public Employee
{
private:
    double wage;
    double hours;
    double Hourlysalary;

public:
    HourlyEmployee()
    {
        wage = 0.0;
        hours = 0.0;
        Hourlysalary = 0.0;
    }

    HourlyEmployee(string name, int id, double w, double h) : Employee(name, id)
    {
        wage = w;
        hours = h;
        Hourlysalary = 0.0;
    }

    void earnings()
    {
        if (hours < 40)
        {
            Hourlysalary = hours * wage;
        }
        else
        {
            Hourlysalary = 40 * wage + ((hours - 40) * wage) * 1.5;
        }
        cout << "Hourly Wage: $" << wage << " per hour" << endl;
        cout << "Hours Worked: " << hours << " hours" << endl;
        cout << "Total Salary: $" << Hourlysalary << endl;
    }

    void displayDetails()
    {
        cout << "\n----- Hourly Employee -----" << endl;
        display();
        earnings();
        cout << "---------------------------\n"
             << endl;
    }
};

class CommissionEmployee : public Employee
{
private:
    double grossSales;
    double commissionRate;
    double Commissionsalary;

public:
    // Default constructor
    CommissionEmployee() : Employee()
    {
        grossSales = 0.0;
        commissionRate = 0.0;
        Commissionsalary = 0.0;
    }

    CommissionEmployee(string name, int id, double sales, double rate) : Employee(name, id)
    {
        grossSales = sales;
        commissionRate = rate;
        Commissionsalary = 0.0;
    }
    void earnings()
    {
        Commissionsalary = grossSales * commissionRate;
        cout << "Gross Sales: $" << grossSales << endl;
        cout << "Commission Rate: " << (commissionRate * 100) << "%" << endl;
        cout << "Commission Salary: $" << Commissionsalary << endl;
    }

    void displayDetails()
    {
        cout << "\n----- Commission Employee -----" << endl;
        display();
        earnings();
        cout << "-------------------------------\n"
             << endl;
    }
};

int main()
{
    cout << "===== Employee Management System =====" << endl;
    SalariedEmployee emp1("John Smith", 101, 2000.0);
    emp1.displayDetails();

    // Create Hourly Employee with less than 40 hours
    HourlyEmployee emp2("Alice Johnson", 102, 25.0, 35.0);
    emp2.displayDetails();

    // Create Hourly Employee with more than 40 hours (overtime)
    HourlyEmployee emp3("Bob Williams", 103, 20.0, 50.0);
    emp3.displayDetails();

    // Create Commission Employee
    CommissionEmployee emp4("Carol Davis", 104, 50000.0, 0.10);
    emp4.displayDetails();
    return 0;
}