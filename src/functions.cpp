#include "../include/functions.h"
#include "../include/timer.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::istringstream;
using std::left;
using std::mt19937;
using std::ofstream;
using std::random_device;
using std::right;
using std::runtime_error;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
using std::to_string;
using std::uniform_int_distribution;
using std::vector;
using std::filesystem::exists;

void isvestis(const vector<Studentas> &studentai, bool arMediana)
{
    cout << left << fixed << setprecision(2);
    if (arMediana)
    {
        cout << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Med.)" << "\n";
        cout << string(100, '-') << "\n";
        for (const Studentas &studentas : studentai)
        {
            cout << setw(20) << studentas.pavarde
                 << setw(20) << studentas.vardas
                 << setw(20) << studentas.galutinisMediana << "\n";
        }
    }
    else
    {
        cout << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << "\n";
        cout << string(100, '-') << "\n";
        for (const Studentas &studentas : studentai)
        {
            cout << setw(20) << studentas.pavarde
                 << setw(20) << studentas.vardas
                 << setw(20) << studentas.galutinisVidurkis << "\n";
        }
    }
}

void isvestisKonsole(const vector<Studentas> &studentai)
{
    cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)"
         << left << setw(20) << "Galutinis (Med.)" << "\n";
    cout << string(100, '-') << "\n";

    cout << left << fixed << setprecision(2);
    for (const Studentas &studentas : studentai)
    {
        cout << setw(20) << studentas.vardas
             << setw(20) << studentas.pavarde
             << setw(20) << studentas.galutinisVidurkis
             << setw(20) << studentas.galutinisMediana << "\n";
    }
}

void isvestisFailas(const vector<Studentas> &studentai, string failoPavadinimas)
{
    try
    {
        ofstream failas("../outputData/" + failoPavadinimas);

        if (!failas.is_open())
            throw runtime_error("Klaida: nepavyko atidaryti failo irasymui.");

        failas
            << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)"
            << left << setw(20) << "Galutinis (Med.)" << "\n";
        failas << string(100, '-') << "\n";

        failas << left << fixed << setprecision(2);
        for (const Studentas &studentas : studentai)
        {
            failas << setw(20) << studentas.vardas
                   << setw(20) << studentas.pavarde
                   << setw(20) << studentas.galutinisVidurkis
                   << setw(20) << studentas.galutinisMediana << "\n";
        }
    }
    catch (const runtime_error &ex)
    {
        cerr << ex.what() << "\n";
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
        studentas.vardas = skaitytiZodi("Iveskite varda: ");
        studentas.pavarde = skaitytiZodi("Iveskite pavarde: ");

        int namuDarbai = skaitytiSkaiciu("Iveskite semestro pazymiu skaiciu: ", 1, 10);

        for (int i = 0; i < namuDarbai; i++)
        {
            cout << "Iveskite " << i + 1 << " pazymi is " << namuDarbai << ": ";
            int pazymys = skaitytiSkaiciu("", 1, 10);

            studentas.pazymiai.push_back(pazymys);
        }

        int pazymys = skaitytiSkaiciu("Iveskite egzamino pazymi: ", 1, 10);

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
        int input = skaitytiSkaiciu("Galutinio balo skaiciavimo budas (1 - vidurkis, 2 - mediana):\n", 1, 2);

        switch (input)
        {
        case 1:
            for (Studentas &studentas : studentai)
            {
                int semestroPazymiuSuma = gautiPazymiuSuma(studentas);
                double vidurkis = gautiVidurkiVidutini(studentas, semestroPazymiuSuma);
                studentas.galutinisVidurkis = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;
            }
            return false;
        case 2:
            for (Studentas &studentas : studentai)
            {
                sort(studentas.pazymiai.begin(), studentas.pazymiai.end());
                int semestroPazymiuSuma = gautiPazymiuSuma(studentas);
                double vidurkis = gautiVidurkiMediana(studentas, semestroPazymiuSuma);
                studentas.galutinisMediana = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;
            }
            return true;
        default:
            cout << "Neteisingas pasirinkimas!\n";
        }
    }
    catch (const runtime_error &ex)
    {
        cerr << ex.what() << endl;
    }

    return false;
}

void suskaiciuotiGalutinius(vector<Studentas> &studentai)
{
    for (Studentas &studentas : studentai)
    {
        int semestroPazymiuSuma = gautiPazymiuSuma(studentas);

        double vidurkis = gautiVidurkiVidutini(studentas, semestroPazymiuSuma);
        studentas.galutinisVidurkis = vidurkis * 0.4 + studentas.egzaminoBalas * 0.6;

        sort(studentas.pazymiai.begin(), studentas.pazymiai.end());
        double mediana = gautiVidurkiMediana(studentas, semestroPazymiuSuma);
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
    try
    {
        studentas.vardas = skaitytiZodi("Iveskite varda: ");
        studentas.pavarde = skaitytiZodi("Iveskite pavarde: ");

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
    catch (const runtime_error &ex)
    {
        cerr << ex.what() << endl;
    }
}

void nuskaitytiFaila(vector<Studentas> &studentai, const string &failoPavadinimas)
{
    ifstream failas(failoPavadinimas);
    if (!failas.is_open())
        throw runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);

    string antraste;
    if (!getline(failas, antraste))
        throw runtime_error("Failas tuscias: " + failoPavadinimas);

    istringstream ss(antraste);
    string zodis;
    int zodziuSkaicius = 0;
    while (ss >> zodis)
    {
        zodziuSkaicius++;
    }

    if (zodziuSkaicius < 4)
        throw runtime_error("Neteisinga antraste: " + failoPavadinimas);

    int namuDarbai = zodziuSkaicius - 3;

    Studentas studentas;
    studentas.namuDarbai = namuDarbai;
    while (failas >> studentas.vardas >> studentas.pavarde)
    {
        studentas.pazymiai.clear();
        bool skaitymoPavyko = true;

        for (int i = 0; i < namuDarbai; i++)
        {
            int pazymys;
            if (!(failas >> pazymys))
            {
                skaitymoPavyko = false;
                break;
            }
            studentas.pazymiai.push_back(pazymys);
        }

        if (!skaitymoPavyko || !(failas >> studentas.egzaminoBalas))
            throw runtime_error("Sugadintas failas: " + failoPavadinimas);

        studentai.push_back(studentas);
    }

    suskaiciuotiGalutinius(studentai);
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

void rusiuotiStudentus(vector<Studentas> &studentai, int input)
{
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
}

void surusiuotiPagalPasirinkima(vector<Studentas> &studentai)
{
    int input = skaitytiSkaiciu("Rusiuoti pagal (1 - vardas, 2 - pavarde, 3 - galutinis (vidurkis), 4 - galutinis (mediana):\n", 1, 4);

    rusiuotiStudentus(studentai, input);
}

int skaitytiSkaiciu(const string &pranesimas, int min, int max)
{
    while (true)
    {
        try
        {
            cout << pranesimas;
            string eilute;
            cin >> eilute;

            for (int i = 0; i < eilute.size(); i++)
            {
                if (i == 0 && eilute[i] == '-')
                {
                    continue;
                }
                if (!isdigit(eilute[i]))
                {
                    throw runtime_error("Klaida: ivestas ne sveikas skaicius.");
                }
            }

            int reiksme = stoi(eilute);

            if (reiksme < min || reiksme > max)
                throw runtime_error("Klaida: skaicius turi buti nuo " + to_string(min) + " iki " + to_string(max) + ".");

            return reiksme;
        }
        catch (const runtime_error &ex)
        {
            cerr << "Klaida: " << ex.what() << "\n";
        }
    }
}

string skaitytiZodi(const string &pranesimas)
{
    while (true)
    {
        try
        {
            cout << pranesimas;
            string eilute;
            cin >> eilute;

            for (char c : eilute)
            {
                if (!isalpha(c))
                {
                    throw runtime_error("Klaida: ivestas zodis turi turėti tik raides.");
                }
            }

            return eilute;
        }
        catch (const runtime_error &ex)
        {
            cerr << "Klaida: " << ex.what() << "\n";
        }
    }
}

string generuotiFaila(int studentuSkaicius, int namuDarbuSkaicius)
{
    const string failoPavadinimas = "studentai" + to_string(studentuSkaicius);

    ofstream failas("../generatedData/" + failoPavadinimas + ".txt");

    if (!failas.is_open())
        throw runtime_error("Klaida: nepavyko atidaryti failo irasymui.");

    failas << left << setw(20) << "Vardas" << setw(20) << "Pavarde";

    for (int i = 1; i <= namuDarbuSkaicius; i++)
    {
        failas << right << setw(10) << "ND" + to_string(i);
    }
    failas << right << setw(10) << " Egz." << "\n";

    for (int i = 0; i < studentuSkaicius; i++)
    {
        failas << left << setw(20) << "VardasNR" + to_string(i + 1) << setw(20) << "PavardeNR" + to_string(i + 1);

        failas << right;
        for (int j = 0; j < namuDarbuSkaicius; j++)
        {
            failas << setw(10) << randomInt(1, 10);
        }
        failas << setw(10) << randomInt(1, 10) << "\n";
    }

    return failoPavadinimas;
}

void skaidytiStudentus(vector<Studentas> &studentai, vector<Studentas> &vargsiukai, vector<Studentas> &kietiakai)
{
    for (const Studentas &studentas : studentai)
    {
        if (studentas.galutinisVidurkis < 5 && studentas.galutinisMediana < 5)
        {
            vargsiukai.push_back(studentas);
        }
        else
        {
            kietiakai.push_back(studentas);
        }
    }
}

void failuGeneravimas()
{
    int studentuSkaicius = skaitytiSkaiciu("Iveskite studentu skaiciu (1 - 10 000 000):\n", 1, 10000000);
    int namuDarbuSkaicius = skaitytiSkaiciu("Iveskite namu darbu skaiciu (1 - 100):\n", 1, 100);

    string failoPavadinimas;
    try
    {
        failoPavadinimas = generuotiFaila(studentuSkaicius, namuDarbuSkaicius);
    }
    catch (const runtime_error &ex)
    {
        cerr << "KLAIDA: " << ex.what() << "\n";
    }

    bool arPadalinti = skaitytiSkaiciu("Ar norite padalinti studentus? (1 - Taip, 2 - Ne):\n", 1, 2) == 1;

    if (arPadalinti)
    {
        vector<Studentas> studentai;

        try
        {
            nuskaitytiFaila(studentai, "../generatedData/" + failoPavadinimas + ".txt");
        }
        catch (const runtime_error &ex)
        {
            cerr << "KLAIDA: " << ex.what() << "\n";
        }
        suskaiciuotiGalutinius(studentai);

        vector<Studentas> vargsiukai;
        vector<Studentas> kietiakai;
        skaidytiStudentus(studentai, vargsiukai, kietiakai);

        int input = skaitytiSkaiciu("Rusiuoti pagal (1 - vardas, 2 - pavarde, 3 - galutinis (vidurkis), 4 - galutinis (mediana):\n", 1, 4);
        rusiuotiStudentus(vargsiukai, input);
        rusiuotiStudentus(kietiakai, input);

        isvestisFailas(vargsiukai, failoPavadinimas + "_vargsiukai.txt");
        isvestisFailas(kietiakai, failoPavadinimas + "_kietiakai.txt");
    }
}

void testuotiGreiti()
{
    int input = skaitytiSkaiciu("Pasirinkite (1 - failo kurimo testas, 2 - duomenu apdorojimo testas):\n", 1, 2);

    switch (input)
    {
    case 1:
        failoKurimoTestavimas();
        break;
    case 2:
        duomenuApdorojimoTestavimas();
        break;
    default:
        cout << "Neteisingas pasirinkimas!\n";
    }
}

void failoKurimoTestavimas()
{
    int studentuSkaicius = skaitytiSkaiciu("Iveskite studentu skaiciu (1 - 10 000 000):\n", 1, 10000000);
    int namuDarbuSkaicius = skaitytiSkaiciu("Iveskite namu darbu skaiciu (1 - 100):\n", 1, 100);

    Timer timer;
    try
    {
        generuotiFaila(studentuSkaicius, namuDarbuSkaicius);
    }
    catch (const runtime_error &ex)
    {
        cerr << "KLAIDA: " << ex.what() << "\n";
    }
    cout << fixed << setprecision(2);
    cout << "Failo sukurimo laikas: " << timer.elapsed() << " s" << endl;
}

void duomenuApdorojimoTestavimas()
{
    const vector<string> failai = {
        "../archive/studentai1000.txt",
        "../archive/studentai10000.txt",
        "../archive/studentai100000.txt",
        "../archive/studentai1000000.txt",
        "../archive/studentai10000000.txt"};

    int input = skaitytiSkaiciu("Pasirinkite 1 - studentai1000.txt, 2 - studentai10000.txt, 3 - studentai100000.txt, 4 - studentai1000000.txt, 5 - studentai10000000.txt):\n", 1, 5);

    const string &pasirinktasFailas = failai[input - 1];
    cout << "Pasirinktas failas: " << pasirinktasFailas << "\n";

    vector<Studentas> studentai;
    Timer totalTimer;
    Timer taskTimer;

    try
    {
        nuskaitytiFaila(studentai, pasirinktasFailas);
        cout << fixed << setprecision(2)
             << "Duomenu nuskaitymo is failo laikas: " << taskTimer.elapsed() << " s\n";
    }
    catch (const runtime_error &ex)
    {
        cerr << "Klaida skaitant faila: " << ex.what() << "\n";
        return;
    }

    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakai;
    taskTimer.reset();
    skaidytiStudentus(studentai, vargsiukai, kietiakai);
    cout << "Studentu rusiavimo i dvi grupes laikas: " << taskTimer.elapsed() << " s\n";

    studentai.clear();
    studentai.shrink_to_fit();

    taskTimer.reset();
    rusiuotiStudentus(vargsiukai, 3);
    rusiuotiStudentus(kietiakai, 3);
    cout << "Studentu rusiavimo pagal vidurki laikas: " << taskTimer.elapsed() << " s\n";

    taskTimer.reset();
    isvestisFailas(vargsiukai, "../outputData/testas_vargsiukai.txt");
    isvestisFailas(kietiakai, "../outputData/testas_kietiakai.txt");
    cout << "Studentu isvedimo i du naujus failus laikas: " << taskTimer.elapsed() << " s\n";

    cout << "Viso testavimo veikimo laikas: " << totalTimer.elapsed() << " s\n";
}

void failoNuskaitymas(vector<Studentas> &studentai)
{
    Timer timer;
    try
    {
        // nuskaitytiFaila(studentai, "../data/kursiokai.txt");
        // nuskaitytiFaila(studentai, "../data/studentai10000.txt");
        nuskaitytiFaila(studentai, "../data/studentai100000.txt");
        // nuskaitytiFaila(studentai, "../data/studentai1000000.txt");
    }
    catch (const runtime_error &ex)
    {
        cerr << "KLAIDA: " << ex.what() << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "Nuskaitymo laikas: " << timer.elapsed() << " s\n";
}
