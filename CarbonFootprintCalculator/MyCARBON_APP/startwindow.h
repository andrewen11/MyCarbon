// startwindow.h
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "mainwindow.h"
#include "credentialswindow.h"

class StartWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    StartWindow(QWidget *parent = nullptr);

private slots:
    void startApplication();

private:
    QLabel *backgroundLabel; // Etichetă pentru fundal
    QPushButton *startButton; // Butonul "Start Calculator"
    QPushButton *credentialsButton; // Butonul pentru accesarea ferestrei de autentificare
    MainWindow *mainWindow; // Fereastra principală
    CredentialsWindow *credentialsWindow; // Fereastra de autentificare
    QRect savedGeometry; // Salvează geometria curentă a ferestrei
    bool isFullscreen;   // Starea de fullscreen
};

#endif // STARTWINDOW_H
