#include "info1.h"
#include <QPixmap>
#include <QApplication>
#include <QScreen>

InfoWindow::InfoWindow(QWidget *parent)
    : QMainWindow(parent), currentImageIndex(0) // Inițializăm indexul imaginii
{
    setMinimumSize(1000, 600);

    // Lista de imagini de fundal
    imagesList = {
        ":/images/info_background1.jpg",
        ":/images/info_background2.jpg",
        ":/images/info_background3.jpg",
        ":/images/info_background4.jpg",
        ":/images/info_background5.jpg",
        ":/images/info_background6.jpg",
        ":/images/info_background7.jpg",
        ":/images/info_background8.jpg"
    };

    // Fundal
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width(), height());

    // Buton "Previous" (Exit la prima imagine)
    previousButton = new QPushButton("Exit", this);
    connect(previousButton, &QPushButton::clicked, this, &InfoWindow::previousImage);

    // Buton "Next" (Exit la ultima imagine)
    nextButton = new QPushButton("Next", this);
    connect(nextButton, &QPushButton::clicked, this, &InfoWindow::nextImage);

    // Actualizăm fundalul și butoanele
    updateBackground();
    setWindowTitle("Information - My Carbon App");
}

void InfoWindow::updateBackground() {
    // Schimbăm imaginea de fundal conform `currentImageIndex`
    QPixmap background(imagesList[currentImageIndex]);
    if (!background.isNull()) {
        backgroundLabel->setPixmap(background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    backgroundLabel->setGeometry(0, 0, width(), height());

    // Gestionăm textul butoanelor
    if (currentImageIndex == 0) {
        previousButton->setText("Exit");
    } else {
        previousButton->setText("Previous");
    }

    if (currentImageIndex == imagesList.size() - 1) {
        nextButton->setText("Exit");
    } else {
        nextButton->setText("Next");
    }

    // Redimensionăm și repoziționăm butoanele
    updateButtonPositions();
}

void InfoWindow::updateButtonPositions() {
    // Calculăm dimensiunea butoanelor în funcție de dimensiunea ferestrei
    int buttonWidth = std::max(80, std::min(110, width() / 6)); // Min 150 px, Max 250 px
    int buttonHeight = std::max(20, std::min(33, height() / 12)); // Min 40 px, Max 60 px

    previousButton->setFixedSize(buttonWidth, buttonHeight);
    nextButton->setFixedSize(buttonWidth, buttonHeight);

    // Ajustăm fontul butoanelor în funcție de dimensiunea butonului
    int fontSize = std::max(14, buttonHeight / 3);
    previousButton->setStyleSheet(buttonStyle(fontSize));
    nextButton->setStyleSheet(buttonStyle(fontSize));

    // Calculăm poziția centralizată
    int totalWidth = previousButton->width() + nextButton->width() + 20; // Spațiu de 20 px între butoane
    int baseX = (width() - totalWidth) / 2;
    int buttonY = height() - previousButton->height() - 50; // Poziție cu margine inferioară de 50 px

    // Repoziționăm butoanele
    previousButton->move(baseX, buttonY);
    nextButton->move(baseX + previousButton->width() + 20, buttonY);
}

QString InfoWindow::buttonStyle(int fontSize) {
    return QString(
               "QPushButton {"
               "    background-color: #4CAF50;"
               "    border: none;"
               "    color: white;"
               "    font-size: 18px;"
               "    border-radius: 15px;"
               "    padding: 3px 3px 3px 3px;"
               "}"
               "QPushButton:hover {"
               "    background-color: #45a049;"
               "}").arg(fontSize);
}

void InfoWindow::nextImage() {
    if (currentImageIndex < imagesList.size() - 1) {
        currentImageIndex++;
        updateBackground();
    } else {
        close(); // La ultima imagine, Next devine Exit
    }
}

void InfoWindow::previousImage() {
    if (currentImageIndex > 0) {
        currentImageIndex--;
        updateBackground();
    } else {
        close(); // La prima imagine, Previous devine Exit
    }
}

void InfoWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    updateBackground();
}
