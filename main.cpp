#include "functions.h"
#include "timer.h"

int main()
{
    Studentas studentas;
    vector<Studentas> studentai;
    bool isFailo;
    int input;
    Timer timer;

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
            ivestisRanka(studentas);
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
        {
            timer.reset();

            try
            {
                // isFailo = nuskaitytiFaila(studentai, "Failai\\kursiokai.txt");
                isFailo = nuskaitytiFaila(studentai, "Failai\\studentai10000.txt");
                // isFailo = nuskaitytiFaila(studentai, "Failai\\studentai100000.txt");
                //  isFailo = nuskaitytiFaila(studentai, "Failai\\studentai1000000.txt");
            }
            catch (const runtime_error &ex)
            {
                cerr << "Klaida: " << ex.what() << endl;
            }

            cout << fixed << setprecision(2);
            cout << "Nuskaitymo laikas: " << timer.elapsed() << " s" << endl;
            break;
        }
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

        int input;
        do
        {
            cout << "Pasirinkite isvedima (1 - Failas, 2 - Konsole):\n";
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
                timer.reset();
                isvestisFailas(studentai);

                cout << fixed << setprecision(2);
                cout << "Output laikas: " << timer.elapsed() << " s" << endl;
                break;
            case 2:
                timer.reset();
                isvestisKonsole(studentai);

                cout << fixed << setprecision(2);
                cout << "Output laikas: " << timer.elapsed() << " s" << endl;
            default:
                cout << "Neteisingas pasirinkimas!\n";
                break;
            }
        } while (input != 1 && input != 2);
    }
    else
    {
        bool arMediana = suskaiciuotiGalutini(studentai);
        isvestis(studentai, arMediana);
    }
};