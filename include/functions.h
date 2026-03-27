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

// funkcija, kuri grazina true arba false, pagal tai ar pirmas parametras yra "mazesnis" uz antra
using Comparator = bool (*)(const Studentas &, const Studentas &);

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

void ivestisRanka(Studentas &studentas);
void generuotiStudenta(Studentas &studentas);

void generuotiPazymius(Studentas &studentas);
int skaitytiSkaiciu(const std::string &pranesimas, int min, int max);
void failuGeneravimas();
void testuotiGreiti();
void failoNuskaitymas(StudentuKonteineris &studentai);
void failoDuomenuApdorojimas(StudentuKonteineris &studentai);
void studentuDuomenuApdorojimas(StudentuKonteineris &studentai);
