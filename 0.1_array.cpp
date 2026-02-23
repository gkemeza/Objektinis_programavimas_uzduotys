#include <iostream>
#include <iomanip>
#include <string>
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

int namuDarbai = 0;
int studentuSkaicius = 0;

struct Studentas
{
    string vardas = "A", pavarde = "B";
    int namuDarbai = 0;
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

double gautiVidurkiVidutini(Studentas &studentas, int pazymiuSuma)
{
    return (pazymiuSuma * 1.0) / (studentas.namuDarbai * 1.0);
}

int gautiVidurkiMediana(int pazymiuSuma, const Studentas &studentas)
{
    if (studentas.namuDarbai % 2 != 0)
    {
        return studentas.pazymiai[studentas.namuDarbai / 2];
    }
    else
    {
        int number1 = studentas.pazymiai[(studentas.namuDarbai - 1) / 2];
        int number2 = studentas.pazymiai[studentas.namuDarbai / 2];
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

void pridetiPazymi(Studentas &studentas, int pazymioNr, int pazymys)
{
    int *naujasMasyvas = new int[pazymioNr];

    for (int i = 0; i < pazymioNr - 1; i++)
    {
        naujasMasyvas[i] = studentas.pazymiai[i];
    }
    naujasMasyvas[pazymioNr - 1] = pazymys;

    delete[] studentas.pazymiai;
    studentas.pazymiai = naujasMasyvas;
}

int ranka(Studentas &studentas)
{
    cout << "Iveskite varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    studentuSkaicius++;
    namuDarbai = 0;
    int pazymys, semestroPazymiuSuma = 0;
    do
    {
        cout << "Iveskite semestro pazymiu skaiciu: ";
        cin >> namuDarbai;
    } while (namuDarbai < 1);

    for (int i = 0; i < namuDarbai; i++)
    {
        int pazymioNr = i + 1;
        cout << "Iveskite " << pazymioNr << " pazymi is " << namuDarbai << ": ";
        cin >> pazymys;

        pridetiPazymi(studentas, pazymioNr, pazymys);
        semestroPazymiuSuma += pazymys;
    }

    cout << "Iveskite egzamino pazymi: ";
    cin >> studentas.egzaminoBalas;

    studentas.namuDarbai = namuDarbai;
    return semestroPazymiuSuma;
}

int gautiPazymiuSuma(const Studentas &studentas)
{
    int suma = 0;
    for (int i = 0; i < studentas.namuDarbai; i++)
    {
        suma += studentas.pazymiai[i];
    }

    return suma;
}

bool suskaiciuotiGalutini(Studentas *studentai)
{
    double vidurkis;
    int input, semestroPazymiuSuma;
    do
    {
        cout << "Pasirinkite galutinio balo skaiciavimo buda (1-vidurkis, 2-mediana):\n";
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Neteisingas pasirinkimas!\n";
            input = 0;
            continue;
        }

        switch (input)
        {
        case 1:
            for (int i = 0; i < studentuSkaicius; i++)
            {
                semestroPazymiuSuma = gautiPazymiuSuma(studentai[i]);
                vidurkis = gautiVidurkiVidutini(studentai[i], semestroPazymiuSuma);
                studentai[i].galutinis = vidurkis * 0.4 + studentai[i].egzaminoBalas * 0.6;
            }
            return false;
        case 2:
            for (int i = 0; i < studentuSkaicius; i++)
            {
                sort(studentai[i].pazymiai, studentai[i].pazymiai + studentai[i].namuDarbai);
                semestroPazymiuSuma = gautiPazymiuSuma(studentai[i]);
                vidurkis = gautiVidurkiMediana(semestroPazymiuSuma, studentai[i]);
                studentai[i].galutinis = vidurkis * 0.4 + studentai[i].egzaminoBalas * 0.6;
            }
            return true;
        default:
            cout << "Neteisingas pasirinkimas!\n";
        }

    } while (input != 1 && input != 2);

    return false;
}

int generuotiStudenta(Studentas &studentas)
{
    switch (rand() % 10)
    {
    case 0:
        studentas.vardas = "Irma";
        break;
    case 1:
        studentas.vardas = "Alma";
        break;
    case 2:
        studentas.vardas = "Irena";
        break;
    case 3:
        studentas.vardas = "Egle";
        break;
    case 4:
        studentas.vardas = "Jolanta";
        break;
    case 5:
        studentas.vardas = "Petras";
        break;
    case 6:
        studentas.vardas = "Jonas";
        break;
    case 7:
        studentas.vardas = "Ignas";
        break;
    case 8:
        studentas.vardas = "Darius";
        break;
    case 9:
        studentas.vardas = "Simas";
        break;
    }
    switch (*studentas.vardas.rbegin())
    {
    case 's':
        switch (rand() % 5)
        {
        case 0:
            studentas.pavarde = "Pavardenis1";
            break;
        case 1:
            studentas.pavarde = "Pavardenis2";
            break;
        case 2:
            studentas.pavarde = "Pavardenis3";
            break;
        case 3:
            studentas.pavarde = "Pavardenis4";
            break;
        case 4:
            studentas.pavarde = "Pavardenis5";
            break;
        }
        break;
    default:
        switch (rand() % 5)
        {
        case 0:
            studentas.pavarde = "Pavardaite1";
            break;
        case 1:
            studentas.pavarde = "Pavardaite2";
            break;
        case 2:
            studentas.pavarde = "Pavardaite3";
            break;
        case 3:
            studentas.pavarde = "Pavardaite4";
            break;
        case 4:
            studentas.pavarde = "Pavardaite5";
            break;
        }
        break;
    };

    namuDarbai = 5;
    studentas.namuDarbai = namuDarbai;
    studentuSkaicius++;
    int semestroPazymiuSuma = 0;
    for (int i = 0; i < namuDarbai; i++)
    {
        int randPazymys = rand() % 10 + 1;
        studentas.pazymiai[i] = randPazymys;
        semestroPazymiuSuma += randPazymys;
    }

    int randBalas = rand() % 10 + 1;
    studentas.egzaminoBalas = randBalas;

    return semestroPazymiuSuma;
}

int generuotiPazymius(Studentas &studentas)
{
    cout << "Iveskite varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    studentuSkaicius++;
    namuDarbai = 5;
    studentas.namuDarbai = namuDarbai;
    int semestroPazymiuSuma = 0;
    for (int i = 0; i < namuDarbai; i++)
    {
        int randPazymys = rand() % 10 + 1;
        studentas.pazymiai[i] = randPazymys;
        semestroPazymiuSuma += randPazymys;
    }

    int randBalas = rand() % 10 + 1;
    studentas.egzaminoBalas = randBalas;

    return semestroPazymiuSuma;
}

int main()
{
    Studentas studentas;
    Studentas *studentai = new Studentas[0];
    int semestroPazymiuSuma;
    int input;
    namuDarbai = 0;

    do
    {
        cout << "Pasirinkite (1 - ranka, 2 - generuoti tik pažymius, 3 - generuoti studentų vardus, pavardės ir pažymius, 4 - baigti darbą):\n";
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Neteisingas pasirinkimas!\n";
            input = 0;
            continue;
        }

        switch (input)
        {
        case 1:
            semestroPazymiuSuma = ranka(studentas);
            pridetiStudenta(studentai, studentas);
            studentas = {};
            break;
        case 2:
            semestroPazymiuSuma = generuotiPazymius(studentas);
            pridetiStudenta(studentai, studentas);
            studentas = {};
            break;
        case 3:
            semestroPazymiuSuma = generuotiStudenta(studentas);
            pridetiStudenta(studentai, studentas);
            studentas = {};
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