#ifndef INFO1_H
#define INFO1_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class InfoWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *backgroundLabel;
    QPushButton *backButton;
    QVector<QString> imagesList; // Stocăm căile către imagini
    int currentImageIndex; // Indexul imaginii curente
    QPushButton *previousButton; // ❗ Declarăm butonul Previous
    QPushButton *nextButton;     // ❗ Declarăm butonul Next

    void updateBackground(); // Actualizează imaginea și butoanele
    void updateButtonPositions(); // Repoziționează și redimensionează butoanele
    QString buttonStyle(int fontSize = 16); // Returnează stilul butoanelor

private slots:
    //void backToStart();
    void nextImage();
    void previousImage();
};
#endif // INFO1_H
