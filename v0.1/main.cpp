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
    int paz[3] = {0}, egz;
    double vid;
};

void ivestis(data& temp);

void isvestis(data& temp);

int main()
{
    data* duomenys = new data[2];
    for(data* a = duomenys; a < duomenys + 2; a++) {
        ivestis(*a);
    }

    for(data* a = duomenys; a < duomenys + 2; a++) {
        isvestis(*a);
    }

    delete[] duomenys;

    return 0;
}


void ivestis(data& temp)
{
    int vidurkis = 0;

    int pazymiuSk = 3;
    cout << "Iveskite varda ";
    cin >> temp.vardas;
    cout << "Iveskite pavarde ";
    cin >> temp.pavarde;
    for(int i = 0; i < pazymiuSk; i++)
    {
        cout << "Iveskite " << i+1 << " -a(-i) pazymi: ";
        cin >> temp.paz[i];
        vidurkis += temp.paz[i];
    }
    temp.vid = vidurkis/pazymiuSk;
    vidurkis = 0;
    cout << "Iveskite egzamino ivertinima ";
    cin >> temp.egz;


}

void isvestis(data& temp)
{
    cout << setw(20) << temp.pavarde << setw(20) << temp.vardas;
         for(int i = 0; i < 3; i++)
    {
        cout << setw(10) << temp.paz[i];
    }
    cout << setw(10) << temp.egz << endl;
}
