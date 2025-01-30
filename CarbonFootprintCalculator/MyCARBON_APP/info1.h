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

private slots:
    void backToStart();
};
#endif // INFO1_H
