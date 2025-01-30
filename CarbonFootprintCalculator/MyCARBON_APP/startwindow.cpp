#include "startwindow.h"
#include <QPixmap>
#include <QPushButton>
#include <QScreen>
#include <QApplication>

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1000, 600); // Dimensiunea minimă

    // Creăm label-ul pentru imagine care acoperă întreaga fereastră
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width(), height()); // Setați inițial dimensiunea să acopere întreaga fereastră

    // Încărcăm imaginea (înlocuiește cu calea către imaginea ta)
    QPixmap background(":/images/carbon_footprint.png");
    if (!background.isNull()) {
        // Scalăm imaginea să acopere întreaga fereastră ignorând raportul de aspect
        backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    // Creăm butonul de start
    startButton = new QPushButton("Start Calculator", this);
    startButton->setFixedSize(150, 35);
    startButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    border-radius: 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    // Creăm butonul pentru credentiale
    credentialsButton = new QPushButton("Credits", this);
    credentialsButton->setFixedSize(150, 35);
    credentialsButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;" // Aceeași culoare ca și Start Calculator
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    border-radius: 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    // Calculăm coordonatele pentru poziționarea centrală
    int totalWidth = startButton->width() + credentialsButton->width() + 10; // Spațiu între butoane
    int baseX = (width() - totalWidth) / 2; // Punctul de start pentru ambele butoane
    int buttonY = height() - startButton->height();

    // Poziționăm butoanele
    startButton->move(baseX, buttonY);
    credentialsButton->move(baseX + startButton->width() + 20, buttonY); // Lângă Start Calculator

    // Conectăm semnalul clicked al butoanelor
    connect(startButton, &QPushButton::clicked, this, [this]() {
        savedGeometry = geometry();
        isFullscreen = isFullScreen();

        // Creăm fereastra principală
        mainWindow = new MainWindow(this);

        // Setăm starea ferestrei noi
        if (isFullscreen) {
            mainWindow->showFullScreen();
        } else {
            mainWindow->setGeometry(savedGeometry);
            mainWindow->show();
        }

        // Conectăm semnalul pentru întoarcere
        connect(mainWindow, &MainWindow::backToStart, this, [this]() {
            mainWindow->close();

            // Restaurăm starea la revenirea în StartWindow
            if (isFullscreen) {
                showFullScreen();
            } else {
                setGeometry(savedGeometry);
                show();
            }
        });

        hide(); // Ascundem StartWindow
    });

    connect(credentialsButton, &QPushButton::clicked, this, [this]() {
        savedGeometry = geometry();
        isFullscreen = isFullScreen();

        // Creăm fereastra de credentiale
        credentialsWindow = new CredentialsWindow(this);

        // Setăm starea ferestrei noi
        if (isFullscreen) {
            credentialsWindow->showFullScreen();
        } else {
            credentialsWindow->setGeometry(savedGeometry);
            credentialsWindow->show();
        }

        // Conectăm semnalul pentru întoarcere
        connect(credentialsWindow, &CredentialsWindow::backToStart, this, [this]() {
            credentialsWindow->close();

            // Restaurăm starea la revenirea în StartWindow
            if (isFullscreen) {
                showFullScreen();
            } else {
                setGeometry(savedGeometry);
                show();
            }
        });

        hide(); // Ascundem StartWindow
    });
    // Setăm titlul ferestrei
    setWindowTitle("My Carbon App");

    // Centrăm fereastra pe ecran
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void StartWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    // Actualizăm dimensiunea imaginii să acopere întreaga fereastră
    QPixmap background(":/images/carbon_footprint.png");
    if (!background.isNull()) {
        backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    backgroundLabel->setGeometry(0, 0, width(), height());

    // Redimensionăm butoanele proporțional cu dimensiunea ferestrei (dar cu limită minimă și maximă)
    int buttonWidth = std::max(130, std::min(150, width() / 8));  // Minimum 130 px, maximum 150 px
    int buttonHeight = std::max(30, std::min(40, height() / 15)); // Minimum 30 px, maximum 40 px
    startButton->setFixedSize(buttonWidth, buttonHeight);
    credentialsButton->setFixedSize(buttonWidth, buttonHeight);

    // Calculăm coordonatele pentru poziționarea centrală
    int totalWidth = startButton->width() + credentialsButton->width() + 20; // Spațiu de 20 px între butoane
    int baseX = (width() - totalWidth) / 2; // Punctul de start pentru primul buton
    int buttonY = height() - startButton->height() - 40;

    // Repoziționăm butoanele
    startButton->move(baseX, buttonY);
    credentialsButton->move(baseX + startButton->width() + 20, buttonY); // Lângă Start Calculator
}


void StartWindow::startApplication()
{
    // Creăm și afișăm fereastra principală
    mainWindow = new MainWindow();
    mainWindow->show();

    // Închidem fereastra de start
    this->close();
}
