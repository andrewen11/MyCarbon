// mainwindow.cpp
#include "mainwindow.h"
#include "carbon_classes.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("Carbon Footprint Calculator");
    setMinimumSize(1000, 600);

    // Creăm un QLabel pentru fundal
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width(), height());

    // Încărcăm imaginea
    originalBackground = QPixmap(":/images/logo.png"); // Salvăm imaginea originală
    if (!originalBackground.isNull()) {
        updateBackground(); // Apelăm funcția pentru a seta fundalul inițial
    }

    backgroundLabel->lower(); // Asigură-te că fundalul este în spate

    backButton = new QPushButton("Back", this);
    backButton->setFixedSize(70, 38);
    backButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"  // Fundal transparent
        "    color: #4CAF50;"  // Text negru
        "    border: 1px solid #4CAF50;"  // Border negru de 2px
        "    font-size: 16px;"
        "    border-radius: 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #4CAF50;"  // Fundal verde la hover
        "    color: white;"  // Text alb la hover
        "}"
    );

    int buttonX = 10;
    int buttonY = backButton->height() - 25;
    backButton->move(buttonX, buttonY);
    backButton->raise();
    connect(backButton, &QPushButton::clicked, this, &MainWindow::backToStart);
    // Aplicăm un stylesheet global pentru MainWindow
    this->setStyleSheet(
        "QMainWindow {"
        "    background-color: #e8f5e9;"  // Fundal deschis verde
        "    color: #2e7d32;"  // Text verde închis
        "}"
        "QPushButton {"
        "    background-color: #4caf50;"
        "    border: none;"
        "    color: white;"
        "    font-size: 14px;"
        "    padding: 10px;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #388e3c;"
        "}"
        "QLabel {"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    color: #2e7d32;"
        "}"
        "QLineEdit {"
        "    background-color: white;"  // Fundal alb pentru QLineEdit
        "    color: black;"  // Text negru
        "    border: 1px solid #a5d6a7;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 14px;"
        "}"
        "QComboBox {"
        "    background-color: white;"  // Fundal alb pentru QComboBox
        "    color: black;"  // Text negru
        "    border: 1px solid #a5d6a7;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 14px;"
        "}"
        );
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Creăm un titlu frumos pentru aplicație
    QLabel *titleLabel = new QLabel("Carbon Footprint Calculator", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");

    mainLayout->addWidget(titleLabel);

    // Layout pentru butoane
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *individualButton = new QPushButton("Individual", this);
    QPushButton *houseButton = new QPushButton("Home", this);
    QPushButton *dietButton = new QPushButton("Diet", this);

    buttonLayout->addWidget(individualButton);
    buttonLayout->addWidget(houseButton);
    buttonLayout->addWidget(dietButton);

    mainLayout->addLayout(buttonLayout);

    // Creăm widget-ul pentru pagini
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(createIndividualPage());
    stackedWidget->addWidget(createHousePage());
    stackedWidget->addWidget(createDietPage());

    mainLayout->addWidget(stackedWidget);

    // Conectăm semnalele
    connect(individualButton, &QPushButton::clicked, this, &MainWindow::showIndividualPage);
    connect(houseButton, &QPushButton::clicked, this, &MainWindow::showHousePage);
    connect(dietButton, &QPushButton::clicked, this, &MainWindow::showDietPage);

    setCentralWidget(centralWidget);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground(); // Actualizăm fundalul la redimensionare
    // Repoziționăm butonul în centrul de jos
    int buttonX = 10;
    int buttonY = backButton->height() - 25; // Poziția normală

    // Ridicăm butonul cu 15-20 px în modul fullscreen
    if (isFullScreen()) {
        buttonY -= 30; // Ridică butonul cu 15 px
    }

    backButton->move(buttonX, buttonY);
    backButton->raise();
}

void MainWindow::updateBackground()
{
    if (!originalBackground.isNull() && backgroundLabel) {
        // Scalăm imaginea păstrând aspect ratio
        QPixmap scaledBackground = originalBackground.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Aplicăm opacitate folosind QPainter
        QPixmap transparentBackground(scaledBackground.size());
        transparentBackground.fill(Qt::transparent);
        QPainter painter(&transparentBackground);
        painter.setOpacity(0.5); // Setează opacitatea (0.0 complet transparent, 1.0 complet opac)
        painter.drawPixmap(0, 0, scaledBackground);
        painter.end();

        backgroundLabel->setPixmap(transparentBackground);

        // Calculăm poziționarea pentru centrare
        int xOffset = (width() - scaledBackground.width()) / 2;
        int yOffset = (height() - scaledBackground.height()) / 2;
        backgroundLabel->setGeometry(xOffset, yOffset, scaledBackground.width(), scaledBackground.height());
    }
}

QWidget* MainWindow::createIndividualPage() {
    individualPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(individualPage);

    // Elemente
    breathsEdit = new QLineEdit();
    distanceEdit = new QLineEdit();

    transportTypeCombo = new QComboBox();
    transportTypeCombo->addItem("(Select option)"); // Element gol
    transportTypeCombo->addItems({"Personal Car", "Public Transportation", "Bicycle", "Scooter"});

    // ComboBox pentru selectarea tipului de combustibil/transport public (vizibil doar pentru anumite tipuri de transport)
    fuelTypeCombo = new QComboBox();
    fuelTypeCombo->addItem("(Choose the fuel type of your car)"); // Element gol
    fuelTypeCombo->addItems({"Gasoline", "Diesel", "Electric", "LPG"});
    fuelTypeCombo->setVisible(false);  // Inițial ascuns

    publicTransportCombo = new QComboBox();
    publicTransportCombo->addItem("(Choose your public transportation method)"); // Element gol
    publicTransportCombo->addItems({"Train", "Metro", "Bus", "Trolleybus", "Airplane"});
    publicTransportCombo->setVisible(false);  // Inițial ascuns

    individualResultLabel = new QLabel();

    QGroupBox *groupBox = new QGroupBox("Individual Details");
    QVBoxLayout *groupLayout = new QVBoxLayout();

    groupLayout->addWidget(new QLabel("Breaths per minute:"));
    groupLayout->addWidget(breathsEdit);
    groupLayout->addWidget(new QLabel("Daily traveled distance (kilometers):"));
    groupLayout->addWidget(distanceEdit);
    groupLayout->addWidget(new QLabel("Transport type:"));
    groupLayout->addWidget(transportTypeCombo);
    groupLayout->addWidget(fuelTypeCombo);   // Adăugăm comboBox-ul pentru combustibil
    groupLayout->addWidget(publicTransportCombo); // Adăugăm comboBox-ul pentru transport public

    groupBox->setLayout(groupLayout);

    QPushButton *calculateButton = new QPushButton("Calculate");
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateIndividual);

    // Conectăm schimbarea tipului de transport pentru a arăta/ascunde opțiunile de combustibil/transport public
    connect(transportTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onTransportTypeChanged);

    layout->addWidget(groupBox);
    layout->addWidget(calculateButton);
    layout->addWidget(individualResultLabel);
    layout->addStretch();

    return individualPage;
}

void MainWindow::onTransportTypeChanged(int index) {
    if (index == 1) {  // Mașină personală
        fuelTypeCombo->setVisible(true);
        publicTransportCombo->setVisible(false);
    } else if (index == 2) {  // Transport comun
        fuelTypeCombo->setVisible(false);
        publicTransportCombo->setVisible(true);
    } else {  // Bicicletă sau Trotinetă
        fuelTypeCombo->setVisible(false);
        publicTransportCombo->setVisible(false);
    }
}

void MainWindow::calculateIndividual() {
    if (transportTypeCombo->currentIndex() == 0) { // Dacă nu este selectat un tip de transport
        QMessageBox::warning(this, "Error", "Please select a transport method!");
        return;
    }
    bool ok1, ok2;
    int breaths = breathsEdit->text().toInt(&ok1);
    double distance = distanceEdit->text().toDouble(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Error", "Please insert numbers in all the fields!");
        return;
    }

    if (breaths < 0 || distance < 0) {
        QMessageBox::warning(this, "Error", "Please insert positive numbers in all the fields!");
        return;
    }


    TipTransport transport;
    TipCombustibil combustibil = BENZINA;
    TipTransportPublic transportPublic = TREN;

    if (transportTypeCombo->currentIndex() == 1) {  // Mașină personală
        transport = MASINA_PERSONALA;
        switch(fuelTypeCombo->currentIndex()) {
        case 0: QMessageBox::warning(this, "Error", "Please select a fuel type!");
                return;
        case 1: combustibil = BENZINA; break;
        case 2: combustibil = MOTORINA; break;
        case 3: combustibil = ELECTRICA; break;
        case 4: combustibil = GPL; break;
        }
    } else if (transportTypeCombo->currentIndex() == 2) {  // Transport comun
        transport = TRANSPORT_COMUN;
        switch(publicTransportCombo->currentIndex()) {
        case 0: QMessageBox::warning(this, "Error", "Please select a public transportation method!");
                return;
        case 1: transportPublic = TREN; break;
        case 2: transportPublic = METROU; break;
        case 3: transportPublic = AUTOBUZ; break;
        case 4: transportPublic = TROLEIBUZ; break;
        case 5: transportPublic = AVION; break;
        }
    } else if (transportTypeCombo->currentIndex() == 3) {  // Bicicletă
        transport = BICICLETA;
    } else {  // Trotinetă
        transport = TROTINETA;
    }

    Persoana persoana(breaths, distance, transport, combustibil, transportPublic);
    double result = persoana.calculTotalAC();
    individualResultLabel->setText(QString("Carbon Footprint: %1 kg CO2/year").arg(result, 0, 'f', 2));
}

QWidget* MainWindow::createHousePage() {
    housePage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(housePage);

    spaceEdit = new QLineEdit();
    houseTypeCombo = new QComboBox();
    houseTypeCombo->addItem("(Select Option)");
    houseTypeCombo->addItems({"Studio", "Apartment", "House"});
    electricityEdit = new QLineEdit();
    gasEdit = new QLineEdit();
    hotWaterEdit = new QLineEdit();
    coldWaterEdit = new QLineEdit();
    houseResultLabel = new QLabel();

    QGroupBox *groupBox = new QGroupBox("Housing Details");
    QVBoxLayout *groupLayout = new QVBoxLayout();

    groupLayout->addWidget(new QLabel("Usable space (m²):"));
    groupLayout->addWidget(spaceEdit);
    groupLayout->addWidget(new QLabel("Type of housing:"));
    groupLayout->addWidget(houseTypeCombo);
    groupLayout->addWidget(new QLabel("Electricity consumption (kWh/month):"));
    groupLayout->addWidget(electricityEdit);
    groupLayout->addWidget(new QLabel("Natural gas consumption (m³/month):"));
    groupLayout->addWidget(gasEdit);
    groupLayout->addWidget(new QLabel("Hot water consumtipon (liters/month):"));
    groupLayout->addWidget(hotWaterEdit);
    groupLayout->addWidget(new QLabel("Cold water consumption (liters/month):"));
    groupLayout->addWidget(coldWaterEdit);

    groupBox->setLayout(groupLayout);

    QPushButton *calculateButton = new QPushButton("Calculate");
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateHouse);

    layout->addWidget(groupBox);
    layout->addWidget(calculateButton);
    layout->addWidget(houseResultLabel);
    layout->addStretch();

    return housePage;
}

QWidget* MainWindow::createDietPage() {
    dietPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(dietPage);

    dietTypeCombo = new QComboBox();
    dietTypeCombo->addItem("(Select Option)");
    dietTypeCombo->addItems({"Vegan", "Vegetarian", "Omnivore"});
    dietResultLabel = new QLabel();

    QGroupBox *groupBox = new QGroupBox("Diet");
    QVBoxLayout *groupLayout = new QVBoxLayout();

    groupLayout->addWidget(new QLabel("Diet type:"));
    groupLayout->addWidget(dietTypeCombo);

    groupBox->setLayout(groupLayout);

    QPushButton *calculateButton = new QPushButton("Calculate");
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateDiet);

    layout->addWidget(groupBox);
    layout->addWidget(calculateButton);
    layout->addWidget(dietResultLabel);
    layout->addStretch();

    return dietPage;
}

void MainWindow::showIndividualPage() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showHousePage() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showDietPage() {
    stackedWidget->setCurrentIndex(2);
}

/*void MainWindow::calculateIndividual() {
    bool ok1, ok2;
    int breaths = breathsEdit->text().toInt(&ok1);
    double distance = distanceEdit->text().toDouble(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Eroare", "Vă rugăm introduceți valori numerice valide!");
        return;
    }

    TipTransport transport = transportTypeCombo->currentIndex() == 0 ? MASINA_PERSONALA : TRANSPORT_COMUN;
    Persoana persoana(breaths, distance, transport);

    double result = persoana.calculTotalAC();
    individualResultLabel->setText(QString("Amprenta de carbon: %1 kg CO2/an").arg(result, 0, 'f', 2));
}*/

void MainWindow::calculateHouse() {
    if (houseTypeCombo->currentIndex() == 0) { // Dacă nu este selectat un tip de locuință
        QMessageBox::warning(this, "Error", "Please slect a housing type!");
        return;
    }
    bool ok[6];
    double space = spaceEdit->text().toDouble(&ok[0]);
    double electricity = electricityEdit->text().toDouble(&ok[1]);
    double gas = gasEdit->text().toDouble(&ok[2]);
    double hotWater = hotWaterEdit->text().toDouble(&ok[3]);
    double coldWater = coldWaterEdit->text().toDouble(&ok[4]);

    if (!ok[0] || !ok[1] || !ok[2] || !ok[3] || !ok[4]) {
        QMessageBox::warning(this, "Error", "Please insert numbers in all the fields!");
        return;
    }

    if (space < 0 || electricity < 0 || gas < 0 || hotWater < 0 || coldWater < 0) {
        QMessageBox::warning(this, "Error", "Please insert positive numbers in all the fields!");
        return;
    }

    TipLocuinta tipLocuinta;
    switch(houseTypeCombo->currentIndex()) {
    case 1: tipLocuinta = GARSONIERA; break;
    case 2: tipLocuinta = APARTAMENT; break;
    default: tipLocuinta = CASA;
    }

    Casa casa(tipLocuinta, space, electricity, gas, hotWater, coldWater);
    double result = casa.calculAC();
    houseResultLabel->setText(QString("Carbon footprint: %1 kg CO2/year").arg(result, 0, 'f', 2));
}

void MainWindow::calculateDiet() {
    if (dietTypeCombo->currentIndex() == 0) { // Dacă nu este selectat un regim alimentar
        QMessageBox::warning(this, "Error", "Please select a diet type!");
        return;
    }
    TipRegim regim;
    switch(dietTypeCombo->currentIndex()) {
    case 1: regim = VEGAN; break;
    case 2: regim = VEGETARIAN; break;
    default: regim = OMNIVOR;
    }

    RegimAlimentar regimAlimentar(regim);
    double result = regimAlimentar.calculAC();
    dietResultLabel->setText(QString("Carbon footprint: %1 kg CO2/year").arg(result, 0, 'f', 2));
}
