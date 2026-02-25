#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
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

int namuDarbai = 0;

struct Studentas
{
    string vardas = "A", pavarde = "B";
    int namuDarbai = 0;
    vector<int> pazymiai;
    int egzaminoBalas = 0;
    double galutinisVidurkis = 0;
    double galutinisMediana = 0;
};

void output(const vector<Studentas> &studentai, bool arMediana)
{
    if (arMediana)
    {
        cout << left << setw(20) << "Pavarde" << left << setw(20) << "Vardas" << left << setw(20) << "Galutinis (Med.)" << endl;
        cout << string(100, '-') << endl;
        for (const Studentas &studentas : studentai)
        {
            cout << left << setw(20) << studentas.pavarde << left << setw(20) << studentas.vardas
                 << left << setw(20) << fixed << setprecision(2) << studentas.galutinisMediana << endl;
        }
    }
    else
    {
        cout << left << setw(20) << "Pavarde" << left << setw(20) << "Vardas" << left << setw(20) << "Galutinis (Vid.)" << endl;
        cout << string(100, '-') << endl;
        for (const Studentas &studentas : studentai)
        {
            cout << left << setw(20) << studentas.pavarde << left << setw(20) << studentas.vardas
                 << left << setw(20) << fixed << setprecision(2) << studentas.galutinisVidurkis << endl;
        }
    }
}

void outputFailas(const vector<Studentas> &studentai)
{
    cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)"
         << left << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(100, '-') << endl;

    for (const Studentas &studentas : studentai)
    {
        cout << left << setw(20) << studentas.vardas << left << setw(20) << studentas.pavarde
             << left << setw(20) << fixed << setprecision(2) << studentas.galutinisVidurkis
             << left << setw(20) << fixed << setprecision(2) << studentas.galutinisMediana << endl;
    }
}

double gautiVidurkiVidutini(const Studentas &studentas, int pazymiuSuma)
{
    return (pazymiuSuma * 1.0) / (studentas.namuDarbai * 1.0);
}

int gautiVidurkiMediana(const Studentas &studentas, int pazymiuSuma)
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

void ranka(Studentas &studentas)
{
    cout << "Iveskite varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    int pazymys;
    do
    {
        cout << "Iveskite semestro pazymiu skaiciu: ";
        cin >> namuDarbai;
    } while (namuDarbai < 1);

    for (int i = 0; i < namuDarbai; i++)
    {
        do
        {
            cout << "Iveskite " << i + 1 << " pazymi is " << namuDarbai << ": ";
            cin >> pazymys;
        } while (pazymys < 1 || pazymys > 10);

        studentas.pazymiai.push_back(pazymys);
    }

    do
    {
        cout << "Iveskite egzamino pazymi: ";
        cin >> pazymys;
    } while (pazymys < 1 || pazymys > 10);

    studentas.egzaminoBalas = pazymys;
    studentas.namuDarbai = namuDarbai;
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
        cout << "Pasirinkite galutinio balo skaiciavimo buda (1 - vidurkis, 2 - mediana):\n";
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
            for (Studentas &studentas : studentai)
            {
                semestroPazymiuSuma = gautiPazymiuSuma(studentas);
                vidurkis = gautiVidurkiVidutini(studentas, semestroPazymiuSuma);
                studentas.galutinisVidurkis = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;
            }
            return false;
        case 2:
            for (Studentas &studentas : studentai)
            {
                sort(studentas.pazymiai.begin(), studentas.pazymiai.end());
                semestroPazymiuSuma = gautiPazymiuSuma(studentas);
                vidurkis = gautiVidurkiMediana(studentas, semestroPazymiuSuma);
                studentas.galutinisMediana = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;
            }
            return true;
        default:
            cout << "Neteisingas pasirinkimas!\n";
        }

    } while (input != 1 && input != 2);

    return false;
}

void suskaiciuotiGalutinius(vector<Studentas> &studentai)
{
    double vidurkis, mediana;
    int semestroPazymiuSuma;
    for (Studentas &studentas : studentai)
    {
        semestroPazymiuSuma = gautiPazymiuSuma(studentas);

        vidurkis = gautiVidurkiVidutini(studentas, semestroPazymiuSuma);
        studentas.galutinisVidurkis = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;

        sort(studentas.pazymiai.begin(), studentas.pazymiai.end());
        mediana = gautiVidurkiMediana(studentas, semestroPazymiuSuma);
        studentas.galutinisMediana = mediana * 0.4 + studentas.egzaminoBalas * 0.6;
    }
}

void generuotiStudenta(Studentas &studentas)
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
    for (int i = 0; i < namuDarbai; i++)
    {
        int randPazymys = rand() % 10 + 1;
        studentas.pazymiai.push_back(randPazymys);
    }

    int randBalas = rand() % 10 + 1;
    studentas.egzaminoBalas = randBalas;
}

void generuotiPazymius(Studentas &studentas)
{
    cout << "Iveskite varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    namuDarbai = 5;
    studentas.namuDarbai = namuDarbai;
    for (int i = 0; i < namuDarbai; i++)
    {
        int randPazymys = rand() % 10 + 1;
        studentas.pazymiai.push_back(randPazymys);
    }

    int randBalas = rand() % 10 + 1;
    studentas.egzaminoBalas = randBalas;
}

bool nuskaitytiFaila(vector<Studentas> &studentai)
{
    std::ifstream failas("kursiokai.txt");
    string antraste;

    std::getline(failas, antraste);

    namuDarbai = 5;
    string vardas, pavarde;
    while (failas >> vardas >> pavarde)
    {
        Studentas studentas;
        studentas.namuDarbai = namuDarbai;
        studentas.vardas = vardas;
        studentas.pavarde = pavarde;

        for (int i = 0; i < 5; i++)
        {
            int pazymys;
            failas >> pazymys;
            studentas.pazymiai.push_back(pazymys);
        }

        failas >> studentas.egzaminoBalas;

        studentai.push_back(studentas);
    }

    return true;
}

bool rusiuotiPagalVarda(Studentas &a, Studentas &b)
{
    return a.vardas < b.vardas;
}

bool rusiuotiPagalPavarde(Studentas &a, Studentas &b)
{
    return a.pavarde < b.pavarde;
}

bool rusiuotiPagalVidurki(Studentas &a, Studentas &b)
{
    return a.galutinisVidurkis < b.galutinisVidurkis;
}

bool rusiuotiPagalMediana(Studentas &a, Studentas &b)
{
    return a.galutinisMediana < b.galutinisMediana;
}

void surusiuotiPagalPasirinkima(vector<Studentas> &studentai)
{
    int input;
    do
    {
        cout << "Pasirinkite pagal ka surusiuoti (1 - vardas, 2 - pavarde, 3 - galutinis (vidurkis), 4 - galutinis (mediana):\n";
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
            sort(studentai.begin(), studentai.end(), rusiuotiPagalVarda);
            break;
        case 2:
            sort(studentai.begin(), studentai.end(), rusiuotiPagalPavarde);
            break;
        case 3:
            sort(studentai.begin(), studentai.end(), rusiuotiPagalVidurki);
            break;
        case 4:
            sort(studentai.begin(), studentai.end(), rusiuotiPagalMediana);
            break;
        default:
            cout << "Neteisingas pasirinkimas!\n";
            break;
        }
    } while (input != 1 && input != 2 && input != 3 && input != 4);
}

int main()
{
    Studentas studentas;
    vector<Studentas> studentai;
    bool isFailo;
    int input;
    namuDarbai = 0;

    do
    {
        cout << "Pasirinkite (1 - ranka, 2 - generuoti tik pažymius, 3 - generuoti studentų vardus, pavardės ir pažymius, 4 - nuskaityti failą, 5 - baigti darbą):\n";
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
            ranka(studentas);
            studentai.push_back(studentas);
            studentas = {};
            break;
        case 2:
            generuotiPazymius(studentas);
            studentai.push_back(studentas);
            studentas = {};
            break;
        case 3:
            generuotiStudenta(studentas);
            studentai.push_back(studentas);
            studentas = {};
            break;
        case 4:
            isFailo = nuskaitytiFaila(studentai);
            break;
        case 5:
            break;
        default:
            cout << "Neteisingas pasirinkimas!\n";
        }

    } while (input != 4 && input != 5);

    if (isFailo)
    {
        suskaiciuotiGalutinius(studentai);
        surusiuotiPagalPasirinkima(studentai);
        outputFailas(studentai);
    }
    else
    {
        bool arMediana = suskaiciuotiGalutini(studentai);
        output(studentai, arMediana);
    }
};