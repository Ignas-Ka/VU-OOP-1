#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

#define PAZYMYS_MIN 1
#define PAZYMYS_MAX 10

struct Studentas
{
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzamino;
    double pazymiuVid;
    double pazymysGalutinis;
    double pazymiuMed;
};

void clearErrorFlagFunkcija()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool patvirtinti(const string &pranesimas, char taip = 'y', char ne = 'n')
{
    while (true)
    {
        cout << "-> " << pranesimas << " (" << taip << "/" << ne << "): ";

        char atsakas;
        cin >> atsakas;
        clearErrorFlagFunkcija();
        if (atsakas == taip)
        {
            return true;
        }
        else if (atsakas == ne)
        {
            return false;
        }
        else
        {
            cout << "Netinkamas simbolis ";
        }
    }
}

double VidurkioSkaiciavimas(vector<int> &masyvas)
{
    const int masyvoDydis = masyvas.size();
    int sum = 0;
    for (int i = 0; i < masyvoDydis; i++)
    {
        sum += masyvas[i];
    }

    return (double)sum / masyvoDydis;
}

double MedianosPaieska(vector<int> &masyvas)
{
    sort(masyvas.begin(), masyvas.end());

    const int masyvoDydis = masyvas.size();
    const bool ArVidurinis = masyvoDydis % 2 != 0;

    if (ArVidurinis)
    {
        return (double)masyvas[masyvoDydis / 2];
    }

    return (double)(masyvas[(masyvoDydis - 1) / 2] + masyvas[masyvoDydis / 2]) / 2.0;
}

int PazymiuSkaicius()
{
    cout << "Iveskite pazymiu skaiciu: ";
    int pazymiuSk;
    cin >> pazymiuSk;
    clearErrorFlagFunkcija();

    while (pazymiuSk < 0)
    {
        cout << "Pazymiu skaicius negali buti neigiamas, iveskite nauja reiksme: ";
        cin >> pazymiuSk;
        clearErrorFlagFunkcija();
    }

    return pazymiuSk;
}

int GeneruotiAtsitiktiniIntervale(int min, int max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

bool PazymioVerifikacija(int pazymys)
{
    return pazymys >= PAZYMYS_MIN && pazymys <= PAZYMYS_MAX;
}

void KuriSpausdinti(Studentas *studentas, bool RodytiVidurki = true)
{
    cout << left
         << setw(10) << studentas->vardas
         << setw(15) << studentas->pavarde
         << setw(12) << fixed << setprecision(2)
         << (RodytiVidurki ? studentas->pazymysGalutinis : studentas->pazymiuMed)
         << endl;
}

void Rezultatai(vector<Studentas> &studentai, bool RodytiVidurki = true)
{
    cout << left
         << setw(10) << "Vardas"
         << setw(16) << "Pavarde"
         << "Galutinis " << (RodytiVidurki ? "Vid." : "Med.") << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (int i = 0; i < studentai.size(); i++)
    {
        KuriSpausdinti(&studentai[i], RodytiVidurki);
    }
}

void StudentoFun(Studentas *studentas, bool ArSkaiciuotiVidurki = true)
{
    studentas->pazymysGalutinis = 0;
    studentas->pazymiuVid = 0;
    studentas->pazymiuMed = 0;
    if (ArSkaiciuotiVidurki)
    {
        if (studentas->pazymiai.size() > 0)
        {
            studentas->pazymiuVid = VidurkioSkaiciavimas(studentas->pazymiai);
        }
        studentas->pazymysGalutinis = 0.4 * studentas->pazymiuVid + 0.6 * studentas->egzamino;
    }
    else
    {
        if (studentas->pazymiai.size() > 0)
        {
            studentas->pazymiuMed = MedianosPaieska(studentas->pazymiai);
        }
    }
}

void SpausdintiAtsitiktiniusPazymius(Studentas *studentas)
{
    cout << "Sugeneruoti " << studentas->pazymiai.size() << " sie atsitiktiniai pazymiai: ";
    for (int i = 0; i < studentas->pazymiai.size(); i++)
    {
        cout << studentas->pazymiai[i] << " ";
    }
    cout << endl;
    cout << "Sugeneruotas atsitiktinis egzamino pazymys: " << studentas->egzamino << endl;
}



#endif
