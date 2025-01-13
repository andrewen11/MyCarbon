#ifndef CARBON_CLASSES_H
#define CARBON_CLASSES_H

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

// Detailed vehicle emission factors (kg CO2/km)
namespace EmisieCombustibil {
constexpr double BENZINA = 0.120;    // Average gasoline car
constexpr double MOTORINA = 0.140;   // Average diesel car
constexpr double ELECTRICA = 0.050;  // Electric car (including power generation)
constexpr double GPL = 0.090;        // LPG car
}

// Detailed public transport emission factors (kg CO2/passenger-km)
namespace EmisieTransportPublic {
constexpr double TREN = 0.035;      // Train (electric)
constexpr double METROU = 0.028;    // Metro
constexpr double AUTOBUZ = 0.068;   // Bus (diesel)
constexpr double TROLEIBUZ = 0.025; // Trolleybus (electric)
constexpr double AVION = 0.285;     // Domestic flight
}

// Copiază enumerările

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

enum TipCombustibil {
    BENZINA,
    MOTORINA,
    ELECTRICA,
    GPL
};

enum TipTransportPublic {
    TREN,
    METROU,
    AUTOBUZ,
    TROLEIBUZ,
    AVION
};

enum TipTransport {
    MASINA_PERSONALA,
    TRANSPORT_COMUN,
    BICICLETA,
    TROTINETA
};

// Copiază clasele (Casa, RegimAlimentar, Persoana)
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

class Persoana {
public:
    Persoana(int breaths, double distance, TipTransport transport,
             TipCombustibil combustibil = TipCombustibil::BENZINA,
             TipTransportPublic transportPublic = TipTransportPublic::TREN)
        : m_breaths(breaths), m_distance(distance), m_transport(transport),
        m_combustibil(combustibil), m_transportPublic(transportPublic) {}

    double calculTotalAC() const {
        return calculAC() + transportAC();
    }

private:
    double transportAC() const {
        double coeficient = 0.0;

        if (m_transport == TipTransport::MASINA_PERSONALA) {
            switch (m_combustibil) {
            case TipCombustibil::BENZINA:
                coeficient = EmisieCombustibil::BENZINA;
                break;
            case TipCombustibil::MOTORINA:
                coeficient = EmisieCombustibil::MOTORINA;
                break;
            case TipCombustibil::ELECTRICA:
                coeficient = EmisieCombustibil::ELECTRICA;
                break;
            case TipCombustibil::GPL:
                coeficient = EmisieCombustibil::GPL;
                break;
            }
        } else if (m_transport == TipTransport::TRANSPORT_COMUN) {
            switch (m_transportPublic) {
            case TipTransportPublic::TREN:
                coeficient = EmisieTransportPublic::TREN;
                break;
            case TipTransportPublic::METROU:
                coeficient = EmisieTransportPublic::METROU;
                break;
            case TipTransportPublic::AUTOBUZ:
                coeficient = EmisieTransportPublic::AUTOBUZ;
                break;
            case TipTransportPublic::TROLEIBUZ:
                coeficient = EmisieTransportPublic::TROLEIBUZ;
                break;
            case TipTransportPublic::AVION:
                coeficient = EmisieTransportPublic::AVION;
                break;
            }
        }
        // Bicicleta și Trotineta au emisii 0

        // Calculăm emisiile anuale: km/zi * emisii/km * 365 zile
        return m_distance * coeficient * 365;
    }

    double calculAC() const {
        // Calculăm emisiile anuale din respirație:
        // respirații/min * 60 min * 24 ore * 365 zile * emisii/respirație
        return m_breaths * 60 * 24 * 365 * EMISIE_RESPIRATIE;
    }

    int m_breaths;
    double m_distance;
    TipTransport m_transport;
    TipCombustibil m_combustibil;
    TipTransportPublic m_transportPublic;
};

#endif // CARBON_CLASSES_H
