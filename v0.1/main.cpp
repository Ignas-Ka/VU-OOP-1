#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::setprecision;
using std::swap;

const int MAX_MOKINIU = 10;
const int PAZYMIU_SK = 4;

struct data
{
    string vardas, pavarde;
    int paz[PAZYMIU_SK] = {0}, egz;
    double vid;
};

void ivestis(data& temp);

void isvestis(data& temp);

bool isNumber(const string& str);

void bubbleSort(int arr[]);

double findMedian(int a[]);

int main()
{
    string arSustabdyti = "0";
    int index = 0;
    data* duomenys = new data[MAX_MOKINIU];

    for(data* a = duomenys; a < duomenys + MAX_MOKINIU; a++)
    {
        ivestis(*a);
        bubbleSort(&*a -> paz);
        cout << "Ar bus dar vienas mokinys? (0 - nebus /1 - bus )";
        cin >> arSustabdyti;
        if (arSustabdyti != "1")
        {
            break;
        }
        index++;

    }

//    for(int i = 0; i < PAZYMIU_SK; i++) {
//        cout << duomenys -> paz[i] << " ";
//    }
//    cout << endl;

    for(data* a = duomenys; a < duomenys + index + 1; a++)
    {
        isvestis(*a);
    }

    delete[] duomenys;

    return 0;
}

bool isNumber(const string& str)
{
    return !str.empty() &&
           std::find_if(str.begin(), str.end(),
                        [](unsigned char c)
    {
        return !std::isdigit(c);
    }) == str.end();
}

void ivestis(data& temp)
{
    string egzas = "0";
    double vidurkis = 0;
    string pazim = "0";

    cout << "Iveskite varda ";
    cin >> temp.vardas;
    cout << "Iveskite pavarde ";
    cin >> temp.pavarde;
    for(int i = 0; i < PAZYMIU_SK; i++)
    {
        while(!(isNumber(pazim)) || stoi(pazim) < 1 || stoi(pazim) > 10)
        {
            cout << "Iveskite " << i+1 << " -a(-i) pazymi: ";
            cin >> pazim;
        }
        temp.paz[i] = stoi(pazim);
        vidurkis += temp.paz[i];
        pazim = "0";
    }
    temp.vid = vidurkis/PAZYMIU_SK;
    vidurkis = 0;
    while(!(isNumber(egzas)) || stoi(egzas) < 1 || stoi(egzas) > 10)
    {
        cout << "Iveskite tinkama egzamino ivertinima ";
        cin >> egzas;
    }
    temp.egz = stoi(egzas);


}

void isvestis(data& temp)
{
    int medArVid = 0;

    cout << setw(20) << temp.pavarde << setw(20) << temp.vardas;
    for(int i = 0; i < PAZYMIU_SK; i++)
    {
        cout << setw(5) << temp.paz[i];
    }
    cout << setw(10) << temp.egz;
    cout << endl;
    cout << "Mediana(0) ar vidurkis(1) ";
    cin >> medArVid;
    if (medArVid == 1) {
        cout << setw(10) << setprecision(3) << temp.vid << endl;
    }
    else {
        cout << setw(10) << setprecision(3) << findMedian(temp.paz) << endl;
    }
}

void bubbleSort(int arr[])
{
    for (int i = 0; i < PAZYMIU_SK-1; i++)
    {
        for (int j = 0; j < PAZYMIU_SK-i-1; j++)
        {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

double findMedian(int a[])
{
    if (PAZYMIU_SK % 2 != 0) {
        return (double)a[PAZYMIU_SK / 2];
    }

    return (double)(a[(PAZYMIU_SK - 1) / 2] + a[PAZYMIU_SK / 2]) / 2.0;
}
