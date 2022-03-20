
#include "Circle.h"

/*
bool compare_pavarde(const string &a, const string &b) {
    if (a.pavarde == b.pavarde) return a.vardas < b.vardas;
    return a.pavarde < b.pavarde;
}
*/
void nuskaitymas() {
    ifstream df(duom);
    ofstream rf(rez);
    ofstream rf1(rez1);

    rf << std::left << std::setw(15) << "Vardas " << std::setw(15) << "Pavarde " << std::setw(15) << "Galutinis (Vid.) " << std::setw(15) << "Galutinis (Med.) " << endl;
    rf << "---------------------------------------------------------------- " << endl;
    rf1 << std::left << std::setw(15) << "Vardas " << std::setw(15) << "Pavarde " << std::setw(15) << "Galutinis (Vid.) " << std::setw(15) << "Galutinis (Med.) " << endl;
    rf1 << "---------------------------------------------------------------- " << endl;
    //df.ignore();
    df.ignore(LONG_MAX, '\n');
    int p_elem = 0;
    //  int n=0;
    int paz;
    double vidurkis = 0;
    vector<data> sarasas;
    int ind = 0;



    auto start = std::chrono::high_resolution_clock::now();
    auto st=start;


    while (!df.eof()) {
        data temp;
        df >> temp.vardas >> temp.pavarde;
        // cout << temp.vardas << " " << temp.pavarde << " " << endl;;
        // while (df >> temp.nd[n]) {
          //   cout << temp.nd[n] << endl
        for (int i = 0; i < 5; i++) {
            df >> paz;
            temp.nd.push_back(paz);
            vidurkis += paz;
            // cout << paz << " ";
            // n++;
        }
        df >> temp.egz;
        // cout << "egz " << temp.egz << endl;

        // }

        if (temp.nd.size() != 0) vidurkis = vidurkis / temp.nd.size();

        else vidurkis = 0;

        temp.rez = vidurkis * 0.4 + temp.egz * 0.6;


        //mediana


        sort(temp.nd.begin(), temp.nd.begin() + temp.nd.size());
        if (temp.nd.size() % 2 == 1) {
            temp.mediana = temp.nd[temp.nd.size() / 2] * 0.4 + temp.egz * 0.6;
        }
        else {
            temp.mediana = ((temp.nd[temp.nd.size() / 2] + temp.nd[(temp.nd.size() / 2) - 1]) / 2.0) * 0.4 + temp.egz * 0.6;
        }




        sarasas.push_back(temp);
        vidurkis = 0;
    cout << ind << endl;
    ind++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start; // Skirtumas (s)
    std::cout << "1000000 eiluciu failo nuskaitymas uztruko: "<< diff.count() << " s\n";
//    return 0;
//    exit(0);

    //rikiavimas

   // std::sort(sarasas.begin(), sarasas.end(), compare_pavarde);
    //pagal pavarde
    /*
    std::sort(sarasas.begin(), sarasas.end(), [](data a, data b) {
        if (a.pavarde == b.pavarde) return a.vardas < b.vardas;
        return a.pavarde < b.pavarde;
        });
        */
    //pagal varda
    /*
    std::sort(sarasas.begin(), sarasas.end(), [](data a, data b) {
        if (a.vardas == b.vardas) return a.pavarde < b.pavarde;
        return a.vardas < b.vardas;
        });
        */
    //pagal pazymius

    std::sort(sarasas.begin(), sarasas.end(), [](data a, data b) {
        if (a.rez == b.rez) return a.pavarde < b.pavarde;
        return a.rez < b.rez;
        });

    //isvedimas



    start = std::chrono::high_resolution_clock::now();



    for (const auto& el : sarasas) {
        if(el.rez >= 5)
        {
            rf1 << std::left << std::setw(15) << el.vardas << " " << std::setw(15) << el.pavarde;
            rf1 << std::setw(15) << std::fixed << std::setprecision(2) << el.rez << std::setw(15) << std::fixed << std::setprecision(2) << el.mediana << " " << endl;
        }
        else
        {
            rf << std::left << std::setw(15) << el.vardas << " " << std::setw(15) << el.pavarde;
            rf << std::setw(15) << std::fixed << std::setprecision(2) << el.rez << std::setw(15) << std::fixed << std::setprecision(2) << el.mediana << " " << endl;

        }
    }


    end = std::chrono::high_resolution_clock::now();
    diff = end-start; // Skirtumas (s)
    std::cout << "1000000 eiluciu failo rusiavimas ir isvedimas i 2 naujus failus uztruko: "<< diff.count() << " s\n";


    diff = std::chrono::high_resolution_clock::now()-st; // Skirtumas (s)
    std::cout << "Visas sugaistas laikas: "<< diff.count() << " s\n\n";


    df.close();
    rf.close();
    sarasas.clear();

}


bool isNumber(const string& s) {

    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

void fileGenerator(int studentuKiekis, string failoPav)
{
    string vardas, pavarde;
    srand(time(0));
    ofstream fout(failoPav + ".txt");
    fout << "Vardas" << setw(31) << "Pavarde";
    for(int i = 1; i <= 5; i++)
    {
        fout << setw(24) << "ND" << i << setw(26);
    }
    fout << "Egz." << setw(25) << '\n';
    for(int i = 1; i <= studentuKiekis; i++)
    {
        vardas = "Vardas"+to_string(i);
        pavarde = "Pavarde"+to_string(i);
        fout << left << setw(30) << vardas << setw(29) << pavarde;
        for(int j = 0; j < 6; j++)
        {
            fout << setw(25) << (rand() % 10) + 1;
        }
        fout << '\n';
    }
    fout.close();
}

void ivestis(data& temp) {
    int n = 0;
    int k = 1;
    double vidurkis = 0;
    string s1;
    temp.nd.clear();
    cout << "Iveskite varda: "; cin >> temp.vardas;
    cout << "Iveskite pavarde: "; cin >> temp.pavarde;
    cout << "Rasykite 0, jei pazymiai baigiasi (max nd pazymiu yra " << C << " )" << endl;

    temp.nd.reserve(1);
    while (k && (n < C)) {    //

        cout << "Iveskite " << n + 1 << " - a pazymi: ";
        // cin >> temp.nd[n];
        cin >> s1;
        //s1 = std::to_string(temp.nd[n]);// pavercia i stringa
        if (isNumber(s1) && !(std::stoi(s1) > 10 || std::stoi(s1) < 0)) {
            // temp.nd[n] = std::stoi(s1);     // konvertuoja string i int tipa
            if (std::stoi(s1) == 0) {
                k = 0;
            }
            else {
                temp.nd.push_back(std::stoi(s1));
                vidurkis += temp.nd.back();
            }
        }
        else {
            //temp.nd[n] = 10;
            temp.nd.push_back(10);
            vidurkis += temp.nd.back();
            cout << "galimai ivedete ne numeri arba netinkama pazymi todel " << n + 1 << " mokiniui(-ei) jis buvo pakeistas i 10" << endl;
        }


        if (k != 0) {
            n++;
            temp.nd.reserve(n + 1);
        }
    }


    if (temp.nd.size() != 0) {
        vidurkis = vidurkis / n;
    }
    else vidurkis = 0;



    cout << "Iveskite egzamino ivertinima: "; //cin >> temp.egz;
    cin >> s1;
    if (isNumber(s1) && !(std::stoi(s1) > 10 || std::stoi(s1) < 0)) {
        temp.egz = std::stoi(s1);
    }
    else {
        temp.egz = 10;
        cout << "galimai ivedete ne numeri arba netinkama egzamino pazymi todel " << n + 1 << " mokiniui(-ei) jis buvo pakeistas i 10" << endl;
    }
    temp.rez = vidurkis * 0.4 + temp.egz * 0.6;

    // medianos skaiciavimas
    if (temp.nd.size() == 0) {
        temp.mediana = temp.egz * 0.6;
    }
    else {
        sort(temp.nd.begin(), temp.nd.begin() + n);
        //temp.nd.size() vietoj n
        if (temp.nd.size() % 2 == 1) {
            temp.mediana = temp.nd[temp.nd.size() / 2] * 0.4 + temp.egz * 0.6;
        }
        else {
            temp.mediana = ((temp.nd[temp.nd.size() / 2] + temp.nd[(temp.nd.size() / 2) - 1]) / 2.0) * 0.4 + temp.egz * 0.6;
        }
    }

    //return temp;
}

void ivestis1(data& temp, int kiek) {
    // int n=0;
    double vidurkis = 0;
    srand((unsigned)time(0));
    if (kiek > 0) {
        temp.nd.reserve(kiek);
    }

    cout << "Iveskite varda: "; cin >> temp.vardas;
    cout << "Iveskite pavarde: "; cin >> temp.pavarde;
    cout << "pazymiai: " << endl;
    for (int i = 0; i < kiek; i++) {    //C
        temp.nd[i] = (rand() % 10) + 1; // pazymiai nuo 1 iki 10
        cout << temp.nd[i] << " ";
        vidurkis += temp.nd[i];
        // n++;

    }

    if (kiek != 0) {
        vidurkis = vidurkis / kiek;
    }
    else vidurkis = 0;

    temp.egz = (rand() % 10) + 1;
    cout << endl;
    cout << "Egzaminas: " << temp.egz << endl;

    temp.rez = vidurkis * 0.4 + temp.egz * 0.6;

    // medianos skaiciavimas
    if (kiek > 0) {
        sort(temp.nd.begin(), temp.nd.begin() + kiek);
        if (kiek % 2 == 1) {
            temp.mediana = temp.nd[kiek / 2] * 0.4 + temp.egz * 0.6;
        }
        else {
            temp.mediana = ((temp.nd[kiek / 2] + temp.nd[(kiek / 2) - 1]) / 2.0) * 0.4 + temp.egz * 0.6;
        }
    }
    else temp.mediana = temp.egz * 0.6;
}

void ivestisfailas(data& temp) {
    cout << "labas" << endl;
}

void isved(const data& temp) {
    cout << std::left << std::setw(10) << temp.vardas << " " << std::setw(10) << temp.pavarde;
    cout << std::setw(10) << std::fixed << std::setprecision(2) << temp.rez << " " << endl;
}

void isvedmediana(const data& temp) {
    cout << std::left << std::setw(10) << temp.vardas << " " << std::setw(10) << temp.pavarde;
    cout << std::setw(10) << std::fixed << std::setprecision(2) << temp.mediana << " " << endl;
}

void isvedfailas(const data& temp) {
    cout << std::left << std::setw(10) << temp.vardas << " " << std::setw(10) << temp.pavarde;
    cout << std::setw(10) << std::fixed << std::setprecision(2) << temp.rez << std::setw(10) << std::fixed << std::setprecision(2) << temp.mediana << " " << endl;
}

void trycatch(string& a) {
    cin >> a;
    do {
        try {
            if (cin.fail()) {
                throw std::runtime_error("Irasete netinkamai\n");
            }
        }
        catch (const std::runtime_error& e) {
            std::wcout << e.what();
            std::wcin.clear();
            std::wcin.ignore(256, '\n');
            cout << "Iveskite is naujo: " << endl;
            cin >> a;
        }
    } while (std::cin.fail() == true);
}

void eil_po_eil(std::string read_vardas, std::string write_vardas, vector<data>& sarasas) {
    data laikinas;
    std::vector<std::string> splited;
    std::string eil;
    std::string abcas;
    std::stringstream my_buffer;
    string paz;
    double vidurkis = 0;
    int n = 1;
    int nd;
    //----------------------------------------------------------------------
   // auto start = std::chrono::high_resolution_clock::now(); auto st = start;
    std::ifstream open_f(read_vardas);
    std::ofstream out_f(write_vardas);

    out_f << std::left << std::setw(10) << "Vardas " << std::setw(10) << "Pavarde " << std::setw(10) << "Galutinis (Vid.) " << std::setw(10) << "Galutinis (Med.) " << endl;
    out_f << "---------------------------------------------------------------- " << endl;
    while (open_f) {
        if (!open_f.eof()) {
            std::getline(open_f, eil);
            splited.push_back(eil);
            my_buffer.str(eil);
            //cout << eil << endl;
            // nuskaitymas
            my_buffer >> laikinas.vardas >> laikinas.pavarde;
            cout << laikinas.vardas << " " << laikinas.pavarde << " ";
            for (int i = 0; i < 15; i++) {
                my_buffer >> paz;
                cout << paz << " ";
            }


            cout << endl;



        }
        else break;
    }

    open_f.close();
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> diff = end - start; // Skirtumas (s)
    // std::cout << "Failo nuskaitymas tesiai á eiluèiø vektoriø uştruko: " << diff.count() << " s\n";
     //------------------------------------------------------------------------
    // start = std::chrono::high_resolution_clock::now();

    // for (std::string a : splited) out_f << a << endl;

    out_f.close();

    // end = std::chrono::high_resolution_clock::now();
    // diff = end - start; // Skirtumas (s)
    // std::cout << "Failo árağymas eilutemis iğ eiluèiø vektoriaus uştruko: " << diff.count() << " s\n";
    splited.resize(0);
    //sarasas.resize(0);

   // diff = std::chrono::high_resolution_clock::now() - st; // Skirtumas (s)
   // std::cout << "Visas sugaiğtas laikas: " << diff.count() << " s\n\n";
}
























/*

while (open_f) {
    n = 1;
    //  laikinas.nd.clear();
    //  laikinas.nd.reserve(n);

    if (!open_f.eof()) {
        std::getline(open_f, eil);
        my_buffer.str(eil);
        // cout << eil;
         // nuskaitymas


        my_buffer >> laikinas.vardas >> laikinas.pavarde;
        cout << laikinas.vardas << " " << laikinas.pavarde << " ";
        for (int i = 0; i < 15; i++) { my_buffer >> paz; cout << paz; }


        /*
        while ((my_buffer >> paz)&&(isNumber(paz))) {
       // if ((isNumber(paz)) {
            n++;
                vidurkis += std::stoi(paz);
            //    cout << paz << " ";
                laikinas.nd.reserve(n);
                laikinas.nd.push_back(std::stoi(paz));
      //  }
        }


        // my_buffer.str("");
        // cout << endl;
        // laikinas.egz = paz;
         //cout << laikinas.egz << endl;
        // laikinas.nd.pop_back();

         vidurkis = vidurkis / laikinas.nd.size();
         laikinas.rez = vidurkis * 0.4 + laikinas.egz * 0.6;


         //mediana
         sort(laikinas.nd.begin(), laikinas.nd.begin() + laikinas.nd.size());
         if (laikinas.nd.size() % 2 == 1) {
             laikinas.mediana = laikinas.nd[laikinas.nd.size() / 2] * 0.4 + laikinas.egz * 0.6;
         }
         else {
             laikinas.mediana = ((laikinas.nd[laikinas.nd.size() / 2] + laikinas.nd[(laikinas.nd.size() / 2) - 1]) / 2.0) * 0.4 + laikinas.egz * 0.6;
         }

        // cout << abcas << endl;
        // splited.push_back(eil);



        // sarasas.push_back(laikinas);


        // isvedfailas(laikinas);

         //sarasas.clear();
    }
    else break;
}

*/
