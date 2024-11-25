#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype> // For isspace()

using namespace std;


string vector[3];




// Factorii de emisie
const double EMISIE_GAZE_NATURALE = 2.3; // kg CO2/m3
const double EMISIE_CURENT_ELECTRIC = 0.5; // kg CO2/kW
const double EMISIE_APA_CALDA = 0.0003; // kg CO2/litru
const double EMISIE_APA_RECE = 0.0001; // kg CO2/litru
const double EMISIE_LEMNE = 0.3; // kg CO2/kg
const double EMISIE_VEGAN = 1.5; // kg CO2/kg
const double EMISIE_VEGETARIAN = 2.5; // kg CO2/kg
const double EMISIE_OMNIVOR = 3.5; // kg CO2/kg
const double EMISIE_RESPIRATIE = 0.04 * 1.96 / 1000; // kg CO2/respirație
const double EMISIE_AUTO = 0.120; // kg CO2 per km pentru mașină personală
const double EMISIE_TRANSPORT_PUBLIC = 0.060; // kg CO2 per km pentru autobuz


enum TipTransport {
    MASINA_PERSONALA,
    TRANSPORT_COMUN
};

enum TipLocuinta {
    GARSONIERA,
    APARTAMENT,
    CASA
};

enum TipRegim {
    VEGAN,
    VEGETARIAN,
    OMNIVOR
};


// Clasă pentru casa de locuit
class Casa {
private:
    TipLocuinta tipLocuinta; // Tipul locuinței
    double spatiuUtil; // Metri pătrați
    double curentElectric; // kWh pe lună
    double gazeNaturale;   // m3 pe lună
    double apaCalda;       // litri pe lună
    double apaRece;        // litri pe lună
    double consumLemne;    // kg pe lună (doar pentru case cu încălzire pe lemne)

public:
    // Constructor
    Casa(TipLocuinta tipLocuinta, double spatiuUtil,
         double curentElectric, double gazeNaturale, double apaCalda, 
         double apaRece, double consumLemne = 0.0) 
         : tipLocuinta(tipLocuinta), spatiuUtil(spatiuUtil), 
           curentElectric(curentElectric), gazeNaturale(gazeNaturale), 
           apaCalda(apaCalda), apaRece(apaRece), consumLemne(consumLemne) {}

    // Calcul emisii din curent electric
    double emisiiCurentElectric() {
        return curentElectric * EMISIE_CURENT_ELECTRIC;
    }

    // Calcul emisii din gaze naturale
    double emisiiGazeNaturale() {
        return gazeNaturale * EMISIE_GAZE_NATURALE;
    }

    // Calcul emisii din lemne
    double emisiiLemne() {
        return consumLemne * EMISIE_LEMNE;
    }

    // Calcul emisii din apă caldă
    double emisiiApaCalda() {
        return apaCalda * EMISIE_APA_CALDA;
    }

    // Calcul emisii din apă rece
    double emisiiApaRece() {
        return apaRece * EMISIE_APA_RECE;
    }

    // Factor de ajustare pe baza tipului locuinței și a suprafeței utile
    double ajustareTipLocuinta(TipLocuinta tipLocuinta) {
        double factor = 1.0; // Valoare implicită

        switch (tipLocuinta) {
        case GARSONIERA:
            factor = 0.8; // Garsonierele au emisii mai mici
            break;
        case APARTAMENT:
            factor = 1.0; // Apartamentele au emisii medii
            break;
        case CASA:
            factor = 1.2; // Casele au emisii mai mari
            break;
        }
        return factor + (spatiuUtil / 100.0); // Ajustare suplimentară în funcție de spațiul util
    }

    // Calcul total emisii de carbon
    double calculAC() {
        double emisii = emisiiCurentElectric() + emisiiGazeNaturale() +
                        emisiiLemne() + emisiiApaCalda() + emisiiApaRece();

        // Ajustare pe baza tipului locuinței
        emisii *= ajustareTipLocuinta(this->tipLocuinta);

        return emisii * 12; // Calcul anual
    }
};

// Clasă pentru regimul alimentar
class RegimAlimentar {
private:
    TipRegim regim; // Regimul alimentar, acum este de tip enumerator

public:
    // Constructor
    RegimAlimentar(TipRegim regim) : regim(regim) {}

    // Calcul amprentă de carbon pentru regim alimentar
    double calculAC() {
        switch (regim) {
        case VEGAN:
            return EMISIE_VEGAN * 365; // Consum zilnic anualizat
        case VEGETARIAN:
            return EMISIE_VEGETARIAN * 365;
        case OMNIVOR:
            return EMISIE_OMNIVOR * 365;
        default:
            return 0.0; // Caz implicit (nu ar trebui să apară)
        }
    }
};

// Clasă pentru persoana individuală
class Persoana {
private:
    int respiratiiPeMinut;
    double kmTransport; // kilometri parcursi zilnic
    TipTransport tipTransport; // tipul de transport folosit

public:
    // Constructor
    Persoana(int respiratiiPeMinut, double kmTransport, TipTransport tipTransport) {
        this->respiratiiPeMinut = respiratiiPeMinut;
        this->kmTransport = kmTransport;
        this->tipTransport = tipTransport;
    }

    // Calcul amprenta de carbon pentru transport
    double transportAC() {
        double coeficientTransport = 0.0;

        // Alege coeficientul în funcție de tipul de transport
        if (tipTransport == MASINA_PERSONALA) {
            coeficientTransport = EMISIE_AUTO;
        } else if (tipTransport == TRANSPORT_COMUN) {
            coeficientTransport = EMISIE_TRANSPORT_PUBLIC;
        }

        return kmTransport * coeficientTransport * 12; // Calcul anual
    }

    // Calcul amprenta de carbon pentru respirație
    double calculAC() {
        return respiratiiPeMinut * 1440 * EMISIE_RESPIRATIE * 12; // Calcul anual
    }

    // Calcul total
    double calculTotalAC() {
        return calculAC() + transportAC();
    }
};

// // Function to trim leading and trailing spaces
// string trim(const string& str) {
//     size_t start = 0;
//     while (start < str.size() && isspace(str[start])) {
//         start++;
//     }

//     size_t end = str.size();
//     while (end > start && isspace(str[end - 1])) {
//         end--;
//     }

//     return str.substr(start, end - start);
// }

int main() {
    // ifstream fisier("dateamprentaco2.csv"); // Deschide fișierul CSV
    // if (!fisier.is_open()) { // Verifică dacă fișierul a fost deschis
    //     cerr << "Eroare: fișierul 'dateamprentaco.txt' nu a putut fi deschis!" << endl;
    //     return 1;
    // }

    // string linie; // Reține linia curentă
    // while (getline(fisier, linie)) { // Citește fișierul linie cu linie
    //     if (linie.empty()) {
    //         continue; // Ignoră liniile goale
    //     }

    //     stringstream linieStream(linie); // Creează un flux pentru procesarea liniei
    //     string valoare;
    //     while (getline(linieStream, valoare, ',')) { // Extrage fiecare valoare separată prin virgulă
    //         valoare = trim(valoare); // Trimite valoarea pentru a elimina spațiile suplimentare
    //         vector->append(valoare);
    //         cout << valoare << " "; // Afișează valoarea curentă
    //     }
    //     cout << endl; // Treci la o nouă linie după ce afișezi valorile unei linii
    // }

    //fisier.close(); // Închide fișierul

    int optiune;
    cout << "Calculul amprentei de carbon\n";
    cout << "1. Individual\n2. Casa de locuit\n3. Regim alimentar\nAlege optiunea: ";
    cin >> optiune;


    if (optiune == 1) {
        int respiratii;
        cout << "Cate respiratii pe minut ai (in medie)? ";
        cin >> respiratii;
        cout << "Cati km parcurgi zilnic? ";
        double kmTransport;
        cin >> kmTransport;
        cout << "Ce tip de transport folosesti (1 - masina personala, 2 - transport comun)? ";
        int tipTransport;
        cin >> tipTransport;
        TipTransport tipTransportEnum = (tipTransport == 1) ? MASINA_PERSONALA : TRANSPORT_COMUN;
        Persoana persoana(respiratii, kmTransport, tipTransportEnum);
        cout << "Amprenta ta de carbon (individuala) este: " << persoana.calculAC() << " kg CO2/an\n";
    } else if (optiune == 2) {

        cout << "Care este spațiul util al locuinței (în metri pătrați)? ";
        double spatiuUtil;
        cin >> spatiuUtil;
        int tipLocuinta;
        cout << "Care este tipul de locuință (1 - garsonieră, 2 - apartament, 3 - casă)? ";
        cin >> tipLocuinta;
        TipLocuinta tipLocuintaEnum = (tipLocuinta == 1) ? GARSONIERA : (tipLocuinta == 2) ? APARTAMENT : CASA;

        double curent, gaze;
        cout << "Cati kWh de curent electric folosesti pe luna? ";
        cin >> curent;
        cout << "Cati metri cubi de gaze naturale consumi pe luna? ";
        cin >> gaze;
        cout << "Cati litri de apa calda folosesti pe luna? ";
        double apaCalda;
        cin >> apaCalda;
        cout << "Cati litri de apa rece folosesti pe luna? ";
        double apaRece;
        cin >> apaRece;

        Casa casa(tipLocuintaEnum, spatiuUtil, curent, gaze, apaCalda, apaRece);
        cout << "Amprenta ta de carbon (casa de locuit) este: " << casa.calculAC() << " kg CO2/an\n";
    } else if (optiune == 3) {
        int dieta;
        cout << "Care este regimul tău alimentar (1 - vegan, 2 - vegetarian, 3 - omnivor)? ";
        cin >> dieta;

        // Mapează intrarea utilizatorului la enumerator
        TipRegim tipRegim = (dieta == 1) ? VEGAN : (dieta == 2) ? VEGETARIAN : OMNIVOR;

        // Creare obiect RegimAlimentar și calculare emisii
        RegimAlimentar regim(tipRegim);
        cout << "Amprenta ta de carbon (regim alimentar) este: " << regim.calculAC() << " kg CO2/an\n";
    } else {
        cout << "Optiune invalida.\n";
    }


    
    return 0;
}

