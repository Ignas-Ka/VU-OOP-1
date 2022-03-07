#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "header.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>


bool palygintiVardus(Studentas &s1, Studentas &s2)
{
    return (s1.vardas < s2.vardas);
}

std::vector<std::string> split(std::string str, char delimiter)
{
	std::vector<std::string> result;
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos)
    {
        end = str.find(delimiter, start);
        result.push_back(str.substr(start, end - start));
    }

	return result;
}

int main()
{
    std::ios::sync_with_stdio(false);

    vector<Studentas> studentai;

    const bool arSkaitytiIsFailo = patvirtinti("Ar norite nuskaityti studentus is failo?");


    if(arSkaitytiIsFailo)
    {
        vector<string> splited;
        Studentas studentas;
        string eil;
        stringstream my_buffer;
        string tempString;

        int n;


        ifstream fin("10000.txt");
        try
        {
            if(!fin)
            {
                throw(n);
            }
        }
        catch(int n)
        {
            cout << "Tokio failo nera" << "\n";
        }

        my_buffer << fin.rdbuf();
        fin.close();

        string word;
        int ndSkaicius = -3;

        string line;
        getline(my_buffer, line);

        stringstream ss(line);
        while(ss >> word)
        {
            ++ndSkaicius;
        }


        while(my_buffer)
        {
            if (!my_buffer.eof())
            {
                getline(my_buffer, eil);

                vector<string> eilDalys = split(eil, ' ');

                studentas.vardas = eilDalys[0];
                studentas.pavarde = eilDalys[1];

                for(int i = 0; i < ndSkaicius; i++)
                {
                    tempString = eilDalys[2+i];
//                    studentas.pazymiai[i] = stoi(tempString);
//                    cout << to_string(eilDalys[2+i]) << endl;
                }

//                tempString = eilDalys[ndSkaicius+2];

                studentas.egzamino = stoi(tempString);

                studentai.push_back(studentas);
                splited.push_back(eil);

                sort(studentai.begin(), studentai.end(), palygintiVardus);
            }
            else break;
        }

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

    cout << '\n';
    Rezultatai(studentai, ArSkaiciuotiVidurki);
    cout << '\n';

    return 0;
}
