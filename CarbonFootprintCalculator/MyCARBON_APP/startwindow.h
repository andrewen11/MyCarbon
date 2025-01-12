// startwindow.h
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "mainwindow.h"

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

private slots:
    void startApplication();

private:
    QPushButton *startButton;
    MainWindow *mainWindow;
    QLabel *backgroundLabel;
};

#endif // STARTWINDOW_H
