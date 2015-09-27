#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QEvent>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabPress = new QKeyEvent(QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);

    uno.setPortName("/dev/ttyACM0");
    uno.open(QIODevice::ReadWrite);
    uno.setBaudRate(QSerialPort::Baud115200);
    uno.setDataBits(QSerialPort::Data8);
    uno.setParity(QSerialPort::NoParity);
    uno.setStopBits(QSerialPort::OneStop);
    uno.setFlowControl(QSerialPort::NoFlowControl);

    /*foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
              qDebug() << "Name        : " << info.portName();
              qDebug() << "Description : " << info.description();
              qDebug() << "Manufacturer: " << info.manufacturer();
    }*/

    if (uno.isOpen() && uno.isWritable()) qDebug() << "Ready...";
    else qDebug() << "Not connected...";
    QObject::connect(&uno, SIGNAL(readyRead()),this,SLOT(showSerial()));
}

MainWindow::~MainWindow()
{
    uno.close();
    delete (this->tabPress);
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    char svalue[4];
    sprintf(svalue,"%d",value);
    QString command = "amixer -q sset 'Master' ";
    command.append(svalue);
    command.append("%");
    ui->label_2->setText(svalue);
    system(command.toStdString().c_str());
}

void MainWindow::on_horizontalScrollBar_sliderReleased()
{
    static bool lampState = 0;
    if(lampState){
        if(ui->horizontalScrollBar->value() < 80 && (uno.isOpen() && uno.isWritable())){
            QByteArray msg("0");
            uno.write(msg);
            uno.flush();
            //ui->label_3->setText("            OFF");
            ui->horizontalScrollBar->setValue(0);
            lampState=!lampState;
        }
    }
    else{
        if(ui->horizontalScrollBar->value() > 20 && (uno.isOpen() && uno.isWritable())){
            QByteArray msg("1");
            uno.write(msg);
            uno.flush();
            //ui->label_3->setText("    ON");
            ui->horizontalScrollBar->setValue(100);
            lampState=!lampState;

        }
    }
}

void MainWindow::showSerial(){
    //if(uno.waitForReadyRead(0)){
        QByteArray dados = uno.readLine();
        qDebug() << dados.data();
    //}
    //qDebug() << "Fim da Linha";
}
