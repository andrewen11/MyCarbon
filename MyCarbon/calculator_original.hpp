#ifndef CARBON_CALCULATOR_HPP
#define CARBON_CALCULATOR_HPP

#include <string>

// Factorii de emisie (declarați extern pentru utilizare globală)
extern const double EMISIE_GAZE_NATURALE;
extern const double EMISIE_CURENT_ELECTRIC;
extern const double EMISIE_APA_CALDA;
extern const double EMISIE_APA_RECE;
extern const double EMISIE_LEMNE;
extern const double EMISIE_VEGAN;
extern const double EMISIE_VEGETARIAN;
extern const double EMISIE_OMNIVOR;
extern const double EMISIE_RESPIRATIE;
extern const double EMISIE_AUTO;
extern const double EMISIE_TRANSPORT_PUBLIC;

enum TipTransport
{
    MASINA_PERSONALA,
    TRANSPORT_COMUN
};

enum TipLocuinta
{
    GARSONIERA,
    APARTAMENT,
    CASA
};

enum TipRegim
{
    VEGAN,
    VEGETARIAN,
    OMNIVOR
};

// Clasă pentru casa de locuit
class Casa
{
private:
    TipLocuinta tipLocuinta;
    double spatiuUtil;
    double curentElectric;
    double gazeNaturale;
    double apaCalda;
    double apaRece;
    double consumLemne;

public:
    Casa(TipLocuinta tipLocuinta, double spatiuUtil, double curentElectric,
         double gazeNaturale, double apaCalda, double apaRece, double consumLemne = 0.0);
    double emisiiCurentElectric();
    double emisiiGazeNaturale();
    double emisiiLemne();
    double emisiiApaCalda();
    double emisiiApaRece();
    double ajustareTipLocuinta(TipLocuinta tipLocuinta);
    double calculAC();
};

// Clasă pentru regimul alimentar
class RegimAlimentar
{
private:
    TipRegim regim;

public:
    RegimAlimentar(TipRegim regim);
    double calculAC();
};

// Clasă pentru persoana individuală
class Persoana
{
private:
    int respiratiiPeMinut;
    double kmTransport;
    TipTransport tipTransport;

public:
    Persoana(int respiratiiPeMinut, double kmTransport, TipTransport tipTransport);
    double transportAC();
    double calculAC();
    double calculTotalAC();
};

#endif // CARBON_CALCULATOR_H_
