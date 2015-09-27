#include "MCU_Connector.h"

MCU_Connector::MCU_Connector(QObject *parent) :
    QObject(parent)
{
    connect(&mcuPort,SIGNAL(readyRead()),this,SLOT(serialHandler()));
    connect(&mcuPort,SIGNAL(aboutToClose()),this,SLOT(serialAboutToClose()));
}

void MCU_Connector::startConnection(){

    sysPorts = QSerialPortInfo::availablePorts();

//    for(QSerialPortInfo port : sysPorts){
//        if (port.manufacturer().contains("arduino",Qt::CaseInsensitive)
//            | (port.portName() == QString("ttyUSB0"))
//            | (port.portName() == QString("rfcomm0")) )
//                mcuPorts.append(port);
//    }

    for (int i = 0; i<sysPorts.length(); i++){
        //Debug
        qDebug() << sysPorts.at(i).manufacturer();
        qDebug() << sysPorts.at(i).description();
        qDebug() << sysPorts.at(i).portName();
        qDebug() << sysPorts.at(i).vendorIdentifier();
        qDebug() << sysPorts.at(i).productIdentifier();
        //
        if (sysPorts.at(i).manufacturer().contains("arduino",Qt::CaseInsensitive)
            | (sysPorts.at(i).portName() == QString("ttyUSB0"))
            | (sysPorts.at(i).portName() == QString("rfcomm0")) )
                mcuPorts.append(sysPorts.at(i));
    }

    if (mcuPorts.length() == 0) emit statusMessenger("No Microcontroller port was found.");

    else if (mcuPorts.length() > 1); //TODO: Show some panel to user chose the port.

         else {
                mcuPort.setPort(mcuPorts.at(0));

                if(open_port(mcuPort)){
                    emit statusMessenger("Port "+mcuPort.portName()+" openned sucessfully.",3000);
                    mcuPort.write("CR"); //Get inicial relay state from microcontroller
                }
                else
                    emit statusMessenger(mcuPort.errorString(),3000);
              }
}

bool MCU_Connector::open_port(QSerialPort &port){

    port.setBaudRate(QSerialPort::Baud9600);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.open(QIODevice::ReadWrite);
    return port.isOpen();
}

void MCU_Connector::setRelayState(bool newState){
    if(mcuPort.isOpen()){
        if(newState) mcuPort.write(QByteArray("R"));
        else mcuPort.write(QByteArray("r"));
    }
}

void MCU_Connector::switchClicked(bool state){
    if(state!=relayState) setRelayState(state);
}

void MCU_Connector::serialAboutToClose(){
    emit statusMessenger("Port closed.");
}

void MCU_Connector::serialHandler(){

    dataIn.append(mcuPort.readAll());
    if (dataIn.contains('#')){

        if(dataIn.contains("RelayON")) {
            relayState = true;
            emit relayStateChanged(relayState);
        }
        else if(dataIn.contains("RelayOFF")) {
            relayState = false;
            emit relayStateChanged(relayState);
        }
        else if(dataIn.contains("LumLevel")) {
            lumLevel = 100 - dataIn.mid(8).remove(dataIn.length()-9,1).toInt()/10.23;
            emit lumLevelChanded(lumLevel);
        }
        else if(dataIn.contains("VolUp")){
            system("amixer -q sset 'Master' 3%+");
        }
        else if(dataIn.contains("VolDown")){
            system("amixer -q sset 'Master' 3%-");
        }
        qDebug() << dataIn.data();
        dataIn.clear();
    }
}

MCU_Connector::~MCU_Connector(){
    mcuPort.close();
}
