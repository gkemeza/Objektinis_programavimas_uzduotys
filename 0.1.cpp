#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::string;
using std::vector;

struct Studentas
{
    string vardas = "A", pavarde = "B";
    vector<int> pazymiai;
    int egzaminoBalas;
    double rezultatas;
};

int main()
{
    Studentas studentas;
    vector<Studentas> studentai;
};
