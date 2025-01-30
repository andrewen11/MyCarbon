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
const double EMISIE_RESPIRATIE = 0.0005 * 0.04 * 1.96; // kg CO2/respirație calculat astfel: volum CO2 inspirat * concentratia * densitatea CO2
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

// Waste Emission Factors (kg CO2 per kg waste)
const double EMISIE_GUNOI_DEPONIE = 1.3;     // Landfill
const double EMISIE_GUNOI_INCINERARE = 2.5; // Incineration
const double EMISIE_GUNOI_RECICLARE = 0.2;  // Recycling
const double EMISIE_GUNOI_COMPOST = 0.1;    // Composting


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
    TROTINETA,
    MERS_PE_JOS
};

#include <vector>
#include <QDebug>
#include <QMap>
#include <QString>
#include <cmath>
// Copiază clasele (Casa, RegimAlimentar, Persoana)
// Definim factorii pentru fiecare țară
// Factori de emisie specifici fiecărei țări (kg CO2 per unitate)
struct FactoriEmisie {
    double electricitate; // kg CO2/kWh
    double gaze;         // kg CO2/m³
    double lemne;        // kg CO2/kg
};

const QMap<QString, FactoriEmisie> FACTORI_EMISIE_TARI = {
    {"Romania", {0.35, 2.3, 1.8}},
    {"Portugal", {0.22, 2.1, 1.7}},
    {"Spain", {0.25, 2.2, 1.6}},
    {"Ukraine", {0.45, 2.5, 2.0}}
};

class Casa {
private:
    double curentElectric;
    double gazeNaturale;
    double consumLemne;
    double spatiuUtil;
    int numPersoane;
    QString tara;
    QString tipLocuinta;
    FactoriEmisie factori;

public:
    Casa(double curentElectric, double gazeNaturale, double consumLemne, double spatiuUtil, int numPersoane, QString tipLocuinta, FactoriEmisie factori)
        : curentElectric(curentElectric), gazeNaturale(gazeNaturale), consumLemne(consumLemne),
        spatiuUtil(spatiuUtil), numPersoane(numPersoane), tipLocuinta(tipLocuinta), factori(factori) {}

    double emisiiCurentElectric() {
        double factorLocuinta = (tipLocuinta == "Studio") ? 0.8 : (tipLocuinta == "Apartment") ? 1.0 : 1.2;
        double factorSpatiu = sqrt(spatiuUtil / 100.0); // Sublinear scaling for electricity
        return (curentElectric * factori.electricitate * factorSpatiu * factorLocuinta) / numPersoane;
    }

    double emisiiGazeNaturale() {
        double factorLocuinta = (tipLocuinta == "Studio") ? 0.8 : (tipLocuinta == "Apartment") ? 1.0 : 1.2;
        double factorSpatiu = sqrt(spatiuUtil / 100.0); // Gas consumption grows with space
        return (gazeNaturale * factori.gaze * factorSpatiu * factorLocuinta) / numPersoane;
    }

    double emisiiLemne() {
        double factorLocuinta = (tipLocuinta == "Studio") ? 0.8 : (tipLocuinta == "Apartment") ? 1.0 : 1.2;
        double factorSpatiu = sqrt(spatiuUtil / 100.0); // Sublinear scaling for heating sources
        return (consumLemne * factori.lemne * factorLocuinta * factorSpatiu) / numPersoane;
    }

    double calculAC() {
        double emisii = emisiiCurentElectric() + emisiiGazeNaturale() + emisiiLemne();
        return emisii * 12; // Annual emissions
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
    Persoana(int breaths, std::vector<double> distances,
             std::vector<TipTransport> transports,
             std::vector<TipCombustibil> combustibili,
             std::vector<TipTransportPublic> transportPublics,
             QMap<QString, double> wasteAmounts,
             QMap<QString, QString> wasteMethods)
        : m_breaths(breaths), m_distances(std::move(distances)),
        m_transports(std::move(transports)), m_combustibili(std::move(combustibili)),
        m_transportPublics(std::move(transportPublics)),
        m_wasteAmounts(std::move(wasteAmounts)), m_wasteMethods(std::move(wasteMethods)) {}

    double calculTotalAC() const {
        qDebug() << "Inside calculTotalAC...";
        double acBreaths = calculAC();
        qDebug() << "Breathing Carbon Footprint: " << acBreaths;
        double acTransport = transportAC();
        qDebug() << "Transport Carbon Footprint: " << acTransport;
        double acWaste = wasteAC();
        qDebug() << "Waste Carbon Footprint: " << acWaste;
        double total = acBreaths + acTransport + acWaste;
        qDebug() << "Total Carbon Footprint: " << total;
        return total;
    }

private:
    double transportAC() const {
        double totalEmissions = 0.0;
        size_t fuelIndex = 0;
        size_t publicTransportIndex = 0;

        for (size_t i = 0; i < m_transports.size(); ++i) {
            double coeficient = 0.0;
            double distance = (i < m_distances.size()) ? m_distances[i] : 0.0; // 🛠️ Fix: Folosim distanța corespunzătoare

            if (m_transports[i] == MASINA_PERSONALA) {
                if (fuelIndex >= m_combustibili.size()) {
                    qWarning() << "🚨 Error: Missing fuel for Personal Car at index" << fuelIndex;
                    continue;
                }
                coeficient = getCombustibilEmission(m_combustibili[fuelIndex]);
                fuelIndex++;
            }
            else if (m_transports[i] == TRANSPORT_COMUN) {
                if (publicTransportIndex >= m_transportPublics.size()) {
                    qWarning() << "🚨 Error: Missing public transport type at index" << publicTransportIndex;
                    continue;
                }
                coeficient = getTransportPublicEmission(m_transportPublics[publicTransportIndex]);
                publicTransportIndex++;
            }

            totalEmissions += coeficient * distance * 12; // 🔥 Fix: Multiplicăm cu distanța introdusă de utilizator
        }

        return totalEmissions;
    }

    double getCombustibilEmission(TipCombustibil combustibil) const {
        switch (combustibil) {
        case BENZINA: return EmisieCombustibil::BENZINA;
        case MOTORINA: return EmisieCombustibil::MOTORINA;
        case ELECTRICA: return EmisieCombustibil::ELECTRICA;
        case GPL: return EmisieCombustibil::GPL;
        default: return 0.0;
        }
    }

    double getTransportPublicEmission(TipTransportPublic transportPublic) const {
        switch (transportPublic) {
        case TREN: return EmisieTransportPublic::TREN;
        case METROU: return EmisieTransportPublic::METROU;
        case AUTOBUZ: return EmisieTransportPublic::AUTOBUZ;
        case TROLEIBUZ: return EmisieTransportPublic::TROLEIBUZ;
        case AVION: return EmisieTransportPublic::AVION;
        default: return 0.0;
        }
    }

    double wasteAC() const {
        double totalWasteEmissions = 0.0;
        for (auto it = m_wasteAmounts.begin(); it != m_wasteAmounts.end(); ++it) {
            QString wasteType = it.key();
            double amount = it.value();
            QString method = m_wasteMethods[wasteType];

            double factor = 0.0;
            if (method == "Landfill") factor = EMISIE_GUNOI_DEPONIE;
            else if (method == "Incineration") factor = EMISIE_GUNOI_INCINERARE;
            else if (method == "Recycling") factor = EMISIE_GUNOI_RECICLARE;
            else if (method == "Composting") factor = EMISIE_GUNOI_COMPOST;

            totalWasteEmissions += factor * amount * 12;
        }
        return totalWasteEmissions;
    }

    double calculAC() const {
        return m_breaths * 60 * 24 * 365 * EMISIE_RESPIRATIE;
    }

    int m_breaths;
    std::vector<double> m_distances;  // 🆕 Adăugat pentru distanțele pe fiecare tip de transport
    std::vector<TipTransport> m_transports;
    std::vector<TipCombustibil> m_combustibili;
    std::vector<TipTransportPublic> m_transportPublics;
    QMap<QString, double> m_wasteAmounts;
    QMap<QString, QString> m_wasteMethods;
};



#endif // CARBON_CLASSES_H
