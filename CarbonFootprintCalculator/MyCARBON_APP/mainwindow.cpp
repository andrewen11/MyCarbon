// mainwindow.cpp
#include "mainwindow.h"
#include "carbon_classes.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("Calculator Amprentă de Carbon");
    setMinimumSize(600, 600);

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
        "    border: 1px solid #a5d6a7;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 14px;"
        "}"
        "QComboBox {"
        "    border: 1px solid #a5d6a7;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 14px;"
        "    background-color: white;"
        "}"
        );
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Creăm un titlu frumos pentru aplicație
    QLabel *titleLabel = new QLabel("Calculator Amprentă de Carbon", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");

    mainLayout->addWidget(titleLabel);

    // Layout pentru butoane
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *individualButton = new QPushButton("Individual", this);
    QPushButton *houseButton = new QPushButton("Casă", this);
    QPushButton *dietButton = new QPushButton("Regim Alimentar", this);

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

QWidget* MainWindow::createIndividualPage() {
    individualPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(individualPage);

    // Elemente
    breathsEdit = new QLineEdit();
    distanceEdit = new QLineEdit();
    transportTypeCombo = new QComboBox();
    transportTypeCombo->addItems({"Mașină personală", "Transport comun"});
    individualResultLabel = new QLabel();

    QGroupBox *groupBox = new QGroupBox("Date Individuale");
    QVBoxLayout *groupLayout = new QVBoxLayout();

    groupLayout->addWidget(new QLabel("Respirații pe minut:"));
    groupLayout->addWidget(breathsEdit);
    groupLayout->addWidget(new QLabel("Kilometri parcurși zilnic:"));
    groupLayout->addWidget(distanceEdit);
    groupLayout->addWidget(new QLabel("Tip transport:"));
    groupLayout->addWidget(transportTypeCombo);

    groupBox->setLayout(groupLayout);

    QPushButton *calculateButton = new QPushButton("Calculează");
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateIndividual);

    layout->addWidget(groupBox);
    layout->addWidget(calculateButton);
    layout->addWidget(individualResultLabel);
    layout->addStretch();

    return individualPage;
}

QWidget* MainWindow::createHousePage() {
    housePage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(housePage);

    spaceEdit = new QLineEdit();
    houseTypeCombo = new QComboBox();
    houseTypeCombo->addItems({"Garsonieră", "Apartament", "Casă"});
    electricityEdit = new QLineEdit();
    gasEdit = new QLineEdit();
    hotWaterEdit = new QLineEdit();
    coldWaterEdit = new QLineEdit();
    houseResultLabel = new QLabel();

    QGroupBox *groupBox = new QGroupBox("Date Locuință");
    QVBoxLayout *groupLayout = new QVBoxLayout();

    groupLayout->addWidget(new QLabel("Spațiu util (m²):"));
    groupLayout->addWidget(spaceEdit);
    groupLayout->addWidget(new QLabel("Tip locuință:"));
    groupLayout->addWidget(houseTypeCombo);
    groupLayout->addWidget(new QLabel("Consum curent electric (kWh/lună):"));
    groupLayout->addWidget(electricityEdit);
    groupLayout->addWidget(new QLabel("Consum gaze naturale (m³/lună):"));
    groupLayout->addWidget(gasEdit);
    groupLayout->addWidget(new QLabel("Consum apă caldă (litri/lună):"));
    groupLayout->addWidget(hotWaterEdit);
    groupLayout->addWidget(new QLabel("Consum apă rece (litri/lună):"));
    groupLayout->addWidget(coldWaterEdit);

    groupBox->setLayout(groupLayout);

    QPushButton *calculateButton = new QPushButton("Calculează");
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
    dietTypeCombo->addItems({"Vegan", "Vegetarian", "Omnivor"});
    dietResultLabel = new QLabel();

    QGroupBox *groupBox = new QGroupBox("Regim Alimentar");
    QVBoxLayout *groupLayout = new QVBoxLayout();

    groupLayout->addWidget(new QLabel("Tip regim alimentar:"));
    groupLayout->addWidget(dietTypeCombo);

    groupBox->setLayout(groupLayout);

    QPushButton *calculateButton = new QPushButton("Calculează");
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

void MainWindow::calculateIndividual() {
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
}

void MainWindow::calculateHouse() {
    bool ok[6];
    double space = spaceEdit->text().toDouble(&ok[0]);
    double electricity = electricityEdit->text().toDouble(&ok[1]);
    double gas = gasEdit->text().toDouble(&ok[2]);
    double hotWater = hotWaterEdit->text().toDouble(&ok[3]);
    double coldWater = coldWaterEdit->text().toDouble(&ok[4]);

    if (!ok[0] || !ok[1] || !ok[2] || !ok[3] || !ok[4]) {
        QMessageBox::warning(this, "Eroare", "Vă rugăm introduceți valori numerice valide!");
        return;
    }

    TipLocuinta tipLocuinta;
    switch(houseTypeCombo->currentIndex()) {
    case 0: tipLocuinta = GARSONIERA; break;
    case 1: tipLocuinta = APARTAMENT; break;
    default: tipLocuinta = CASA;
    }

    Casa casa(tipLocuinta, space, electricity, gas, hotWater, coldWater);
    double result = casa.calculAC();
    houseResultLabel->setText(QString("Amprenta de carbon: %1 kg CO2/an").arg(result, 0, 'f', 2));
}

void MainWindow::calculateDiet() {
    TipRegim regim;
    switch(dietTypeCombo->currentIndex()) {
    case 0: regim = VEGAN; break;
    case 1: regim = VEGETARIAN; break;
    default: regim = OMNIVOR;
    }

    RegimAlimentar regimAlimentar(regim);
    double result = regimAlimentar.calculAC();
    dietResultLabel->setText(QString("Amprenta de carbon: %1 kg CO2/an").arg(result, 0, 'f', 2));
}
