#include "functions.h"

void isvestis(const vector<Studentas> &studentai, bool arMediana)
{
    cout << left << fixed << setprecision(2);
    if (arMediana)
    {
        cout << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Med.)" << endl;
        cout << string(100, '-') << endl;
        for (const Studentas &studentas : studentai)
        {
            cout << setw(20) << studentas.pavarde
                 << setw(20) << studentas.vardas
                 << setw(20) << studentas.galutinisMediana << endl;
        }
    }
    else
    {
        cout << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << endl;
        cout << string(100, '-') << endl;
        for (const Studentas &studentas : studentai)
        {
            cout << setw(20) << studentas.pavarde
                 << setw(20) << studentas.vardas
                 << setw(20) << studentas.galutinisVidurkis << endl;
        }
    }
}

void isvestisKonsole(const vector<Studentas> &studentai)
{
    cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)"
         << left << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(100, '-') << endl;

    cout << left << fixed << setprecision(2);
    for (const Studentas &studentas : studentai)
    {
        cout << setw(20) << studentas.vardas
             << setw(20) << studentas.pavarde
             << setw(20) << studentas.galutinisVidurkis
             << setw(20) << studentas.galutinisMediana << endl;
    }
}

void isvestisFailas(const vector<Studentas> &studentai)
{
    ofstream failas("isvestis.txt");

    failas
        << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)"
        << left << setw(20) << "Galutinis (Med.)" << endl;
    failas << string(100, '-') << endl;

    failas << left << fixed << setprecision(2);
    for (const Studentas &studentas : studentai)
    {
        failas << setw(20) << studentas.vardas
               << setw(20) << studentas.pavarde
               << setw(20) << studentas.galutinisVidurkis
               << setw(20) << studentas.galutinisMediana << endl;
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

void ivestisRanka(Studentas &studentas)
{
    try
    {
        cout << "Iveskite varda ir pavarde: ";
        cin >> studentas.vardas >> studentas.pavarde;

        int pazymys, namuDarbai;
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
    catch (const runtime_error &ex)
    {
        cerr << ex.what() << endl;
    }
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
    try
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
    catch (const runtime_error &ex)
    {
        cerr << ex.what() << endl;
    }
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

int randomInt(int min, int max)
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}

void generuotiStudenta(Studentas &studentas)
{
    switch (randomInt(0, 9))
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
        switch (randomInt(0, 4))
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
        switch (randomInt(0, 4))
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

    int namuDarbai = 5;
    studentas.namuDarbai = namuDarbai;
    for (int i = 0; i < namuDarbai; i++)
    {
        int randPazymys = randomInt(1, 10);
        studentas.pazymiai.push_back(randPazymys);
    }

    int randBalas = randomInt(1, 10);
    studentas.egzaminoBalas = randBalas;
}

void generuotiPazymius(Studentas &studentas)
{
    cout << "Iveskite varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    int namuDarbai = 5;
    studentas.namuDarbai = namuDarbai;
    for (int i = 0; i < namuDarbai; i++)
    {
        int randPazymys = randomInt(1, 10);
        studentas.pazymiai.push_back(randPazymys);
    }

    int randBalas = randomInt(1, 10);
    studentas.egzaminoBalas = randBalas;
}

bool nuskaitytiFaila(vector<Studentas> &studentai, const string &failoPavadinimas)
{
    try
    {
        ifstream failas(failoPavadinimas);
        string antraste;

        getline(failas, antraste);
        istringstream ss(antraste);

        string zodis;
        int zodziuSkaicius = 0;
        while (ss >> zodis)
        {
            zodziuSkaicius++;
        }

        int namuDarbai = zodziuSkaicius - 3;

        Studentas studentas;
        string vardas, pavarde;
        while (failas >> vardas >> pavarde)
        {
            studentas.pazymiai.clear();
            studentas.namuDarbai = namuDarbai;
            studentas.vardas = vardas;
            studentas.pavarde = pavarde;

            for (int i = 0; i < namuDarbai; i++)
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
    catch (const runtime_error &ex)
    {
        cerr << "Klaida: " << ex.what() << endl;
    }
}

bool rusiuotiPagalVarda(const Studentas &a, const Studentas &b)
{
    return a.vardas < b.vardas;
}

bool rusiuotiPagalPavarde(const Studentas &a, const Studentas &b)
{
    return a.pavarde < b.pavarde;
}

bool rusiuotiPagalVidurki(const Studentas &a, const Studentas &b)
{
    return a.galutinisVidurkis < b.galutinisVidurkis;
}

bool rusiuotiPagalMediana(const Studentas &a, const Studentas &b)
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