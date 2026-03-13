#include "../include/functions.h"
#include "../include/timer.h"

using std::cerr;
using std::cout;
using std::endl;
using std::fixed;
using std::runtime_error;
using std::setprecision;
using std::vector;

int main()
{
    Timer timer;
    Studentas studentas;
    vector<Studentas> studentai;
    bool isFailo, pridetiStudentai;
    int input;

    do
    {
        input = skaitytiSkaiciu("Pasirinkite (1 - ranka, 2 - generuoti tik pažymius, 3 - generuoti studentų vardus, pavardės ir pažymius, 4 - nuskaityti failą, 5 - generuoti faila, 6 - testuoti greiti, 7 - baigti darbą):\n", 1, 7);

        switch (input)
        {
        case 1:
            ivestisRanka(studentas);
            studentai.push_back(studentas);
            studentas = {};
            pridetiStudentai = true;
            break;
        case 2:
            generuotiPazymius(studentas);
            studentai.push_back(studentas);
            studentas = {};
            pridetiStudentai = true;
            break;
        case 3:
            generuotiStudenta(studentas);
            studentai.push_back(studentas);
            studentas = {};
            pridetiStudentai = true;
            break;
        case 4:
        {
            timer.reset();

            try
            {
                // isFailo = nuskaitytiFaila(studentai, "data\\kursiokai.txt");
                // isFailo = nuskaitytiFaila(studentai, "data\\studentai10000.txt");
                isFailo = nuskaitytiFaila(studentai, "data\\studentai100000.txt");
                //  isFailo = nuskaitytiFaila(studentai, "studentai1000000.txt");
            }
            catch (const runtime_error &ex)
            {
                cerr << "Klaida: " << ex.what() << "\n";
            }

            cout << fixed << setprecision(2);
            cout << "Nuskaitymo laikas: " << timer.elapsed() << " s" << endl;
            break;
        }
        case 5:
            failuGeneravimas();
            break;
        case 6:
            testuotiGreiti();
            break;
        case 7:
            break;
        default:
            cout << "Neteisingas pasirinkimas!\n";
        }
    } while (input != 4 && input != 7);

    if (isFailo)
    {
        suskaiciuotiGalutinius(studentai);
        surusiuotiPagalPasirinkima(studentai);

        int input = skaitytiSkaiciu("Pasirinkite isvedima (1 - Failas, 2 - Konsole):\n", 1, 2);

        switch (input)
        {
        case 1:
            isvestisFailas(studentai, "isvestis.txt");
            break;
        case 2:
            isvestisKonsole(studentai);
            break;
        default:
            cout << "Neteisingas pasirinkimas!\n";
            break;
        }
    }
    else if (pridetiStudentai)
    {
        bool arMediana = suskaiciuotiGalutini(studentai);
        isvestis(studentai, arMediana);
    };
}