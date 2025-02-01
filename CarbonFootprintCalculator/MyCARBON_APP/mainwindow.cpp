// mainwindow.cpp
#include "mainwindow.h"
#include "info1.h"
#include "carbon_classes.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QPainter>
#include <QInputDialog>
#include <QTextEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), infoWindow(nullptr)
{
    qDebug() << "MainWindow constructor called.";
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

void MainWindow::goBack() {
    qDebug() << "Returning to Start Menu...";  // 🔥 Debugging
    emit backToStart();  // ✅ Notify that we are returning
    this->hide();  // ✅ Hide instead of closing
}

void MainWindow::openInfoWindow() {
    qDebug() << "Opening Info Window...";  // 🔥 Debugging

    if (!infoWindow) {
        infoWindow = new InfoWindow(this);  // ✅ Ensure it's linked to MainWindow
    }

    infoWindow->show();
    infoWindow->raise();
    infoWindow->activateWindow();
}

MainWindow::~MainWindow() {
    delete infoWindow;
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // ✅ Top Bar Layout (Grid pentru o mai bună aliniere)
    QGridLayout *topBarLayout = new QGridLayout();
    topBarLayout->setColumnStretch(1, 1); // Asigură că titlul e centrat

    // ✅ "Back" Button (Stânga)
    backButton = new QPushButton("Back", this);
    backButton->setFixedSize(90, 43);
    backButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    color: #4CAF50;"
        "    border: 2px solid #4CAF50;"
        "    font-size: 16px;"
        "    border-radius: 20px;"
        "} "
        "QPushButton:hover { background-color: #4CAF50; color: white; }"
        );
    connect(backButton, &QPushButton::clicked, this, &MainWindow::goBack);

    // ✅ Title Label (Mijloc)
    QLabel *titleLabel = new QLabel("🌍 Carbon Footprint Calculator", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #2e7d32; margin-bottom: 10px;");

    // ✅ "Info" Button (Dreapta)
    infoButton = new QPushButton("Help", this);
    infoButton->setFixedSize(90, 43);
    infoButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    color: #4CAF50;"
        "    border: 2px solid #4CAF50;"
        "    font-size: 16px;"
        "    border-radius: 20px;"
        "} "
        "QPushButton:hover { background-color: #4CAF50; color: white; }"
        );
    connect(infoButton, &QPushButton::clicked, this, &MainWindow::openInfoWindow);

    // ✅ Adăugăm elementele în grid layout
    topBarLayout->addWidget(backButton, 0, 0, Qt::AlignLeft);   // Buton Back (stânga)
    topBarLayout->addWidget(titleLabel, 0, 1, Qt::AlignCenter); // Titlu (centru)
    topBarLayout->addWidget(infoButton, 0, 2, Qt::AlignRight);  // Buton Info (dreapta)

    // ✅ Adăugăm Top Bar în layout-ul principal
    mainLayout->addLayout(topBarLayout);

    // ✅ Meniu de navigare
    QHBoxLayout *menuLayout = new QHBoxLayout();
    menuLayout->setSpacing(15);

    QPushButton *individualButton = new QPushButton("👤 Individual", this);
    QPushButton *houseButton = new QPushButton("🏠 Home", this);
    QPushButton *dietButton = new QPushButton("🥗 Diet", this);
    connect(dietButton, &QPushButton::clicked, this, &MainWindow::showDietPage);

    QString buttonStyle =
        "QPushButton {"
        "    background-color: #4CAF50; color: white; font-size: 18px; padding: 12px;"
        "    border-radius: 10px; font-weight: bold;"
        "} "
        "QPushButton:hover { background-color: #388E3C; }";

    individualButton->setStyleSheet(buttonStyle);
    houseButton->setStyleSheet(buttonStyle);
    dietButton->setStyleSheet(buttonStyle);

    menuLayout->addWidget(individualButton);
    menuLayout->addWidget(houseButton);
    menuLayout->addWidget(dietButton);
    mainLayout->addLayout(menuLayout);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(createIndividualPage());
    stackedWidget->addWidget(createHousePage());
    stackedWidget->addWidget(createDietPage());
    mainLayout->addWidget(stackedWidget);

    connect(individualButton, &QPushButton::clicked, this, &MainWindow::showIndividualPage);
    connect(houseButton, &QPushButton::clicked, this, &MainWindow::showHousePage);
    connect(dietButton, &QPushButton::clicked, this, &MainWindow::showDietPage);

    setCentralWidget(centralWidget);

    if (!transportFormLayout) {  // Verifică dacă există deja
        transportFormLayout = new QFormLayout();
    }
    if (!wasteFormLayout) {
        wasteFormLayout = new QFormLayout();
    }
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground(); // Actualizăm fundalul la redimensionare
    // ✅ Align "Back" Button (Left Side)
    // Repoziționează butoanele doar în partea de sus!
    int buttonY = 15;  // Distanta de la marginea superioară

    // ✅ Poziționare "Back" (stânga)
    int backButtonX = 10;
    backButton->move(backButtonX, buttonY);

    // ✅ Poziționare "Info" (dreapta)
    int infoButtonX = width() - infoButton->width() - 10;
    infoButton->move(infoButtonX, buttonY);
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

    // ✅ Container principal pentru scroll
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(20, 20, 20, 20); // 🔥 Added more margins
    scrollLayout->setSpacing(15);

    // ✅ Asigurăm inițializarea layout-urilor
   transportFormLayout = new QFormLayout();
    wasteFormLayout = new QFormLayout();

    scrollWidget->setStyleSheet(
        "QWidget {"
        "    background-color: rgba(255, 255, 255, 0.6);"  // ✅ Light white transparent
        "    border-radius: 10px;"
        "} "
        );

    // 🌬️ **Respirație - Container cu stil**
    QGroupBox *breathGroup = new QGroupBox();
    breathGroup->setStyleSheet(
        "QGroupBox {"
        "    background-color: white;"  // ✅ Same white background
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 20px;"  // ✅ Bigger title
        "    font-weight: bold;"
        "    color: #2e7d32;"
        "    margin-top: 15px;"
        "} "
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top left;"  // ✅ Align title to left
        "    padding: 10px 15px;"
        "}"
        );

    QVBoxLayout *breathLayout = new QVBoxLayout();
    QLabel *breathLabel = new QLabel("Breaths per minute:");
    breathLabel->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: green;"
        "margin-bottom: 5px;"
        "margin-top: -5px;"
        );
    breathsEdit = new QLineEdit();
    breathsEdit->setPlaceholderText("Enter your breathing rate (5-25)");
    breathsEdit->setValidator(new QIntValidator(5, 25, this));
    breathsEdit->setStyleSheet(
        "QLineEdit {"
        "    background-color: white;"
        "    border: 1px solid #4CAF50;"
        "    border-radius: 5px;"
        "    padding: 8px;"
        "    font-size: 16px;"
        "}"
        );

    breathLayout->addWidget(breathLabel);
    breathLayout->addWidget(breathsEdit);
    breathGroup->setLayout(breathLayout);
    scrollLayout->addWidget(breathGroup);

    // 🚗 **Transport - Container cu stil**

    QLabel *TransportLabel = new QLabel("Select transport method(s):");  // 🔥 Added icon for visibility
    TransportLabel->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: green;"
        "margin-bottom: 5px;"
        "margin-top: -5px;"
        );

    QGroupBox *transportGroup = new QGroupBox();
    transportGroup->setStyleSheet(
        "QGroupBox {"
        "    background-color: white;"  // ✅ White background for contrast
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "    color: #2e7d32;"
        "    margin-top: 15px;"
        "} "
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top left;"
        "    padding: 10px 15px;"
        "}"
        );

    QVBoxLayout *transportLayout = new QVBoxLayout();
    transportTypeList = new QListWidget();
    transportTypeList->setSelectionMode(QAbstractItemView::MultiSelection);

    // 🔥 Fix `QListWidget` style
    transportTypeList->setStyleSheet(
        "QListWidget {"
        "    background-color: rgba(255, 255, 255, 245);"  // ✅ Light background
        "    border: 1px solid #4CAF50;"  // ✅ Green border
        "    font-size: 16px;"
        "    padding: 10px;"
        "    color: black;"  // ✅ Text color visible
        "} "
        "QListWidget::indicator:unchecked {"
        "    background-color: white;"
        "    border: 2px solid #4CAF50;"
        "    width: 18px;"
        "    height: 18px;"
        "} "
        "QListWidget::indicator:checked {"
        "    background-color: #4CAF50;"
        "    border: 2px solid #2e7d32;"
        "}");

    // 🚛 **Waste - Container cu stil**
    QLabel *WasteLabel = new QLabel("Select waste used:");
    WasteLabel->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: #2e7d32;"
        "margin-bottom: 5px;"
        "margin-top: -5px;"
        );

    QGroupBox *wasteGroup = new QGroupBox();
    wasteGroup->setStyleSheet(
        "QGroupBox {"
        "    background-color: white;"  // ✅ White background for consistency
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "    color: #2e7d32;"
        "    margin-top: 15px;"
        "} "
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top left;"
        "    padding: 10px 15px;"
        "}"
        );

    QVBoxLayout *wasteLayout = new QVBoxLayout();
    wasteTypeList = new QListWidget();
    wasteTypeList->setSelectionMode(QAbstractItemView::MultiSelection);

    // 🔥 Fix `QListWidget` style
    wasteTypeList->setStyleSheet(
        "QListWidget {"
        "    background-color: rgba(255, 255, 255, 245);"  // ✅ Light background
        "    border: 1px solid #4CAF50;"  // ✅ Green border
        "    font-size: 16px;"
        "    padding: 10px;"
        "    color: black;"  // ✅ Text color visible
        "} "
        "QListWidget::indicator:unchecked {"
        "    background-color: white;"
        "    border: 2px solid #4CAF50;"
        "    width: 18px;"
        "    height: 18px;"
        "} "
        "QListWidget::indicator:checked {"
        "    background-color: #4CAF50;"
        "    border: 2px solid #2e7d32;"
        "}");

    // ✅ Auto-adjust height based on content
    wasteTypeList->setMinimumHeight(wasteTypeList->sizeHintForRow(0) * 4 + 10);
    wasteLayout->addWidget(WasteLabel);
    wasteLayout->addWidget(wasteTypeList);
    wasteLayout->addLayout(wasteFormLayout);
    wasteGroup->setLayout(wasteLayout);
    scrollLayout->addWidget(wasteGroup);

    // ✅ Add transport options dynamically
    QStringList transportOptions = {"Personal Car", "Public Transport", "Bicycle", "Scooter", "Walk"};
    for (const QString &option : transportOptions) {
        QListWidgetItem *item = new QListWidgetItem(option, transportTypeList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        transportTypeList->addItem(item);
    }

    // ✅ Dynamically adjust QListWidget height
    int rowHeight = transportTypeList->sizeHintForRow(0); // Height of one row
    transportTypeList->setFixedHeight(rowHeight * transportTypeList->count() + 10); // Dynamic height

    transportLayout->addWidget(TransportLabel);
    transportLayout->addWidget(transportTypeList);
    transportLayout->addLayout(transportFormLayout);
    transportGroup->setLayout(transportLayout);
    scrollLayout->addWidget(transportGroup);

    connect(transportTypeList, &QListWidget::itemChanged, this, &MainWindow::onTransportTypeChanged);

    // ✅ Add waste options dynamically
    QStringList wasteOptions = {"Plastic", "Paper", "Glass", "Food Waste"};
    for (const QString &option : wasteOptions) {
        QListWidgetItem *item = new QListWidgetItem(option, wasteTypeList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        wasteTypeList->addItem(item);
    }

    // ✅ Dynamically adjust QListWidget height
    int wasteRowHeight = wasteTypeList->sizeHintForRow(0);
    wasteTypeList->setFixedHeight(wasteRowHeight * wasteTypeList->count() + 10);

    wasteLayout->addWidget(wasteTypeList);
    wasteLayout->addLayout(wasteFormLayout);
    wasteGroup->setLayout(wasteLayout);
    scrollLayout->addWidget(wasteGroup);

    connect(wasteTypeList, &QListWidget::itemChanged, this, &MainWindow::onWasteTypeChanged);

    // ✅ **Adăugăm butonul de calcul și rezultat**
    QPushButton *calculateButton = new QPushButton("Calculate");
    calculateButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"  // ✅ Green background
        "    color: white;"  // ✅ White text
        "    font-size: 18px;"  // ✅ Larger font
        "    padding: 10px 20px;"
        "    border-radius: 8px;"  // ✅ Rounded corners
        "    font-weight: bold;"
        "} "
        "QPushButton:hover {"
        "    background-color: #388E3C;"  // ✅ Darker green on hover
        "} "
        "QPushButton:pressed {"
        "    background-color: #1B5E20;"  // ✅ Even darker when pressed
        "} "
        );
    scrollLayout->addWidget(calculateButton, 0, Qt::AlignCenter);  // ✅ Center the button
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateIndividual);

    // ✅ **Facem containerul scrollabil**
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // 🔥 Fix scroll area background color and remove black edges
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"  // Remove any black border
        "    background-color: transparent;"  // Make background blend
        "} "
        "QScrollArea QWidget {"
        "    background-color: rgba(255, 255, 255, 0.6);"  // ✅ White transparent
        "    border-radius: 10px;"  // ✅ Rounded corners
        "} "
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: rgba(0, 0, 0, 0.1);"  // ✅ Light scrollbar background
        "    width: 10px;"
        "    margin: 5px 0 5px 0;"
        "    border-radius: 5px;"
        "} "
        "QScrollBar::handle:vertical {"
        "    background: rgba(76, 175, 80, 0.8);"  // ✅ Green scroll handle
        "    min-height: 30px;"
        "    border-radius: 5px;"
        "} "
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: none;"
        "    border: none;"
        "}"
        );


    // ✅ **Adăugăm scrollArea în layout-ul principal al paginii**
    QVBoxLayout *mainLayout = new QVBoxLayout(individualPage);
    mainLayout->addWidget(scrollArea);

    return individualPage;
}





void MainWindow::onTransportTypeChanged(QListWidgetItem *item) {
    if (!transportTypeList || !transportFormLayout || !item) return; // 🔥 Verificare pointeri

    QString transportName = item->text();
    bool checked = (item->checkState() == Qt::Checked);

    qDebug() << "Transport selection changed: " << transportName << ", Checked: " << checked;

    transportTypeList->setStyleSheet(
        "QListWidget {"
        "    background-color: rgba(255, 255, 255, 230);"
        "    border: 1px solid #4CAF50;"
        "    font-size: 16px;"
        "    padding: 10px;"
        "    color: black;"
        "}"
        "QListWidget::indicator:unchecked {"
        "    background-color: white;"
        "    border: 2px solid #4CAF50;"
        "    width: 18px;"
        "    height: 18px;"
        "}"
        "QListWidget::indicator:checked {"
        "    background-color: #4CAF50;"
        "    border: 2px solid #2e7d32;"
        "}"
        );

    // 🚗 Personal Car
    if (transportName == "Personal Car") {
        if (checked && !distanceInputs.contains(transportName)) {
            QLabel *distanceLabel = new QLabel("Personal Car Distance (km):");
            QLineEdit *distanceEdit = new QLineEdit();
            distanceEdit->setPlaceholderText("Enter monthly distance (km)");
            distanceEdit->setStyleSheet(
                "QLineEdit {"
                "    background-color: white;"
                "    border: 1px solid #4CAF50;"
                "    border-radius: 5px;"
                "    padding: 5px;"
                "    font-size: 14px;"
                "} "
                );

            QLabel *fuelLabel = new QLabel("Personal Car Fuel Type:");
            QComboBox *fuelCombo = new QComboBox();
            fuelCombo->addItems({"Gasoline", "Diesel", "Electric", "LPG"});

            // ✅ Apply the same styling as the disposal method combo box
            fuelCombo->setStyleSheet(
                "QComboBox {"
                "    background-color: white;"
                "    color: black;"
                "    border: 2px solid #4CAF50;"
                "    border-radius: 5px;"
                "    padding: 5px;"
                "    font-size: 14px;"
                "} "
                "QComboBox::drop-down {"
                "    border: none;"
                "    background: #4CAF50;"
                "    width: 25px;"
                "} "
                "QComboBox::down-arrow {"
                "    image: url(:/icons/down-arrow.png);"  // ✅ Use a custom arrow icon
                "} "
                "QComboBox QAbstractItemView {"
                "    background: white;"
                "    color: black;"
                "    selection-background-color: #4CAF50;"
                "    selection-color: white;"
                "    border: 1px solid #4CAF50;"
                "} "
                "QComboBox::item {"
                "    padding: 5px;"
                "} "
                "QComboBox::item:selected {"
                "    background-color: #4CAF50;"
                "    color: white;"
                "} "
                );

            transportFormLayout->addRow(distanceLabel, distanceEdit);
            transportFormLayout->addRow(fuelLabel, fuelCombo);

            distanceLabels[transportName] = distanceLabel;
            distanceInputs[transportName] = distanceEdit;
            fuelLabels[transportName] = fuelLabel;
            fuelInputs[transportName] = fuelCombo;
        }
        else if (!checked) {
            delete distanceLabels.take(transportName);
            delete distanceInputs.take(transportName);
            delete fuelLabels.take(transportName);
            delete fuelInputs.take(transportName);
        }
    }

    // 🚌 Public Transport
    else if (transportName == "Public Transport") {
        if (checked) {
            // Create public transport widgets if they don't exist
                publicTransportLabel = new QLabel("Select Public Transport:");
                transportFormLayout->addRow(publicTransportLabel);

            if (!publicTransportCombo) {
                publicTransportCombo = new QListWidget();
                publicTransportCombo->setSelectionMode(QAbstractItemView::MultiSelection);
                publicTransportCombo->setStyleSheet(
                    "QListWidget {"
                    "    background-color: rgba(255, 255, 255, 245);"
                    "    border: 1px solid #4CAF50;"
                    "    font-size: 16px;"
                    "    padding: 10px;"
                    "    color: black;"
                    "} "
                    "QListWidget::indicator:unchecked {"
                    "    background-color: white;"
                    "    border: 2px solid #4CAF50;"
                    "    width: 18px;"
                    "    height: 18px;"
                    "} "
                    "QListWidget::indicator:checked {"
                    "    background-color: #4CAF50;"
                    "    border: 2px solid #2e7d32;"
                    "}"
                    );

                QStringList options = {"Train", "Metro", "Bus", "Trolleybus", "Airplane"};
                for (const QString &option : options) {
                    QListWidgetItem *optionItem = new QListWidgetItem(option);
                    optionItem->setFlags(optionItem->flags() | Qt::ItemIsUserCheckable);
                    optionItem->setCheckState(Qt::Unchecked);
                    publicTransportCombo->addItem(optionItem);
                }

                connect(publicTransportCombo, &QListWidget::itemChanged, this, &MainWindow::onPublicTransportChanged);
                transportFormLayout->addRow(publicTransportCombo);
            }
        } else {
            // Safe cleanup of public transport widgets
            if (publicTransportCombo) {
                // First, disconnect the signal to prevent crashes during cleanup
                disconnect(publicTransportCombo, &QListWidget::itemChanged, this, &MainWindow::onPublicTransportChanged);

                // Remove all public transport distance inputs
                QMutableMapIterator<QString, QLabel*> labelIt(publicTransportLabels);
                while (labelIt.hasNext()) {
                    labelIt.next();
                    if (labelIt.value()) {
                        transportFormLayout->removeWidget(labelIt.value());
                        delete labelIt.value();
                    }
                }
                publicTransportLabels.clear();

                QMutableMapIterator<QString, QLineEdit*> distanceIt(publicTransportDistances);
                while (distanceIt.hasNext()) {
                    distanceIt.next();
                    if (distanceIt.value()) {
                        transportFormLayout->removeWidget(distanceIt.value());
                        delete distanceIt.value();
                    }
                }
                publicTransportDistances.clear();

                // Remove the combo box and label
                if (publicTransportLabel) {
                    transportFormLayout->removeWidget(publicTransportLabel);
                    delete publicTransportLabel;
                    publicTransportLabel = nullptr;
                }

                transportFormLayout->removeWidget(publicTransportCombo);
                delete publicTransportCombo;
                publicTransportCombo = nullptr;
            }
        }
        return;
    }
    // 🚲 Bicycle, 🛴 Scooter, 🚶 Walk
    else if (transportName == "Bicycle" || transportName == "Scooter" || transportName == "Walk") {
        if (checked && !distanceInputs.contains(transportName)) {
            QLabel *distanceLabel = new QLabel(transportName + " Distance (km):");
            QLineEdit *distanceEdit = new QLineEdit();
            distanceEdit->setPlaceholderText("Enter monthly distance (km)");
            distanceEdit->setStyleSheet("border: 1px solid #4CAF50; border-radius: 5px; padding: 5px;");

            transportFormLayout->addRow(distanceLabel, distanceEdit);
            distanceLabels[transportName] = distanceLabel;
            distanceInputs[transportName] = distanceEdit;
        }
        else if (!checked) {
            delete distanceLabels.take(transportName);
            delete distanceInputs.take(transportName);
        }
    }
}


void MainWindow::onPublicTransportChanged(QListWidgetItem *item) {
    if (!publicTransportCombo || !transportFormLayout || !item) return;

    QString transportType = item->text();
    bool checked = (item->checkState() == Qt::Checked);

    qDebug() << "Public Transport Selection Changed: " << transportType << ", Checked: " << checked;

    if (checked) {
        // Only create new widgets if they don't already exist
        if (!publicTransportDistances.contains(transportType)) {
            QLabel *label = new QLabel(transportType + " Distance (km):");
            QLineEdit *distanceEdit = new QLineEdit();
            distanceEdit->setPlaceholderText("Enter monthly distance for " + transportType);
            distanceEdit->setStyleSheet("border: 1px solid #4CAF50; border-radius: 5px; padding: 5px;");

            transportFormLayout->addRow(label, distanceEdit);
            publicTransportLabels[transportType] = label;
            publicTransportDistances[transportType] = distanceEdit;
        }
    } else {
        // Safe removal of widgets
        if (publicTransportLabels.contains(transportType)) {
            QLabel *label = publicTransportLabels[transportType];
            transportFormLayout->removeWidget(label);
            delete label;
            publicTransportLabels.remove(transportType);
        }

        if (publicTransportDistances.contains(transportType)) {
            QLineEdit *distanceEdit = publicTransportDistances[transportType];
            transportFormLayout->removeWidget(distanceEdit);
            delete distanceEdit;
            publicTransportDistances.remove(transportType);
        }
    }
}

double getCombustibilEmission(TipCombustibil combustibil) {
    switch (combustibil) {
    case BENZINA: return EmisieCombustibil::BENZINA;
    case MOTORINA: return EmisieCombustibil::MOTORINA;
    case ELECTRICA: return EmisieCombustibil::ELECTRICA;
    case GPL: return EmisieCombustibil::GPL;
    default: return 0.0;
    }
}

double getTransportPublicEmission(TipTransportPublic transportPublic) {
    switch (transportPublic) {
    case TREN: return EmisieTransportPublic::TREN;
    case METROU: return EmisieTransportPublic::METROU;
    case AUTOBUZ: return EmisieTransportPublic::AUTOBUZ;
    case TROLEIBUZ: return EmisieTransportPublic::TROLEIBUZ;
    case AVION: return EmisieTransportPublic::AVION;
    default: return 0.0;
    }
}

void MainWindow::onWasteTypeChanged(QListWidgetItem *item) {
    if (!item) return;

    QString wasteName = item->text();
    bool checked = (item->checkState() == Qt::Checked);

    if (checked) {
        QLabel *amountLabel = new QLabel(wasteName + " Amount (g):");
        QLineEdit *amountEdit = new QLineEdit();
        amountEdit->setPlaceholderText("Enter monthly waste amount");
        amountEdit->setValidator(new QDoubleValidator(0.00, 1000.00, 2, this));
        amountEdit->setLocale(QLocale::C); // ✅ Forțăm separatorul de zecimale "."

        QLabel *methodLabel = new QLabel("Disposal Method for " + wasteName + ":");
        QComboBox *methodCombo = new QComboBox();
        methodCombo->addItems({"Landfill", "Incineration", "Recycling", "Composting"});

        // ✅ Aplică stilul manual, după crearea QComboBox-ului
        methodCombo->setStyleSheet(
            "QComboBox {"
            "    background-color: white;"  // ✅ Alb pentru câmpul principal
            "    color: black;"  // ✅ Text negru
            "    border: 2px solid #4CAF50;"
            "    border-radius: 5px;"
            "    padding: 5px;"
            "    font-size: 14px;"
            "} "
            "QComboBox::drop-down {"
            "    border: none;"
            "    background: #4CAF50;"  // ✅ Fundal verde pentru săgeată
            "    width: 25px;"
            "} "
            "QComboBox::down-arrow {"
            "    image: url(:/icons/down-arrow.png);"  // ✅ Poți pune o imagine custom
            "} "
            "QComboBox QAbstractItemView {"
            "    background: white;"  // ✅ Alb pentru dropdown
            "    color: black;"  // ✅ Text negru pentru contrast
            "    selection-background-color: #4CAF50;"  // ✅ Verde pentru selecție
            "    selection-color: white;"  // ✅ Text alb când e selectat
            "    border: 1px solid #4CAF50;"
            "} "
            "QComboBox::item {"
            "    padding: 5px;"
            "} "
            "QComboBox::item:selected {"
            "    background-color: #4CAF50;"  // ✅ Verde când e selectat
            "    color: white;"
            "} ");

        // ✅ Adăugare în layout
        wasteFormLayout->addRow(amountLabel, amountEdit);
        wasteFormLayout->addRow(methodLabel, methodCombo);

        // ✅ Stocare pentru eliminare ulterioară
        wasteAmountLabels.insert(wasteName, amountLabel);
        wasteAmountInputs.insert(wasteName, amountEdit);
        wasteMethodLabels.insert(wasteName, methodLabel);
        wasteDisposalInputs.insert(wasteName, methodCombo);
    }
    else {
        // ✅ Elimină câmpurile la deselectare
        delete wasteAmountLabels.take(wasteName);
        delete wasteAmountInputs.take(wasteName);
        delete wasteMethodLabels.take(wasteName);
        delete wasteDisposalInputs.take(wasteName);
    }
}



void MainWindow::calculateIndividual() {
    qDebug() << "Calculating Individual Carbon Footprint...";
    bool ok;
    int breaths = breathsEdit->text().toInt(&ok);
    if (!ok || breaths < 5 || breaths > 25) {
        QMessageBox::warning(this, "Error", "Please enter a valid breathing rate (5-25).");
        return;
    }

    std::vector<TipTransport> transports;
    std::vector<TipCombustibil> combustibili;
    std::vector<TipTransportPublic> transportPublics;
    std::vector<double> distances;

    double totalTransportCO2 = 0.0;
    QString transportDetails;
    double totalCO2Footprint = 0.0;
    QString resultDetails;

    // 🛠️ Waste Calculations
    double totalWasteCO2 = 0.0;
    QString wasteDetails;

    // ✅ Respiration Carbon Footprint
    double acBreaths = breaths * 60 * 24 * 365 * EMISIE_RESPIRATIE;
    totalCO2Footprint += acBreaths;
    resultDetails += QString("💨 <b>Breathing Carbon Footprint:</b> %1 kg CO₂/year<br>").arg(acBreaths, 0, 'f', 2);

    // 🚗 Personal Transport
    for (const QString &transport : distanceInputs.keys()) {
        double distance = distanceInputs[transport]->text().toDouble(&ok);
        if (!ok || distance <= 0) {
            QMessageBox::warning(this, "Error", "Please enter a valid distance for " + transport);
            return;
        }

        if (transport == "Personal Car") {
            transports.push_back(MASINA_PERSONALA);
            distances.push_back(distance);

            if (fuelInputs.contains(transport)) {
                QString fuelType = fuelInputs[transport]->currentText();
                TipCombustibil combustibil;

                if (fuelType == "Gasoline") combustibil = BENZINA;
                else if (fuelType == "Diesel") combustibil = MOTORINA;
                else if (fuelType == "Electric") combustibil = ELECTRICA;
                else if (fuelType == "LPG") combustibil = GPL;
                else {
                    QMessageBox::warning(this, "Error", "Please select a valid fuel type for " + transport);
                    return;
                }
                combustibili.push_back(combustibil);

                double transportCO2 = distance * 12 * getCombustibilEmission(combustibil);
                totalCO2Footprint += transportCO2;
                totalTransportCO2 += transportCO2;
                transportDetails += QString("🚗 Personal Car (Fuel: %1, %2 km): %3 kg CO₂/year<br>")
                                        .arg(fuelType).arg(distance).arg(transportCO2, 0, 'f', 2);
            }
        }

        else if (transport == "Bicycle") {
            double co2Bicycle = distance * 12 * 0.0021;
            totalCO2Footprint += co2Bicycle;
            totalTransportCO2 += co2Bicycle;
            transportDetails += QString("🚲 Bicycle (%1 km): %2 kg CO₂/year<br>")
                                    .arg(distance).arg(co2Bicycle, 0, 'f', 2);
        }
        else if (transport == "Scooter") {
            double co2Scooter = distance * 12 * 0.0018;
            totalCO2Footprint += co2Scooter;
            totalTransportCO2 += co2Scooter;
            transportDetails += QString("🛴 Scooter (%1 km): %2 kg CO₂/year<br>")
                                    .arg(distance).arg(co2Scooter, 0, 'f', 2);
        }
        else if (transport == "Walk") {
            double co2Walk = distance * 12 * 0.0010;
            totalCO2Footprint += co2Walk;
            totalTransportCO2 += co2Walk;
            transportDetails += QString("🚶 Walking (%1 km): %2 kg CO₂/year<br>")
                                    .arg(distance).arg(co2Walk, 0, 'f', 2);
        }
    }

    // 🚌 Public Transport (Separate Line for Each)
    if (publicTransportCombo) {
        for (int i = 0; i < publicTransportCombo->count(); ++i) {
            QListWidgetItem *item = publicTransportCombo->item(i);
            if (item->checkState() == Qt::Checked) {
                QString transportType = item->text();
                double publicDistance = publicTransportDistances[transportType]->text().toDouble(&ok);
                if (!ok || publicDistance <= 0) {
                    QMessageBox::warning(this, "Error", "Please enter a valid distance for " + transportType);
                    return;
                }

                TipTransportPublic transportPublic;
                QString transportEmoji;

                if (transportType == "Train") {
                    transportPublic = TREN;
                    transportEmoji = "🚂";
                } else if (transportType == "Metro") {
                    transportPublic = METROU;
                    transportEmoji = "🚇";
                } else if (transportType == "Bus") {
                    transportPublic = AUTOBUZ;
                    transportEmoji = "🚌";
                } else if (transportType == "Trolleybus") {
                    transportPublic = TROLEIBUZ;
                    transportEmoji = "🚎";
                } else if (transportType == "Airplane") {
                    transportPublic = AVION;
                    transportEmoji = "✈️";
                }

                transportPublics.push_back(transportPublic);

                double transportCO2 = publicDistance * getTransportPublicEmission(transportPublic);
                totalCO2Footprint += transportCO2;
                totalTransportCO2 += transportCO2;
                transportDetails += QString("%1 %2 (%3 km): %4 kg CO₂/year<br>")
                                        .arg(transportEmoji).arg(transportType)
                                        .arg(publicDistance).arg(transportCO2, 0, 'f', 2);
            }
        }
    }

    // 🚆 **Transport Summary**
    if (!transportDetails.isEmpty()) {
        resultDetails += "<hr><b>TRANSPORT DETAILS (kg CO₂ emissions/year) 🚆:</b><br>" + transportDetails + "<br>";
    }
    resultDetails += "🚆 <b>TOTAL Transport Carbon Footprint:</b> " +
                     QString("%1 kg CO₂/year").arg(totalTransportCO2, 0, 'f', 2) + "<br>";

    // ♻️ **Waste Summary**
    for (const QString &waste : wasteAmountInputs.keys()) {
        QString wasteEmoji;

        if (waste == "Plastic") wasteEmoji = "🛍️";
        else if (waste == "Paper") wasteEmoji = "📄";
        else if (waste == "Glass") wasteEmoji = "🥛";
        else if (waste == "Food Waste") wasteEmoji = "♨️";

        bool ok;
        double amount = wasteAmountInputs[waste]->text().toDouble(&ok);
        if (!ok || amount < 0) {
            QMessageBox::warning(this, "Error", "Please enter a valid waste amount for " + waste);
            return;
        }

        QString method = wasteDisposalInputs[waste]->currentText();
        double factor = (method == "Landfill") ? EMISIE_GUNOI_DEPONIE :
                            (method == "Incineration") ? EMISIE_GUNOI_INCINERARE :
                            (method == "Recycling") ? EMISIE_GUNOI_RECICLARE :
                            EMISIE_GUNOI_COMPOST;

        double wasteCO2 = factor * amount * 12 / 1000;
        totalWasteCO2 += wasteCO2;
        wasteDetails += QString("%1 %2 (%3 kg): %4 kg CO₂/year<br>")
                            .arg(wasteEmoji).arg(waste).arg(amount).arg(wasteCO2, 0, 'f', 2);
    }

    if (!wasteDetails.isEmpty()) {
        resultDetails += "<hr><b>WASTE DETAILS (kg CO₂ emissions/year) 🗑️: </b><br>" + wasteDetails + "<br>";
    }
    resultDetails += "🗑️ <b>TOTAL Waste Carbon Footprint:</b> " +
                     QString("%1 kg CO₂/year").arg(totalWasteCO2, 0, 'f', 2) + "<br>";

    totalCO2Footprint += totalWasteCO2;
    // 🌎 **Total Summary**
    resultDetails += "<hr><b>🌎 TOTAL Carbon Footprint:</b> " +
                     QString("%1 kg CO₂/year").arg(totalCO2Footprint, 0, 'f', 2);
    qDebug() << "Total Carbon Footprint: " << totalCO2Footprint;

    // 🔹 Recomandări bazate pe amprentă
    QString recommendations;
    QString recColor;
    QPixmap image;
    if (totalCO2Footprint < 1000) {
        recommendations = "🎉 <b>Great job!</b> Your carbon footprint is quite low. Keep up your eco-friendly habits!";
        recColor = "#4CAF50"; // Verde
        image.load(":/images/green_nature.jpg");
    } else if (totalCO2Footprint < 5000) {
        recommendations = "🌱 <b>You're doing well, but there's room for improvement!</b> Try using public transport or a bicycle more often.";
        recColor = "#FFA500"; // Galben-Portocaliu
        image.load(":/images/renewable_energy.jpg");
    } else {
        recommendations = "⚠️ <b>Your carbon footprint is quite high!</b> Consider reducing car usage, eating more plant-based foods, and conserving energy at home.";
        recColor = "#FF3B30"; // Roșu
        image.load(":/images/pollution.jpg");
    }

    // 🏆 Creare fereastră personalizată de dialog
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Carbon Footprint Results");
    dialog->setMinimumSize(500, 450);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(image.scaled(250, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QLabel *carbonDetailsLabel = new QLabel(resultDetails);
    carbonDetailsLabel->setWordWrap(true);
    carbonDetailsLabel->setStyleSheet("font-size: 14px; color: white; background-color: #2E7D32; padding: 10px; border-radius: 8px;");
    layout->addWidget(carbonDetailsLabel);


    QLabel *recLabel = new QLabel(recommendations);
    recLabel->setWordWrap(true);
    recLabel->setAlignment(Qt::AlignCenter);
    recLabel->setStyleSheet(QString("font-size: 16px; font-weight: bold; color: %1;").arg(recColor));
    layout->addWidget(recLabel);

    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);

    dialog->setLayout(layout);
    dialog->exec();
}

QWidget* MainWindow::createHousePage() {
    housePage = new QWidget();

    // ✅ Scrollable container
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(20, 20, 20, 20);
    scrollLayout->setSpacing(15);

    // ✅ Group Box for Home Inputs
    QGroupBox *groupBox = new QGroupBox();
    groupBox->setStyleSheet(
        "QGroupBox {"
        "    background-color: rgba(255,255,255,0.3);"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "    color: #2e7d32;"
        "    margin-top: 15px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top left;"
        "    padding: 10px 15px;"
        "}"
        );

    QVBoxLayout *groupLayout = new QVBoxLayout();

    countryCombo = new QComboBox();
    countryCombo->addItems({"Romania", "Portugal", "Spain", "Ukraine"});
    countryCombo->setStyleSheet(
        "QComboBox {"
        "    background-color: white;"
        "    color: black;"
        "    border: 2px solid #4CAF50;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 14px;"
        "} "
        "QComboBox::drop-down {"
        "    border: none;"
        "    background: #4CAF50;"
        "    width: 25px;"
        "} "
        "QComboBox::down-arrow {"
        "    image: url(:/icons/down-arrow.png);"
        "} "
        "QComboBox QAbstractItemView {"
        "    background: white;"
        "    color: black;"
        "    selection-background-color: #4CAF50;"
        "    selection-color: white;"
        "    border: 1px solid #4CAF50;"
        "} "
        "QComboBox::item {"
        "    padding: 5px;"
        "} "
        "QComboBox::item:selected {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "} ");

    houseTypeCombo = new QComboBox();
    houseTypeCombo->addItems({"Studio", "Apartment", "House"});
    houseTypeCombo->setStyleSheet(
        "QComboBox {"
        "    background-color: white;"
        "    color: black;"
        "    border: 2px solid #4CAF50;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 14px;"
        "} "
        "QComboBox::drop-down {"
        "    border: none;"
        "    background: #4CAF50;"
        "    width: 25px;"
        "} "
        "QComboBox::down-arrow {"
        "    image: url(:/icons/down-arrow.png);"
        "} "
        "QComboBox QAbstractItemView {"
        "    background: white;"
        "    color: black;"
        "    selection-background-color: #4CAF50;"
        "    selection-color: white;"
        "    border: 1px solid #4CAF50;"
        "} "
        "QComboBox::item {"
        "    padding: 5px;"
        "} "
        "QComboBox::item:selected {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "} ");

    spaceEdit = new QLineEdit();
    spaceEdit->setValidator(new QDoubleValidator(0, 10000, 2, this));
    spaceEdit->setLocale(QLocale::C);
    spaceEdit->setText("0.0");

    electricityEdit = new QLineEdit();
    electricityEdit->setValidator(new QDoubleValidator(0, 10000, 2, this));
    electricityEdit->setLocale(QLocale::C);
    electricityEdit->setText("0.0");

    gasEdit = new QLineEdit();
    gasEdit->setValidator(new QDoubleValidator(0, 10000, 2, this));
    gasEdit->setLocale(QLocale::C);
    gasEdit->setText("0.0");

    woodEdit = new QLineEdit();
    woodEdit->setValidator(new QDoubleValidator(0, 10000, 2, this));
    woodEdit->setLocale(QLocale::C);
    woodEdit->setText("0.0");

    numPersonsEdit = new QLineEdit();
    houseResultLabel = new QLabel();

    groupLayout->addWidget(new QLabel("Select your country:"));
    groupLayout->addWidget(countryCombo);
    groupLayout->addWidget(new QLabel("Type of housing:"));
    groupLayout->addWidget(houseTypeCombo);
    groupLayout->addWidget(new QLabel("Usable space (m²):"));
    groupLayout->addWidget(spaceEdit);
    groupLayout->addWidget(new QLabel("Electricity consumption (kWh/month):"));
    groupLayout->addWidget(electricityEdit);
    groupLayout->addWidget(new QLabel("Natural gas consumption (m³/month):"));
    groupLayout->addWidget(gasEdit);
    groupLayout->addWidget(new QLabel("Wood consumption (kg/month):"));
    groupLayout->addWidget(woodEdit);
    groupLayout->addWidget(new QLabel("Number of people in the household:"));
    groupLayout->addWidget(numPersonsEdit);

    groupBox->setLayout(groupLayout);

    QPushButton *calculateButton = new QPushButton("Calculate");
    calculateButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    font-size: 18px;"
        "    padding: 10px 20px;"
        "    border-radius: 8px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #388E3C; }"
        );
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateHouse);

    scrollLayout->addWidget(groupBox);
    scrollLayout->addWidget(calculateButton, 0, Qt::AlignCenter);
    scrollLayout->addWidget(houseResultLabel);
    scrollLayout->addStretch();

    // ✅ Scroll Area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet(
        "QScrollArea { border: none; background-color: transparent; }"
        "QScrollArea QWidget { background-color: rgba(255, 255, 255, 0.6); border-radius: 10px; }"
        "QScrollBar:vertical { background: rgba(0, 0, 0, 0.1); width: 10px; border-radius: 5px; }"
        "QScrollBar::handle:vertical { background: rgba(76, 175, 80, 0.8); min-height: 30px; border-radius: 5px; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { background: none; border: none; }"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(housePage);
    mainLayout->addWidget(scrollArea);

    return housePage;
}


void MainWindow::calculateHouse() {
    QLocale cLocale(QLocale::C);
    bool ok;
    double space = cLocale.toDouble(spaceEdit->text(), &ok);
    if (!ok || space <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid usable space value.");
        return;
    }

    double electricity = cLocale.toDouble(electricityEdit->text(), &ok);
    if (!ok || electricity < 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid electricity consumption value.");
        return;
    }

    double gas = cLocale.toDouble(gasEdit->text(), &ok);
    if (!ok || gas < 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid natural gas consumption value.");
        return;
    }

    double wood = cLocale.toDouble(woodEdit->text(), &ok);
    if (!ok || wood < 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid wood consumption value.");
        return;
    }
    int numPersons = numPersonsEdit->text().toInt(&ok);
    if (!ok || numPersons <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid number of persons in the household.");
        return;
    }
    QString selectedCountry = countryCombo->currentText();
    QString houseType = houseTypeCombo->currentText();

    // ✅ Ensure the selected country exists in the emission factors map
    if (!FACTORI_EMISIE_TARI.contains(selectedCountry)) {
        QMessageBox::warning(this, "Error", "Selected country is not available in the dataset.");
        return;
    }

    // ✅ Use the selected country's emission factors
    FactoriEmisie factori = FACTORI_EMISIE_TARI[selectedCountry];

    Casa casa(electricity, gas, wood, space, numPersons, houseType, factori);
    //double totalCO2 = casa.calculAC();
    //houseResultLabel->setText(QString("Carbon footprint per person per year: %1 kg CO2").arg(totalCO2, 0, 'f', 2));

    double co2Electricity = casa.emisiiCurentElectric() * 12;
    double co2Gas = casa.emisiiGazeNaturale() * 12;
    double co2Wood = casa.emisiiLemne() * 12;
    double totalCO2 = co2Electricity + co2Gas + co2Wood;

    // 🔹 Recomandări bazate pe amprentă
    QString recommendations;
    QString recColor;
    QPixmap image;
    if (totalCO2 < 1000) {
        recommendations = "🎉 <b>Great job!</b> Your carbon footprint is low. Keep using energy efficiently!";
        recColor = "#4CAF50"; // Verde
        image.load(":/images/green_home.jpg");
    } else if (totalCO2 < 5000) {
        recommendations = "🌱 <b>You're doing okay!</b> Try using energy-saving appliances and reducing heating costs.";
        recColor = "#FFA500"; // Galben-Portocaliu
        image.load(":/images/energy_saving.jpg");
    } else {
        recommendations = "⚠️ <b>Your carbon footprint is quite high!</b> Consider using renewable energy sources and reducing heating and cooling consumption.";
        recColor = "#FF3B30"; // Roșu
        image.load(":/images/high_energy_use.jpg");
    }

    // 🏡 Creare fereastră personalizată de dialog
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Home Carbon Footprint Results");
    dialog->setMinimumSize(500, 450);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(image.scaled(250, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QLabel *carbonDetailsLabel = new QLabel(QString(
                                                "🔌 <b>Electricity Emissions:</b> %1 kg CO₂/year/person<br>"
                                                "🔥 <b>Gas Emissions:</b> %2 kg CO₂/year/person<br>"
                                                "🌲 <b>Wood Emissions:</b> %3 kg CO₂/year/person<br>"
                                                "<hr>🏡 <b>Total Home Carbon Footprint:</b> %4 kg CO₂/year/person<br><br>")
                                                .arg(co2Electricity, 0, 'f', 2)
                                                .arg(co2Gas, 0, 'f', 2)
                                                .arg(co2Wood, 0, 'f', 2)
                                                .arg(totalCO2, 0, 'f', 2));
    carbonDetailsLabel->setWordWrap(true);
    carbonDetailsLabel->setStyleSheet("font-size: 14px; color: white; background-color: #2E7D32; padding: 10px; border-radius: 8px;");
    layout->addWidget(carbonDetailsLabel);

    QLabel *recLabel = new QLabel(recommendations);
    recLabel->setWordWrap(true);
    recLabel->setAlignment(Qt::AlignCenter);
    recLabel->setStyleSheet(QString("font-size: 16px; font-weight: bold; color: %1;").arg(recColor));
    layout->addWidget(recLabel);

    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);

    dialog->setLayout(layout);
    dialog->exec();
}

void MainWindow::showIndividualPage() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showHousePage() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showDietPage() {
    stackedWidget->setCurrentWidget(dietPage);
}

QWidget* MainWindow::createDietPage() {
    dietPage = new QWidget();

    // Container principal pentru scroll
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(20, 20, 20, 20);
    scrollLayout->setSpacing(15);

    // Grup pentru consumul de alimente
    QGroupBox *foodGroup = new QGroupBox("Weekly Food Consumption (g)");
    foodGroup->setStyleSheet(
        "QGroupBox {"
        "    background-color: rgba(255,255,255,0.4);"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "    color: #2e7d32;"
        "    margin-top: 15px;"
        "} "
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top left;"
        "    padding: 10px 15px;"
        "} "
        );

    QVBoxLayout *foodLayout = new QVBoxLayout();

    QMap<QString, QString> foodItems = {
        {"White Meat", "🍗"}, {"Red Meat", "🥩"}, {"Fish", "🐟"},
        {"Dairy", "🥛"}, {"Vegetables", "🥦"}, {"Fruits", "🍎"},
        {"Grains", "🌾"}, {"Sweets", "🍬"}, {"Juices", "🥤"},
        {"Ultra-Processed Food", "🍟"}
    };

    for (const QString &food : foodItems.keys()) {
        QLabel *label = new QLabel(foodItems[food] + " " + food + ":");
        QLineEdit *edit = new QLineEdit();
        edit->setValidator(new QDoubleValidator(0, 100000, 2, this)); // până la 100.000g
        edit->setPlaceholderText("Enter weekly consumption in grams");
        edit->setStyleSheet(
            "QLineEdit {"
            "    background-color: white;"
            "    border: 1px solid #4CAF50;"
            "    border-radius: 5px;"
            "    padding: 5px;"
            "    font-size: 14px;"
            "} "
            );
        foodLayout->addWidget(label);
        foodLayout->addWidget(edit);
        foodInputs.insert(food, edit);
    }

    foodGroup->setLayout(foodLayout);
    scrollLayout->addWidget(foodGroup);

    // Buton pentru calculare
    QPushButton *calculateButton = new QPushButton("Calculate Carbon Footprint");
    calculateButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    font-size: 18px;"
        "    padding: 10px 20px;"
        "    border-radius: 8px;"
        "    font-weight: bold;"
        "} "
        "QPushButton:hover { background-color: #388E3C; }"
        );
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateDiet);
    scrollLayout->addWidget(calculateButton, 0, Qt::AlignCenter);

    // Rezultatul calculului
    dietResultLabel = new QLabel();
    dietResultLabel->setWordWrap(true);
    dietResultLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2e7d32;");
    scrollLayout->addWidget(dietResultLabel);

    // ✅ Facem containerul scrollabil
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // ✅ Apply White Transparent Background with Green Border
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"  // Remove any black border
        "    background-color: transparent;"  // Make background blend
        "} "
        "QScrollArea QWidget {"
        "    background-color: rgba(255, 255, 255, 0.6);"  // ✅ White transparent
        "    border-radius: 10px;"  // ✅ Rounded corners
        "} "
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: rgba(0, 0, 0, 0.1);"  // ✅ Light scrollbar background
        "    width: 10px;"
        "    margin: 5px 0 5px 0;"
        "    border-radius: 5px;"
        "} "
        "QScrollBar::handle:vertical {"
        "    background: rgba(76, 175, 80, 0.8);"  // ✅ Green scroll handle
        "    min-height: 30px;"
        "    border-radius: 5px;"
        "} "
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: none;"
        "    border: none;"
        "}"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(dietPage);
    mainLayout->addWidget(scrollArea);

    return dietPage;
}

void MainWindow::calculateDiet() {
    qDebug() << "Calculating Diet Carbon Footprint...";

    double totalFoodCO2 = 0.0;
    QString foodDetails;

    // ✅ Updated emission factors
    QMap<QString, double> foodFactors = {
        {"White Meat", 6.0},   // 🍗 Chicken & Turkey
        {"Red Meat", 27.0},    // 🥩 Beef, Lamb & Pork (Arithmetic Mean)
        {"Fish", 6.0},         // 🐟 Fish
        {"Dairy", 3.2},        // 🥛 Dairy
        {"Vegetables", 2.0},   // 🥦 Vegetables
        {"Fruits", 3.0},       // 🍎 Fruits
        {"Grains", 2.7},       // 🌾 Grains
        {"Sweets", 5.4},       // 🍬 Sweets
        {"Juices", 0.5},       // 🥤 Juices
        {"Ultra-Processed Food", 5.0} // 🍟 Processed Foods
    };

    for (const QString &food : foodInputs.keys()) {
        bool ok;
        double quantityGramsPerWeek = foodInputs[food]->text().toDouble(&ok);
        if (!ok || quantityGramsPerWeek < 0) {
            QMessageBox::warning(this, "Input Error", "Please enter a valid amount for " + food);
            return;
        }

        // ✅ Convert grams → kg per week
        double quantityKgPerWeek = quantityGramsPerWeek / 1000.0;

        // ✅ Convert weekly consumption to annual consumption
        double quantityKgPerYear = quantityKgPerWeek * 52;

        // ✅ Calculate annual carbon footprint
        double foodCO2 = quantityKgPerYear * foodFactors[food];
        totalFoodCO2 += foodCO2;

        foodDetails += QString("🍽 %1: %2 kg CO₂/year<br>")
                           .arg(food)
                           .arg(foodCO2, 0, 'f', 2);
    }

    // 🌎 **Prepare pop-up text**
    QString resultText = "<b>🌱 Diet Carbon Footprint:</b><br>";
    resultText += foodDetails;
    resultText += "<hr><b>🍽 TOTAL Diet Emissions:</b> " +
                  QString("%1 kg CO₂/year").arg(totalFoodCO2, 0, 'f', 2);

    // ✅ Show the pop-up with recommendations & dynamic image
    showDietCarbonFootprintPopup(totalFoodCO2, resultText);
}


void MainWindow::showDietCarbonFootprintPopup(double totalFoodCO2, const QString &carbonDetails) {
    // Create the pop-up window
    QDialog *popup = new QDialog(this);
    popup->setWindowTitle("Diet Carbon Footprint");
    popup->setFixedSize(400, 600);
    popup->setStyleSheet(
        "QDialog {"
        "    background-color: white;"
        "    border-radius: 10px;"
        "    padding: 15px;"
        "}"
        );

    QVBoxLayout *layout = new QVBoxLayout(popup);

    // ✅ Determine recommendation level & image
    QString recommendation;
    QString colorStyle;
    QString imagePath;

    if (totalFoodCO2 > 2000) {  // High Carbon Footprint (Red)
        recommendation = "⚠️ Your carbon footprint is **high**.\nConsider reducing red meat and processed foods.";
        colorStyle = "color: red; font-size: 16px; font-weight: bold;";
        imagePath = ":/images/high_footprint.png";  // Set your high footprint image path
    } else if (totalFoodCO2 > 1000) {  // Neutral (Yellow-Orange)
        recommendation = "⚠️ Your carbon footprint is **moderate**.\nTry incorporating more plant-based foods.";
        colorStyle = "color: orange; font-size: 16px; font-weight: bold;";
        imagePath = ":/images/neutral_footprint.png";  // Set your neutral footprint image path
    } else {  // Low Carbon Footprint (Green)
        recommendation = "✅ Your carbon footprint is **low**.\nGreat job! Keep maintaining a sustainable diet.";
        colorStyle = "color: green; font-size: 16px; font-weight: bold;";
        imagePath = ":/images/low_footprint.png";  // Set your low footprint image path
    }

    // ✅ Image label (dynamic)
    QLabel *imageLabel = new QLabel();
    QPixmap image(imagePath);
    imageLabel->setPixmap(image.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    // ✅ Title label
    QLabel *titleLabel = new QLabel("🌱 Your Diet Carbon Footprint:");
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #2e7d32;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // ✅ Carbon footprint details
    QLabel *detailsLabel = new QLabel(carbonDetails);
    detailsLabel->setWordWrap(true);
    detailsLabel->setStyleSheet("font-size: 14px; padding: 10px;");
    layout->addWidget(detailsLabel);

    // ✅ Recommendation label
    QLabel *recommendationLabel = new QLabel(recommendation);
    recommendationLabel->setStyleSheet(colorStyle);
    recommendationLabel->setWordWrap(true);
    recommendationLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(recommendationLabel);

    // ✅ Close button
    QPushButton *closeButton = new QPushButton("Close");
    closeButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    font-size: 16px;"
        "    padding: 8px 16px;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "} "
        "QPushButton:hover { background-color: #388E3C; }"
        );
    connect(closeButton, &QPushButton::clicked, popup, &QDialog::accept);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);

    popup->setLayout(layout);
    popup->exec();  // Show the pop-up window
}

