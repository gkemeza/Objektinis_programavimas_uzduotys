#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <random>
#include <stdexcept>
#include <filesystem>
#include <list>
#include <deque>

struct Studentas
{
    std::string vardas = "A", pavarde = "B";
    int namuDarbai = 0;
    std::vector<int> pazymiai;
    int egzaminoBalas = 0;
    double galutinisVidurkis = 0;
    double galutinisMediana = 0;
};

using StudentuKonteineris = std::vector<Studentas>;
// using StudentuKonteineris = std::list<Studentas>;
// using StudentuKonteineris = std::deque<Studentas>;

using Comparator = bool (*)(const Studentas &, const Studentas &);

template <typename Konteineris>
void surusiuotiPazymius(Konteineris &studentas)
{
    sort(studentas.pazymiai.begin(), studentas.pazymiai.end());
}

template <typename Konteineris>
inline void surusiuotiStudentus(Konteineris &studentai, Comparator comparator)
{
    sort(studentai.begin(), studentai.end(), comparator);
}

template <>
inline void surusiuotiStudentus(std::list<Studentas> &studentai, Comparator comparator)
{
    studentai.sort(comparator);
}

void isvestis(const StudentuKonteineris &studentai, bool arMediana);
void isvestisKonsole(const StudentuKonteineris &studentai);
void isvestisFailas(const StudentuKonteineris &studentai, std::string failoPavadinimas);
double gautiVidurkiVidutini(const Studentas &studentas, int pazymiuSuma);
int gautiVidurkiMediana(const Studentas &studentas, int pazymiuSuma);
void ivestisRanka(Studentas &studentas);
int gautiPazymiuSuma(const Studentas &studentas);
bool suskaiciuotiGalutini(StudentuKonteineris &studentai);
void suskaiciuotiGalutinius(StudentuKonteineris &studentai);
int randomInt(int min, int max);
void generuotiStudenta(Studentas &studentas);
void generuotiPazymius(Studentas &studentas);
void nuskaitytiFaila(StudentuKonteineris &studentai, const std::string &failoPavadinimas);
bool rusiuotiPagalVarda(const Studentas &a, const Studentas &b);
bool rusiuotiPagalPavarde(const Studentas &a, const Studentas &b);
bool rusiuotiPagalGalutiniVidurki(const Studentas &a, const Studentas &b);
bool rusiuotiPagalGalutiniMediana(const Studentas &a, const Studentas &b);
void rusiuotiStudentus(StudentuKonteineris &studentai, int input);
void surusiuotiPagalPasirinkima(StudentuKonteineris &studentai);
int skaitytiSkaiciu(const std::string &pranesimas, int min, int max);
std::string skaitytiZodi(const std::string &pranesimas);
std::string generuotiFaila(int studentuSkaicius, int namuDarbuSkaicius);
void failuGeneravimas();
void testuotiGreiti();
void failoKurimoTestavimas();
void duomenuApdorojimoTestavimas();
void failoNuskaitymas(StudentuKonteineris &studentai);
void failoDuomenuApdorojimas(StudentuKonteineris &studentai);
void studentuDuomenuApdorojimas(StudentuKonteineris &studentai);
