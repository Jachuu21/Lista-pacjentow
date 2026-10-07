#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
struct Wezel{
    string ImieNazwisko;
    string pesel;
    string data;

    Wezel * nextalfabetycznie = nullptr;
    Wezel * nextwiekiem = nullptr;
    Wezel * nextwizytami = nullptr;
};
bool sprawdzam_datami(const string a, const string b)
{
    if(a<b) return true;
    else return false;
}
void sortowanie_data(Wezel * nowy, Wezel *& glowa_daty)
{
    Wezel ** ptr = &glowa_daty;
    while(*ptr){
        bool comp = false;
        comp = sprawdzam_datami(nowy->data, (*ptr)->data);
        if(comp == true) break;
        ptr = &(*ptr)->nextwizytami;
    }
    nowy->nextwizytami= *ptr;
    *ptr = nowy;
}
bool sprawdzam_wiekiem(const string a, const string b)
{
    if(a<b) return true;
    else return false;
}
void sortowanie_wiekiem(Wezel * nowy, Wezel *& glowa_wiek)
{
    Wezel ** ptr = &glowa_wiek;
    while(*ptr){
        bool comp = false;
        comp = sprawdzam_wiekiem(nowy->pesel, (*ptr)->pesel);
        if(comp == true) break;
        ptr = &(*ptr)->nextwiekiem;
    }
    nowy->nextwiekiem = *ptr;
    *ptr = nowy;
}
bool sprawdzam_alfabetycznie(const string a, const string b) 
{
    if(a<b) return true;
    else return false;
}
void sortowanie_alfabetyczne(Wezel * nowy, Wezel *& glowa_alfa)
{
    Wezel ** ptr = &glowa_alfa;
    while(*ptr){
        bool comp = false;
        comp = sprawdzam_alfabetycznie(nowy->ImieNazwisko, (*ptr)->ImieNazwisko);
        if(comp==true) break;
        ptr=&(*ptr)->nextalfabetycznie;
    }
    nowy->nextalfabetycznie = *ptr;
    *ptr = nowy; 
}
void dodaj(string data, string pesel, string ImieNazwisko, Wezel *& glowa_alfa, Wezel *& glowa_wiek, Wezel *& glowa_daty)
{
    Wezel * nowy = new Wezel{ImieNazwisko, pesel, data};
    bool info = false;
    Wezel* temp = glowa_alfa;
    while(temp){
        if(data==temp->data){
            cout << "Termin zajęty: " << data << endl; 
            info = true;
        }
        temp=temp->nextalfabetycznie;
    }
    if(info==false){
        sortowanie_alfabetyczne(nowy, glowa_alfa);
        sortowanie_wiekiem(nowy, glowa_wiek);
        sortowanie_data(nowy, glowa_daty);  
    }
    
}
void usuwanie_wizyt(string data, Wezel *& glowa_daty)
{
    Wezel ** ptr = &glowa_daty;
    bool znajdz = false;
    while(*ptr){
        if(data==(*ptr)->data){
            *ptr = (*ptr)->nextwizytami;
            znajdz = true;
            break;
        }
        ptr = &(*ptr)->nextwizytami;

    }
    if(znajdz==false){
        cout << "Wizyta nie znaleziona: " << data << endl;
    }
}
void wypisz_alfabetycznie(Wezel * glowa_alfa)
{
    cout << "Lista alfabetycznie:\n";
    int nr = 1;
    while(glowa_alfa){
        cout << nr << " | " << glowa_alfa->data << " | " << glowa_alfa->pesel << " | " << glowa_alfa->ImieNazwisko << endl;
        glowa_alfa = glowa_alfa->nextalfabetycznie;
        nr++;
    }

}
void wypisz_wiekiem(Wezel * glowa_wiek)
{
    cout << "Lista wiekiem:\n";
    int nr = 1;
    while(glowa_wiek){
        cout << nr << " | " << glowa_wiek->data << " | " << glowa_wiek->pesel << " | " << glowa_wiek->ImieNazwisko << endl;
        glowa_wiek = glowa_wiek->nextwiekiem;
        nr++;
    }
}
void wypisz_wizytami(Wezel * glowa_daty)
{
    cout << "Lista wizytami:\n"; 
    int nr = 1;
    while(glowa_daty){
        cout << nr << " | " << glowa_daty->data << " | " << glowa_daty->pesel << " | " << glowa_daty->ImieNazwisko << endl;
        glowa_daty = glowa_daty->nextwizytami;
        nr++;
    }
}
int main()
{
    Wezel* glowa_alfa = nullptr;
    Wezel* glowa_wiek = nullptr;
    Wezel* glowa_daty = nullptr;
    ifstream plik;
    plik.open("komendy.txt", ios::binary);
    //if(plik.is_open()) cout << "PLIK ZOSTAŁ OTWORZONY :)" << endl;
    //else cout << "NIE UDAŁO SIĘ OTWORZYĆ PLIKU!" << endl;
    string linia;
    while(getline(plik, linia)){
        stringstream ss(linia);
        string komenda;
        ss>>komenda;
        if(komenda == "dodaj"){
            string data, godzina, pesel, ImieNazwisko;
            ss>>data >> godzina >> pesel;
            if(pesel.length()<11){
                cout << "Nieprawidłowy PESEL: " << pesel << endl;
            }
            else{
                getline(ss >> ws, ImieNazwisko);
                dodaj(data + " " + godzina, pesel, ImieNazwisko, glowa_alfa, glowa_wiek, glowa_daty);
            }
            
        }
        else if(komenda == "usuń"){
            string data, godzina;
            ss >> data >> godzina;
            usuwanie_wizyt(data + " " + godzina, glowa_daty);
        }
        else if(komenda == "wypisz"){
            string typ;
            ss>>typ;
            if(typ=="alfabetycznie"){
                wypisz_alfabetycznie(glowa_alfa);
            }
            else if(typ=="wiekiem"){
                wypisz_wiekiem(glowa_wiek);
            }
            else{
                wypisz_wizytami(glowa_daty);
            }
            
        }
        
        
        
    }
    plik.close();
    
    
    
    
    
    return 0;
}
