#include "Crow/include/crow.h" // Trebuie instalat Crow framework: https://github.com/CrowCpp/Crow
#include "json.hpp" // Trebuie instalat nlohmann/json: https://github.com/nlohmann/json
#include "calculator_original.hpp" // Codul tău original
#include <string>

using json = nlohmann::json;
using namespace std;

int main() {
    crow::SimpleApp app;

    // Activare CORS pentru toate rutele
    app.after_handle([](crow::response& res) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
    });

    // Ruta pentru calculul individual
    CROW_ROUTE(app, "/calculate/individual").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        auto requestData = json::parse(req.body);
        
        // Extrage datele din request
        int respiratii = requestData["respiratii"].get<int>();
        double kmTransport = requestData["kmTransport"].get<double>();
        bool isMasina = requestData["isMasina"].get<bool>();
        
        // Creează obiectul Persoana și calculează
        Persoana persoana(respiratii, kmTransport, isMasina ? MASINA_PERSONALA : TRANSPORT_COMUN);
        
        // Pregătește răspunsul JSON
        json response;
        response["respiratii"] = persoana.calculAC();
        response["transport"] = persoana.transportAC();
        response["total"] = persoana.calculTotalAC();
        
        return crow::response{response.dump()};
    });

    // Ruta pentru calculul casei
    CROW_ROUTE(app, "/calculate/casa").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        auto requestData = json::parse(req.body);
        
        // Extrage datele din request
        string tipLocuintaStr = requestData["tipLocuinta"].get<string>();
        TipLocuinta tipLocuinta;
        if (tipLocuintaStr == "garsoniera") tipLocuinta = GARSONIERA;
        else if (tipLocuintaStr == "apartament") tipLocuinta = APARTAMENT;
        else tipLocuinta = CASA;
        
        double spatiuUtil = requestData["spatiuUtil"].get<double>();
        double curentElectric = requestData["curentElectric"].get<double>();
        double gazeNaturale = requestData["gazeNaturale"].get<double>();
        double apaCalda = requestData["apaCalda"].get<double>();
        double apaRece = requestData["apaRece"].get<double>();
        
        // Creează obiectul Casa și calculează
        Casa casa(tipLocuinta, spatiuUtil, curentElectric, gazeNaturale, apaCalda, apaRece);
        
        // Pregătește răspunsul JSON
        json response;
        response["curentElectric"] = casa.emisiiCurentElectric();
        response["gazeNaturale"] = casa.emisiiGazeNaturale();
        response["apaCalda"] = casa.emisiiApaCalda();
        response["apaRece"] = casa.emisiiApaRece();
        response["total"] = casa.calculAC();
        
        return crow::response{response.dump()};
    });

    // Ruta pentru calculul regimului alimentar
    CROW_ROUTE(app, "/calculate/regim").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        auto requestData = json::parse(req.body);
        
        // Extrage datele din request
        string regimStr = requestData["regim"].get<string>();
        TipRegim regim;
        if (regimStr == "vegan") regim = VEGAN;
        else if (regimStr == "vegetarian") regim = VEGETARIAN;
        else regim = OMNIVOR;
        
        // Creează obiectul RegimAlimentar și calculează
        RegimAlimentar regimAlimentar(regim);
        
        // Pregătește răspunsul JSON
        json response;
        response["total"] = regimAlimentar.calculAC();
        
        return crow::response{response.dump()};
    });

    // Pornește serverul pe portul 3000
    app.port(3000)
        .multithreaded()
        .run();

    return 0;
}
