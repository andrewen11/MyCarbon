#include "credentialswindow.h"
#include <QPixmap>
#include <QApplication>
#include <QScreen>

CredentialsWindow::CredentialsWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1000, 600);// Dimensiunea minimă

    // Creăm label-ul pentru imagine care acoperă întreaga fereastră
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width(), height()); // Inițial setăm dimensiunea să acopere întreaga fereastră

    // Încărcăm imaginea (înlocuiește cu calea către imaginea ta)
    QPixmap background(":/images/credentials_background.png");
    if (!background.isNull()) {
        backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    // Creăm butonul de întoarcere
    backButton = new QPushButton("Back to start menu", this);
    backButton->setFixedSize(150, 40);
    backButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    border-radius: 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #C70039;"
        "}"
        );

    // Poziționăm butonul manual în centrul de jos al ferestrei
    int buttonX = (width() - backButton->width()) / 2;
    int buttonY = height() - backButton->height() - 60;
    backButton->move(buttonX, buttonY);

    // Conectăm semnalul clicked al butonului la semnalul pentru întoarcere
    connect(backButton, &QPushButton::clicked, this, &CredentialsWindow::backToStart);

    // Setăm titlul ferestrei
    setWindowTitle("Credits - My Carbon App");
}

void CredentialsWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    // Actualizăm dimensiunea imaginii să acopere întreaga fereastră
    QPixmap background(":/images/credentials_background.png");
    if (!background.isNull()) {
        backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    backgroundLabel->setGeometry(0, 0, width(), height());

    // Setăm dimensiunea butonului dinamic
    int buttonWidth = std::max(200, width() / 6);  // Min 150px, max ~1/6 din lățimea ferestrei
    int buttonHeight = std::max(40, height() / 15); // Min 40px, max ~1/15 din înălțime
    backButton->setFixedSize(buttonWidth, buttonHeight);

    // Redimensionăm textul
    QString styleSheet = QString(
                             "QPushButton {"
                             "    background-color: #4CAF50;"
                             "    border: none;"
                             "    color: white;"
                             "    font-size: %1.5px;" // Font dinamic
                             "    border-radius: 20px;"
                             "}"
                             "QPushButton:hover {"
                             "    background-color: #C70039;"
                             "}"
                             ).arg(std::max(14, buttonHeight / 2));  // Min 14px, max ~jumătate din înălțimea butonului

    backButton->setStyleSheet(styleSheet);


    // Repoziționăm butonul în centrul de jos
    int buttonX = (width() - backButton->width()) / 2;
    int buttonY = height() - backButton->height() - 60; // Poziția normală

    // Ridicăm butonul cu 15-20 px în modul fullscreen
    //if (isFullScreen()) {
      //  buttonY -= 30; // Ridică butonul cu 15 px
    //}

    backButton->move(buttonX, buttonY);
}
