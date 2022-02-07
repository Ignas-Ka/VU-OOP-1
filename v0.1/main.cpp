#include <iostream>
#include <string>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;


struct data
{
    string vardas, pavarde;
    int egz;
    double vid;
    int paz[];
};

void ivestis(data* temp, int& pazymiuSk);

void isvestis(data* temp, int& pazymiuSk);

int main()
{
    struct data* duomenys = (struct data *)malloc(sizeof(struct data) + 50 * sizeof(int));
    duomenys = new data[3];
    int pazymiuSk = 0;
    ivestis(duomenys, pazymiuSk);
    isvestis(duomenys, pazymiuSk);


    return 0;
}


void ivestis(data* temp, int& pazymiuSk)
{
    int vidurkis = 0;
    for(int i = 0; i < 3; i++)
    {
        cout << "Iveskite varda ";
        cin >> temp[i].vardas;
        cout << "Iveskite pavarde ";
        cin >> temp[i].pavarde;
        cout << "Iveskite pazymiu skaiciu ";
        cin >> pazymiuSk;
        for(int j = 0; j < pazymiuSk; j++)
        {
            cout << "Iveskite " << i+1 << " -a(-i) pazymi ";
            cin >> temp[i].paz[j];
            vidurkis += temp[i].paz[j];
        }
        temp[i].vid = vidurkis/pazymiuSk;
        vidurkis = 0;
        cout << "Iveskite egzamino ivertinima ";
        cin >> temp[i].egz;
    }
}

void isvestis(data* temp, int& pazymiuSk)
{
    cout << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << endl;
    cout << "-----------------------------------------------------------------";
         for(int i = 0; i < 3; i++)
    {
        cout << setw(20) << temp[i].pavarde << setw(20) << temp[i].vardas << setw(20) << temp[i].vid << endl;
    }
}
