#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabPress = new QKeyEvent(QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);
    keyA = new QKeyEvent(QEvent::KeyPress,Qt::Key_A,Qt::NoModifier);
    nano.open("/dev/rfcomm0");
    tank.open("/dev/rfcomm1");
}

MainWindow::~MainWindow()
{
    nano.close();
    delete(this->tabPress);
    delete(this->keyA);
    delete ui;
}

void MainWindow::sendNano(int i){
    nano << i;
    nano.flush();

}

void MainWindow::on_pushButton_clicked()
{
    sendNano(1);
    ui->statusBar->showMessage("Ligada");
    QApplication::sendEvent(this, tabPress);
}

void MainWindow::on_pushButton_2_clicked()
{
    sendNano(0);
    ui->statusBar->showMessage("Desligada");
    QApplication::sendEvent(this, tabPress);
}
