// startwindow.cpp
#include "startwindow.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QWidget>
#include <QApplication>
#include <QScreen>
#include <QPalette>

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Setăm dimensiunea ferestrei
    resize(800, 600);

    // Creăm un widget central
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Creăm layout-ul principal
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Adăugăm label-ul pentru imagine
    backgroundLabel = new QLabel(this);

    // Încărcăm imaginea (înlocuiește cu calea către imaginea ta)
    QPixmap background(":/images/carbon_footprint.jpg");
    if (!background.isNull()) {
        // Scalăm imaginea să se potrivească cu fereastra păstrând aspectul
        backgroundLabel->setPixmap(background.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        backgroundLabel->setAlignment(Qt::AlignCenter);
    }

    // Creăm butonul de start
    startButton = new QPushButton("Start Calculator", this);
    startButton->setFixedSize(200, 50);
    startButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    border: none;"
        "    color: white;"
        "    padding: 5px 10px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 16px;"
        "    margin: 4px 2px;"
        "    border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    // Adăugăm widget-urile în layout
    mainLayout->addWidget(backgroundLabel);
    mainLayout->addWidget(startButton, 0, Qt::AlignCenter);

    // Conectăm semnalul clicked al butonului
    connect(startButton, &QPushButton::clicked, this, &StartWindow::startApplication);

    // Setăm titlul ferestrei
    setWindowTitle("Calculator Amprentă de Carbon");

    // Centrăm fereastra pe ecran
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void StartWindow::startApplication()
{
    // Creăm și afișăm fereastra principală
    mainWindow = new MainWindow();
    mainWindow->show();

    // Închidem fereastra de start
    this->close();
}
