#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "header.h"
#include <fstream>

void eil_po_eil(string read_vardas, string write_vardas)
{
    vector<string> splited;
    string eil;

    ifstream open_f(read_vardas);
    while (open_f)
    {
        if (!open_f.eof())
        {
            getline(open_f, eil);
            splited.push_back(eil);
        }
        else break;
    }
    open_f.close();

    ofstream out_f(write_vardas);
    for (string a: splited) out_f << a;
    out_f.close();
    splited.resize(0);
}

int main()
{
    vector<Studentas> studentai;

    const bool arSkaitytiIsFailo = patvirtinti("Ar norite nuskaityti studentus is failo?");

    if(arSkaitytiIsFailo)
    {

        Studentas studentas;

        ifstream fin("10000.txt");

        string line;
        getline(fin, line);

//        while(!fin.eof())
//        {
        for(int j = 0; j < 3000; j++)
        {


            fin >> studentas.vardas;
            fin >> studentas.pavarde;
            int pazymys = 0;
            for(int i = 0; i < 15; i++)
            {
                fin >> pazymys;
                studentas.pazymiai.push_back(pazymys);
            }
            fin >> studentas.egzamino;
            studentai.push_back(studentas);
        }
//        }




        fin.close();
    }
    else
    {
        while (true)
        {
            Studentas studentas;

            cout << "Iveskite varda: ";
            getline(cin, studentas.vardas);

            cout << "Iveskite pavarde: ";
            getline(cin, studentas.pavarde);

            const bool ArZinomasPazymiuSk = patvirtinti("Ar zinote tikslu pazymiu skaiciu?");
            const int pazymiuSk = ArZinomasPazymiuSk ? PazymiuSkaicius() : 0;

            bool ArGeneruotiAtsitiktinius = false;
            if (pazymiuSk > 0)
            {
                ArGeneruotiAtsitiktinius = patvirtinti("Ar generuoti pazymius atsitiktinai (jei ne, iveskite ranka)?");
            }

            if (ArGeneruotiAtsitiktinius)
            {
                if (ArZinomasPazymiuSk)
                {
                    for (int i = 0; i < pazymiuSk; i++)
                    {
                        int pazymys = GeneruotiAtsitiktiniIntervale(PAZYMYS_MIN, PAZYMYS_MAX);
                        studentas.pazymiai.push_back(pazymys);
                    }
                }
                else
                {
                    while (true)
                    {
                        int pazymys = GeneruotiAtsitiktiniIntervale(0, PAZYMYS_MAX);
                        if (PazymioVerifikacija(pazymys))
                        {
                            studentas.pazymiai.push_back(pazymys);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                studentas.egzamino = GeneruotiAtsitiktiniIntervale(PAZYMYS_MIN, PAZYMYS_MAX);
                SpausdintiAtsitiktiniusPazymius(&studentas);
            }
            else
            {
                if (ArZinomasPazymiuSk)
                {
                    if (pazymiuSk > 0)
                    {
                        cout << "Iveskite pazymius: ";
                        while (studentas.pazymiai.size() != pazymiuSk)
                        {
                            int pazymys;
                            cin >> pazymys;
                            if (!PazymioVerifikacija(pazymys))
                            {
                                cout << "Pazymys " << pazymys << " indeksu " << studentas.pazymiai.size() << " neatitinka pazymiu intervalo ("
                                     << PAZYMYS_MIN << "-" << PAZYMYS_MAX << "). Istaisykite klaida bei pildykite pazymius toliau." << endl;
                                clearErrorFlagFunkcija();
                            }
                            else
                            {
                                studentas.pazymiai.push_back(pazymys);
                            }
                        }

                        clearErrorFlagFunkcija();
                    }
                }
                else
                {
                    while (true)
                    {
                        cout << "Iveskite pazymi [" << studentas.pazymiai.size() << "] (iveskite -1, jei nenorite ivesti daugiau pazymiu): ";

                        int pazymys;
                        cin >> pazymys;
                        clearErrorFlagFunkcija();

                        if (pazymys == -1)
                        {
                            break;
                        }
                        else
                        {
                            if (!PazymioVerifikacija(pazymys))
                            {
                                cout << "Pazymys " << pazymys << " neatitinka pazymiu intervalo ("
                                     << PAZYMYS_MIN << "-" << PAZYMYS_MAX << ")." << endl;
                            }
                            else
                            {
                                studentas.pazymiai.push_back(pazymys);
                            }
                        }
                    }
                }

                cout << "Iveskite egzamino pazymi: ";
                cin >> studentas.egzamino;
                while (!PazymioVerifikacija(studentas.egzamino))
                {
                    cout << "Pazymys " << studentas.egzamino << " neatitinka pazymiu intervalo ("
                         << PAZYMYS_MIN << "-" << PAZYMYS_MAX << "). Istaisykite klaida bei pildykite pazymius toliau." << endl;
                    clearErrorFlagFunkcija();
                    cin >> studentas.egzamino;
                }

                clearErrorFlagFunkcija();
            }

            studentai.push_back(studentas);
            if (!patvirtinti("Ar norite prideti studenta?"))
            {
                break;
            }
        }
    }


    bool ArSkaiciuotiVidurki = patvirtinti("Ar skaiciuoti vidurki (kitu atveju bus skaiciuojama mediana)?");
    for (int i = 0; i < studentai.size(); i++)
    {
        StudentoFun(&studentai[i], ArSkaiciuotiVidurki);
    }

    cout << endl;
    Rezultatai(studentai, ArSkaiciuotiVidurki);
    cout << endl;

    return 0;
}
