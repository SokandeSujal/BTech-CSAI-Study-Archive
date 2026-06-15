#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // ofstream out;
    // out.open("samplefile.txt");
    // out << "This is store in a file";
    // out.close();

    ifstream in;
    in.open("samplefile2.txt");
    string str;

    while (in.eof() == 0)
    {
        getline(in, str);
        cout << str << endl;
    }

    in.close();

    return 0;
}