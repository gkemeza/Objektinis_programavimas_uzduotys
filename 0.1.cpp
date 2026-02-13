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

void output(vector<Studentas> studentai)
{
    cout << left << setw(20) << "Pavarde" << left << setw(20) << "Vardas" << left << setw(20) << "Galutinis (Vid.)" << endl;
    cout << string(100, '-') << endl;

    for (auto studentas : studentai)
    {
        cout << left << setw(20) << studentas.pavarde << left << setw(20) << studentas.vardas << left << setw(20) << studentas.rezultatas << endl;
    }
}

// Vidurki/mediana dalinti is tiek pat pazymiu, visiem studentams.

int main()
{
    Studentas studentas;
    vector<Studentas> studentai;

    for (int ii = 0; ii < 2; ii++)
    {
        int sum = 0;
        cout << "Iveskite varda ir pavarde: ";
        cin >> studentas.vardas >> studentas.pavarde;

        cout << "Iveskite semestro pazymiu skaiciu ";
        int n, temp;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Iveskite " << i + 1 << " pazymi is " << n << ": ";
            cin >> temp;
            studentas.pazymiai.push_back(temp);
            sum += temp;
        }

        cout << "Iveskite egzamino paz: ";
        cin >> studentas.egzaminoBalas;

        studentas.rezultatas = sum * 1.0 / (studentas.pazymiai.size() * 1.0) * 0.4 + studentas.egzaminoBalas * 0.6;
        studentai.push_back(studentas);
        studentas.pazymiai.clear();
    }

    output(studentai);
};
