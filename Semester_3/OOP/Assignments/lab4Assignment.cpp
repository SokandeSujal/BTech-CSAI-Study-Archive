#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    string name;
    int age;
    virtual void calculate_result()
    {
        cout << "No result to calculate." << endl;
    }
};

class Student : virtual public Person
{
public:
    int roll_number;
    int subject1_marks;
    int subject2_marks;
    void calculate_result() override
    {
        int total = subject1_marks + subject2_marks;
        cout << "Student total marks = " << total << endl;
    }
};

class Sports : virtual public Person
{
public:
    string sports_name;
    int sport1_score;
    int sport2_score;
    void calculate_result() override
    {
        int total = sport1_score + sport2_score;
        cout << "Sports total score = " << total << endl;
    }
};

class Result : public Student, public Sports
{
public:
    int grace_marks;
    void calculate_result() override
    {
        int academic_total = subject1_marks + subject2_marks;
        int sports_total = sport1_score + sport2_score;
        int final_score = academic_total + sports_total + grace_marks;
        cout << "Final score for " << name << " = " << final_score << endl;
    }
};

int main()
{

    return 0;
}
