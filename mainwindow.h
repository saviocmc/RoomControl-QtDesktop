#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QKeyEvent>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QAbstractButton>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalScrollBar_sliderReleased();

    void showSerial();

private:
    Ui::MainWindow *ui;
    std::ofstream nano;
    QKeyEvent *tabPress;
    QList<QSerialPortInfo> ports;
    QSerialPort uno;
};

#endif // MAINWINDOW_H
