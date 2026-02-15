#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::right;
using std::setprecision;
using std::setw;
using std::string;
using std::vector;

int maxPazymiai = 5;

struct Studentas
{
    string vardas = "A", pavarde = "B";
    vector<int> pazymiai;
    int egzaminoBalas;
    double galutinis;
};

void output(vector<Studentas> studentai)
{
    cout << left << setw(20) << "Pavarde" << left << setw(20) << "Vardas" << left << setw(20) << "Galutinis (.)" << endl;
    cout << string(100, '-') << endl;

    for (auto studentas : studentai)
    {
        cout << left << setw(20) << studentas.pavarde << left << setw(20) << studentas.vardas << left << setw(20) << fixed << setprecision(2) << studentas.galutinis << endl;
    }
}

double gautiVidurkiVidutini(int pazymiuSuma)
{
    return (pazymiuSuma * 1.0) / (maxPazymiai * 1.0);
}

int gautiVidurkiMediana(int pazymiuSuma, const Studentas &studentas, int size)
{
    if (size % 2 != 0)
    {
        return studentas.pazymiai[size / 2];
    }
    else
    {
        int number1 = studentas.pazymiai[(size - 1) / 2];
        int number2 = studentas.pazymiai[size / 2];
        return (number1 + number2) / 2.0;
    }
}

int main()
{
    Studentas studentas;
    vector<Studentas> studentai;

    for (int i = 0; i < 2; i++)
    {
        int semestroPazymiuSuma = 0;
        cout << "Iveskite varda ir pavarde: ";
        cin >> studentas.vardas >> studentas.pavarde;

        int n, temp;
        do
        {
            cout << "Iveskite semestro pazymiu skaiciu (max " << maxPazymiai << "):";
            cin >> n;
        } while (n > maxPazymiai || n < 1);

        for (int i = 0; i < n; i++)
        {
            cout << "Iveskite " << i + 1 << " pazymi is " << n << ": ";
            cin >> temp;
            studentas.pazymiai.push_back(temp);
            semestroPazymiuSuma += temp;
        }

        cout << "Iveskite egzamino pazymi: ";
        cin >> studentas.egzaminoBalas;

        sort(studentas.pazymiai.begin(), studentas.pazymiai.end());

        // int size = studentas.pazymiai.size();
        // double vidurkis = gautiVidurkiMediana(semestroPazymiuSuma, studentas, size);
        double vidurkis = gautiVidurkiVidutini(semestroPazymiuSuma);

        studentas.galutinis = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;

        studentai.push_back(studentas);
        studentas.pazymiai.clear();
    }

    output(studentai);
};