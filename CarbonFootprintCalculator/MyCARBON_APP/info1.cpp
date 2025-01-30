#include "info1.h"
#include <QPixmap>
#include <QApplication>
#include <QScreen>

InfoWindow::InfoWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1000, 600);

    // Fundal
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width(), height());

    QPixmap background(":/images/info_background.png");
    if (!background.isNull()) {
        backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    // Buton "Back"
    backButton = new QPushButton("Back to Main Menu", this);
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

    int buttonX = (width() - backButton->width()) / 2;
    int buttonY = height() - backButton->height() - 60;
    backButton->move(buttonX, buttonY);

    connect(backButton, &QPushButton::clicked, this, &InfoWindow::backToStart);

    setWindowTitle("Information - My Carbon App");
}

void InfoWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    // Redimensionare imagine fundal
    QPixmap background(":/images/info_background.png");
    if (!background.isNull()) {
        backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    backgroundLabel->setGeometry(0, 0, width(), height());

    // Ajustare dimensiune buton
    int buttonWidth = std::max(200, width() / 6);
    int buttonHeight = std::max(40, height() / 15);
    backButton->setFixedSize(buttonWidth, buttonHeight);

    QString styleSheet = QString(
                             "QPushButton {"
                             "    background-color: #4CAF50;"
                             "    border: none;"
                             "    color: white;"
                             "    font-size: %1.5px;"
                             "    border-radius: 20px;"
                             "}"
                             "QPushButton:hover {"
                             "    background-color: #C70039;"
                             "}"
                             ).arg(std::max(14, buttonHeight / 2));

    backButton->setStyleSheet(styleSheet);

    // Repoziționare buton
    int buttonX = (width() - backButton->width()) / 2;
    int buttonY = height() - backButton->height() - 60;
    backButton->move(buttonX, buttonY);
}

void InfoWindow::backToStart() {
    close();
}
