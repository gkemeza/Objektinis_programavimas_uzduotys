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

struct Studentas
{
    std::string vardas = "A", pavarde = "B";
    int namuDarbai = 0;
    std::vector<int> pazymiai;
    int egzaminoBalas = 0;
    double galutinisVidurkis = 0;
    double galutinisMediana = 0;
};

void isvestis(const std::vector<Studentas> &studentai, bool arMediana);
void isvestisKonsole(const std::vector<Studentas> &studentai);
void isvestisFailas(const std::vector<Studentas> &studentai);
double gautiVidurkiVidutini(const Studentas &studentas, int pazymiuSuma);
int gautiVidurkiMediana(const Studentas &studentas, int pazymiuSuma);
void ivestisRanka(Studentas &studentas);
int gautiPazymiuSuma(const Studentas &studentas);
bool suskaiciuotiGalutini(std::vector<Studentas> &studentai);
void suskaiciuotiGalutinius(std::vector<Studentas> &studentai);
int randomInt(int min, int max);
void generuotiStudenta(Studentas &studentas);
void generuotiPazymius(Studentas &studentas);
bool nuskaitytiFaila(std::vector<Studentas> &studentai, const std::string &failoPavadinimas);
bool rusiuotiPagalVarda(const Studentas &a, const Studentas &b);
bool rusiuotiPagalPavarde(const Studentas &a, const Studentas &b);
bool rusiuotiPagalGalutiniVidurki(const Studentas &a, const Studentas &b);
bool rusiuotiPagalGalutiniMediana(const Studentas &a, const Studentas &b);
void surusiuotiPagalPasirinkima(std::vector<Studentas> &studentai);
int skaitytiSkaiciu(const std::string &pranesimas, int min, int max);
std::string skaitytiZodi(const std::string &pranesimas);
void generuotiFaila(int studentuSkaicius, int namuDarbuSkaicius);