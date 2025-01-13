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
    void onTransportTypeChanged(int index);

private:

    QStackedWidget *stackedWidget;

    // Page widgets
    QWidget *individualPage;
    QWidget *housePage;
    QWidget *dietPage;

    // Individual page controls
    QLineEdit *breathsEdit;
    QLineEdit *distanceEdit;
    QComboBox *transportTypeCombo;
    QComboBox *fuelTypeCombo;
    QComboBox *publicTransportCombo;
    QLabel *individualResultLabel;

    // House page controls
    QLineEdit *spaceEdit;
    QComboBox *houseTypeCombo;
    QLineEdit *electricityEdit;
    QLineEdit *gasEdit;
    QLineEdit *hotWaterEdit;
    QLineEdit *coldWaterEdit;
    QLabel *houseResultLabel;

    // Diet page controls
    QComboBox *dietTypeCombo;
    QLabel *dietResultLabel;

    void setupUI();
    QWidget* createIndividualPage();
    QWidget* createHousePage();
    QWidget* createDietPage();
};

#endif // MAINWINDOW_H
