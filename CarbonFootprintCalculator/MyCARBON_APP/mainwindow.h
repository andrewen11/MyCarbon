#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showIndividualPage();
    void showHousePage();
    void showDietPage();
    void calculateIndividual();
    void calculateHouse();
    void calculateDiet();

private:
    QStackedWidget *stackedWidget;

    // Individual page widgets
    QWidget *individualPage;
    QLineEdit *breathsEdit;
    QLineEdit *distanceEdit;
    QComboBox *transportTypeCombo;
    QLabel *individualResultLabel;

    // House page widgets
    QWidget *housePage;
    QLineEdit *spaceEdit;
    QComboBox *houseTypeCombo;
    QLineEdit *electricityEdit;
    QLineEdit *gasEdit;
    QLineEdit *hotWaterEdit;
    QLineEdit *coldWaterEdit;
    QLabel *houseResultLabel;

    // Diet page widgets
    QWidget *dietPage;
    QComboBox *dietTypeCombo;
    QLabel *dietResultLabel;

    void setupUI();
    QWidget* createIndividualPage();
    QWidget* createHousePage();
    QWidget* createDietPage();
};

#endif // MAINWINDOW_H
