#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <random>
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
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
using std::uniform_int_distribution;
using std::vector;

struct Studentas
{
    string vardas = "A", pavarde = "B";
    int namuDarbai = 0;
    vector<int> pazymiai;
    int egzaminoBalas = 0;
    double galutinisVidurkis = 0;
    double galutinisMediana = 0;
};

void isvestis(const vector<Studentas> &studentai, bool arMediana);
void isvestisKonsole(const vector<Studentas> &studentai);
void isvestisFailas(const vector<Studentas> &studentai);
double gautiVidurkiVidutini(const Studentas &studentas, int pazymiuSuma);
int gautiVidurkiMediana(const Studentas &studentas, int pazymiuSuma);
void ivestisRanka(Studentas &studentas);
int gautiPazymiuSuma(const Studentas &studentas);
bool suskaiciuotiGalutini(vector<Studentas> &studentai);
void suskaiciuotiGalutinius(vector<Studentas> &studentai);
int randomInt(int min, int max);
void generuotiStudenta(Studentas &studentas);
void generuotiPazymius(Studentas &studentas);
bool nuskaitytiFaila(vector<Studentas> &studentai, const string &failoPavadinimas);
bool rusiuotiPagalVarda(const Studentas &a, const Studentas &b);
bool rusiuotiPagalPavarde(const Studentas &a, const Studentas &b);
bool rusiuotiPagalGalutiniVidurki(const Studentas &a, const Studentas &b);
bool rusiuotiPagalGalutiniMediana(const Studentas &a, const Studentas &b);
void surusiuotiPagalPasirinkima(vector<Studentas> &studentai);