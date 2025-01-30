// main.cpp
// main.cpp
#include "startwindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartWindow startWindow;
    MainWindow mainWindow;

    // ✅ Connect the back button signal to show the start window again
    QObject::connect(&mainWindow, &MainWindow::backToStart, [&]() {
        mainWindow.hide();  // Hide the main window
        startWindow.show(); // Show the start window again
    });

    startWindow.show();
    return a.exec();
}
