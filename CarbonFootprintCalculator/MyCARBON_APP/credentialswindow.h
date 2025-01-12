#ifndef CREDENTIALSWINDOW_H
#define CREDENTIALSWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class CredentialsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CredentialsWindow(QWidget *parent = nullptr);
    ~CredentialsWindow() {}

private:
    QLabel *backgroundLabel;
    QPushButton *backButton;

signals:
    void backToStart();

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CREDENTIALSWINDOW_H
