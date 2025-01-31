#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QPainter>
#include <QInputDialog>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QMap>
#include <QStackedWidget>
#include <QLabel>
#include <QScrollArea>
#include "info1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void onTransportTypeChanged(QListWidgetItem *item);
    void onPublicTransportChanged(QListWidgetItem *item);
    void resizeEvent(QResizeEvent *event);
    void onWasteTypeChanged(QListWidgetItem *item);
    void openInfoWindow();
    void goBack();  // ✅ Slot to handle back button action
    void showDietCarbonFootprintPopup(double totalFoodCO2, const QString &carbonDetails);

private:

    QStackedWidget *stackedWidget;

    // Page widgets
    QWidget *individualPage;
    QWidget *housePage;
    QWidget *dietPage;

    QWidget *containerWidget; // Declarația variabilei
    // Individual page controls
    QLineEdit *breathsEdit;
    QLineEdit *distanceEdit;
    QComboBox *fuelTypeCombo;
    QListWidget *publicTransportCombo;
    QMap<QString, QLineEdit*> publicTransportDistances;
    QMap<QString, QLabel*> publicTransportLabels; // Hărțile pentru etichetele transportului public
    QLabel *publicTransportLabel; // Etichetă pentru "Select Public Transport"
    QLabel *individualResultLabel;

    // House page controls
    QLineEdit *spaceEdit;
    QComboBox *houseTypeCombo;
    QLineEdit *electricityEdit;
    QLineEdit *gasEdit;
    QLineEdit *hotWaterEdit;
    QLineEdit *coldWaterEdit;
    QLabel *houseResultLabel;
    QLineEdit *woodEdit;       // 🔥 Câmp pentru consumul de lemne
    QLineEdit *numPersonsEdit;
    QComboBox *countryCombo;   // 🔥 ComboBox pentru selecția țării

    // Diet page controls
    QComboBox *dietTypeCombo;
    QLabel *dietResultLabel;
    QLabel *backgroundLabel;
    QPixmap originalBackground;
    QMap<QString, QLineEdit*> foodInputs;
    void updateBackground();

    // Waste section
    QGroupBox *wasteGroupBox;
    QListWidget *wasteTypeList;
    QFormLayout *wasteFormLayout;
    QMap<QString, QComboBox*> wasteDisposalInputs;
    QMap<QString, QLineEdit*> wasteAmountInputs;
    QMap<QString, QLabel*> wasteAmountLabels;
    QMap<QString, QLabel*> wasteMethodLabels;
    QLabel *wasteTitleLabel;

    void setupUI();
    QWidget* createIndividualPage();
    QWidget* createHousePage();
    QWidget* createDietPage();
    QVBoxLayout *individualLayout;

    QListWidget *transportTypeList;  // List of checkboxes for transport
    QFormLayout *transportFormLayout;  // Holds input fields dynamically
    QMap<QString, QLineEdit*> distanceInputs;  // Stores distance inputs for each transport
    QMap<QString, QComboBox*> fuelInputs;  // Stores fuel inputs (for cars)
    QMap<QString, QLabel*> distanceLabels;  // Stochează etichetele pentru distanțe
    QMap<QString, QLabel*> fuelLabels;      // Stochează etichetele pentru combustibili
    QPushButton *backButton;
    QPushButton *infoButton;

    InfoWindow *infoWindow;

signals:
    void backToStart();
};

#endif // MAINWINDOW_H
