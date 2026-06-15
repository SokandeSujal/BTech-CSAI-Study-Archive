#include <iostream>
#include <string>
using namespace std;

// Base class Person
class Person
{
protected:
    string name;
    int age;

public:
    Person()
    {
        name = "Unknown";
        age = 0;
    }

    Person(string n, int a)
    {
        name = n;
        age = a;
    }

    void displayPerson()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }

    // Virtual function for runtime polymorphism
    virtual void calculate_result()
    {
        cout << "Base class - No result calculation" << endl;
    }
};

// Derived class Student from Person
class Student : virtual public Person
{
protected:
    int roll_number;
    float subject1_marks;
    float subject2_marks;

public:
    Student()
    {
        roll_number = 0;
        subject1_marks = 0.0;
        subject2_marks = 0.0;
    }

    Student(string n, int a, int roll, float s1, float s2) : Person(n, a)
    {
        roll_number = roll;
        subject1_marks = s1;
        subject2_marks = s2;
    }

    void displayStudent()
    {
        cout << "Roll Number: " << roll_number << endl;
        cout << "Subject 1 Marks: " << subject1_marks << endl;
        cout << "Subject 2 Marks: " << subject2_marks << endl;
    }

    // Override calculate_result
    void calculate_result()
    {
        float average = (subject1_marks + subject2_marks) / 2.0;
        cout << "Academic Average: " << average << "%" << endl;
        if (average >= 40)
        {
            cout << "Academic Status: PASS" << endl;
        }
        else
        {
            cout << "Academic Status: FAIL" << endl;
        }
    }
};

// Derived class Sports from Person
class Sports : virtual public Person
{
protected:
    string sports_name;
    float sport1_score;
    float sport2_score;

public:
    Sports()
    {
        sports_name = "Unknown";
        sport1_score = 0.0;
        sport2_score = 0.0;
    }

    Sports(string n, int a, string sname, float sc1, float sc2) : Person(n, a)
    {
        sports_name = sname;
        sport1_score = sc1;
        sport2_score = sc2;
    }

    void displaySports()
    {
        cout << "Sports Name: " << sports_name << endl;
        cout << "Sport 1 Score: " << sport1_score << endl;
        cout << "Sport 2 Score: " << sport2_score << endl;
    }

    // Override calculate_result
    void calculate_result()
    {
        float average = (sport1_score + sport2_score) / 2.0;
        cout << "Sports Average Score: " << average << endl;
        if (average >= 50)
        {
            cout << "Sports Performance: EXCELLENT" << endl;
        }
        else if (average >= 30)
        {
            cout << "Sports Performance: GOOD" << endl;
        }
        else
        {
            cout << "Sports Performance: NEEDS IMPROVEMENT" << endl;
        }
    }
};

// Result class - Multiple inheritance from Student and Sports
class Result : public Student, public Sports
{
private:
    int grace_marks;

public:
    Result()
    {
        grace_marks = 0;
    }

    Result(string n, int a, int roll, float s1, float s2,
           string sname, float sc1, float sc2, int grace)
    {
        name = n;
        age = a;
        roll_number = roll;
        subject1_marks = s1;
        subject2_marks = s2;
        sports_name = sname;
        sport1_score = sc1;
        sport2_score = sc2;
        grace_marks = grace;
    }

    void displayResult()
    {
        cout << "\n========== FINAL RESULT ==========" << endl;
        displayPerson();
        displayStudent();
        displaySports();
        cout << "Grace Marks: " << grace_marks << endl;
    }

    // Override calculate_result
    void calculate_result()
    {
        float academic_avg = (subject1_marks + subject2_marks) / 2.0 + grace_marks;
        float sports_avg = (sport1_score + sport2_score) / 2.0;
        float final_result = (academic_avg + sports_avg) / 2.0;

        cout << "\n----- Final Result Calculation -----" << endl;
        cout << "Academic Average (with grace): " << academic_avg << "%" << endl;
        cout << "Sports Average: " << sports_avg << endl;
        cout << "Overall Performance: " << final_result << endl;

        if (final_result >= 50)
        {
            cout << "Final Grade: DISTINCTION" << endl;
        }
        else if (final_result >= 40)
        {
            cout << "Final Grade: FIRST CLASS" << endl;
        }
        else if (final_result >= 30)
        {
            cout << "Final Grade: PASS" << endl;
        }
        else
        {
            cout << "Final Grade: FAIL" << endl;
        }
        cout << "===================================\n"
             << endl;
    }
};

int main()
{
    cout << "===== Student Result Management System =====" << endl;

    // Create Result object
    Result r1("Rahul Sharma", 20, 101, 75.0, 82.0, "Cricket", 85.0, 90.0, 5);

    r1.displayResult();

    // Using base class pointer for runtime polymorphism
    cout << "\n----- Using Base Class Pointer (Runtime Polymorphism) -----" << endl;
    Person *person;

    person = &r1;
    cout << "\nCalling calculate_result() through Person pointer:" << endl;
    person->calculate_result();

    // Create another student with poor performance
    Result r2("Priya Patel", 19, 102, 35.0, 40.0, "Football", 45.0, 50.0, 3);
    r2.displayResult();

    person = &r2;
    cout << "\nCalling calculate_result() through Person pointer:" << endl;
    person->calculate_result();

    return 0;
}