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
using std::sort;
using std::string;
using std::vector;

int namuDarbai = 5;
int studentuSkaicius = 0;
int pazymiuSkaicius = 0;

struct Studentas
{
    string vardas = "A", pavarde = "B";
    int *pazymiai = new int[0];
    int egzaminoBalas = 0;
    double galutinis = 0;
};

void output(const Studentas *studentai, bool arMediana)
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

    for (int i = 0; i < studentuSkaicius; i++)
    {
        cout << left << setw(20) << studentai[i].pavarde << left << setw(20) << studentai[i].vardas << left << setw(20) << fixed << setprecision(2) << studentai[i].galutinis << endl;
    }
}

double gautiVidurkiVidutini(int pazymiuSuma)
{
    return (pazymiuSuma * 1.0) / (namuDarbai * 1.0);
}

int gautiVidurkiMediana(int pazymiuSuma, const Studentas &studentas)
{
    if (namuDarbai % 2 != 0)
    {
        return studentas.pazymiai[namuDarbai / 2];
    }
    else
    {
        int number1 = studentas.pazymiai[(namuDarbai - 1) / 2];
        int number2 = studentas.pazymiai[namuDarbai / 2];
        return (number1 + number2) / 2.0;
    }
}

void pridetiStudenta(Studentas *&masyvas, Studentas &studentas)
{
    Studentas *naujasMasyvas = new Studentas[studentuSkaicius];

    for (int i = 0; i < studentuSkaicius - 1; i++)
    {
        naujasMasyvas[i] = masyvas[i];
    }
    naujasMasyvas[studentuSkaicius - 1] = studentas;

    delete[] masyvas;
    masyvas = naujasMasyvas;
}

void pridetiPazymi(int *&masyvas, int pazymys)
{
    int *naujasMasyvas = new int[pazymiuSkaicius];

    for (int i = 0; i < pazymiuSkaicius - 1; i++)
    {
        naujasMasyvas[i] = masyvas[i];
    }
    naujasMasyvas[pazymiuSkaicius - 1] = pazymys;

    delete[] masyvas;
    masyvas = naujasMasyvas;
}

int ranka(Studentas &studentas)
{
    cout << "Iveskite varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    studentuSkaicius += 1;
    int n, pazymys, semestroPazymiuSuma = 0;
    do
    {
        cout << "Iveskite semestro pazymiu skaiciu (max " << namuDarbai << "): ";
        cin >> n;
    } while (n > namuDarbai || n < 1);

    for (int i = 0; i < n; i++)
    {
        cout << "Iveskite " << i + 1 << " pazymi is " << n << ": ";
        cin >> pazymys;
        pridetiPazymi(studentas.pazymiai, pazymys);
        semestroPazymiuSuma += pazymys;
    }

    cout << "Iveskite egzamino pazymi: ";
    cin >> studentas.egzaminoBalas;

    return semestroPazymiuSuma;
}

int gautiPazymiuSuma(const Studentas &studentas)
{
    int suma = 0;
    for (int i = 0; i < namuDarbai; i++)
    {
        suma += studentas.pazymiai[i];
    }

    return suma;
}

bool suskaiciuotiGalutini(Studentas *&studentai)
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
            for (int i = 0; i < studentuSkaicius; i++)
            {
                semestroPazymiuSuma = gautiPazymiuSuma(studentai[i]);
                vidurkis = gautiVidurkiVidutini(semestroPazymiuSuma);
                studentai[i].galutinis = vidurkis * 0.4 + studentai[i].egzaminoBalas * 0.6;
            }
            return false;
        case 2:
            for (int i = 0; i < studentuSkaicius; i++)
            {
                std::sort(studentai, studentai + studentuSkaicius);
                semestroPazymiuSuma = gautiPazymiuSuma(studentai[i]);
                vidurkis = gautiVidurkiMediana(semestroPazymiuSuma, studentai[i]);
                studentai[i].galutinis = vidurkis * 0.4 + studentai[i].egzaminoBalas * 0.6;
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
    Studentas *studentai = new Studentas[studentuSkaicius];
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
            pridetiStudenta(studentai, studentas);
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

    for (int i = 0; i < studentuSkaicius; i++)
    {
        delete[] studentai[i].pazymiai;
    }
    delete[] studentai;
};