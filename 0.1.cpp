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

int namuDarbai = 5;
int studentuSkaicius = 0;

struct Studentas
{
    string vardas = "A", pavarde = "B";
    vector<int> pazymiai;
    int egzaminoBalas = 0;
    double galutinis = 0;
};

void output(const vector<Studentas> &studentai, bool arMediana)
{
    if (arMediana)
    {
        cout << left << setw(20) << "Pavarde" << left << setw(20) << "Vardas" << left << setw(20) << "Galutinis (Med.)" << endl;
    }
    else
    {
        cout << left << setw(20) << "Pavarde" << left << setw(20) << "Vardas" << left << setw(20) << "Galutinis (Vid.)" << endl;
    }
    cout << string(100, '-') << endl;

    for (const Studentas &studentas : studentai)
    {
        cout << left << setw(20) << studentas.pavarde << left << setw(20) << studentas.vardas << left << setw(20) << fixed << setprecision(2) << studentas.galutinis << endl;
    }
}

double gautiVidurkiVidutini(int pazymiuSuma)
{
    return (pazymiuSuma * 1.0) / (namuDarbai * 1.0);
}

int gautiVidurkiMediana(int pazymiuSuma, const Studentas &studentas)
{
    int size = studentas.pazymiai.size();

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

int ranka(Studentas &studentas)
{
    int semestroPazymiuSuma = 0;
    cout << "Iveskite varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    int n, temp;
    do
    {
        cout << "Iveskite semestro pazymiu skaiciu (max " << namuDarbai << "): ";
        cin >> n;
    } while (n > namuDarbai || n < 1);

    for (int i = 0; i < n; i++)
    {
        cout << "Iveskite " << i + 1 << " pazymi is " << n << ": ";
        cin >> temp;
        studentas.pazymiai.push_back(temp);
        semestroPazymiuSuma += temp;
    }

    cout << "Iveskite egzamino pazymi: ";
    cin >> studentas.egzaminoBalas;

    return semestroPazymiuSuma;
}

int gautiPazymiuSuma(const Studentas &studentas)
{
    int suma = 0;
    for (int pazymys : studentas.pazymiai)
    {
        suma += pazymys;
    }

    return suma;
}

bool suskaiciuotiGalutini(vector<Studentas> &studentai)
{
    double vidurkis;
    int input, semestroPazymiuSuma;
    do
    {
        cout << "Pasirinkite galutinio balo skaiciavimo buda (1-vidurkis, 2-mediana):\n";
        cin >> input;

        switch (input)
        {
        case 1:
            for (Studentas &studentas : studentai)
            {
                semestroPazymiuSuma = gautiPazymiuSuma(studentas);
                vidurkis = gautiVidurkiVidutini(semestroPazymiuSuma);
                studentas.galutinis = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;
            }
            return false;
        case 2:
            for (Studentas &studentas : studentai)
            {
                sort(studentas.pazymiai.begin(), studentas.pazymiai.end());
                semestroPazymiuSuma = gautiPazymiuSuma(studentas);
                vidurkis = gautiVidurkiMediana(semestroPazymiuSuma, studentas);
                studentas.galutinis = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;
            }
            return true;
        default:
            cout << "Neteisingas pasirinkimas!";
        }

    } while (input != 1 && input != 2);

    return false;
}

int main()
{
    Studentas studentas;
    vector<Studentas> studentai;
    int semestroPazymiuSuma;
    int input;

    do
    {
        cout << "Pasirinkite (1 - ranka, 2 - generuoti tik pažymius, 3 - generuoti studentų vardus, pavardės ir pažymius, 4 - baigti darbą):\n";
        cin >> input;

        switch (input)
        {
        case 1:
            semestroPazymiuSuma = ranka(studentas);
            studentai.push_back(studentas);
            studentas = {};
            break;
        case 2:
            // semestroPazymiuSuma = generuotiPazymius(studentas);
            break;
        case 3:
            // semestroPazymiuSuma = generuotisStudenta(studentas);
            break;
        case 4:
            break;
        default:
            cout << "Neteisingas pasirinkimas!\n";
        }

    } while (input != 4);

    bool arMediana = suskaiciuotiGalutini(studentai);
    output(studentai, arMediana);
};