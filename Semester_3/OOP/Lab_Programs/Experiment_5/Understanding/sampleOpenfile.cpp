#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    // Writing to a file using constructors of ofstream class
    string name = "Sujal Sokande";
    ofstream out("samplefile.txt");
    out << name;

    // Reading from a file using constructors of ifstream class
    string str;
    ifstream readfromfile("samplefile2.txt");
    // in >> str;
    getline(readfromfile, str);

    cout << str << endl;

    return 0;
}