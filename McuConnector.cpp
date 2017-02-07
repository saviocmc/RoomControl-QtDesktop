#include "McuConnector.h"

McuConnector::McuConnector(QObject *parent) : QObject(parent){

    connect(&mcuPort,SIGNAL(readyRead()),this,SLOT(serialIncomingHandler()));
    connect(&mcuPort,SIGNAL(aboutToClose()),this,SLOT(serialAboutToClose()));

}

bool openPort(QSerialPort &port){

    port.setBaudRate(QSerialPort::Baud9600);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.open(QIODevice::ReadWrite);
    return port.isOpen();

}


void McuConnector::startConnection(){

    QList<QSerialPortInfo> mcuPorts;

    for (QSerialPortInfo port : QSerialPortInfo::availablePorts()){

        //Debug
        qDebug() << port.portName();
        qDebug() << port.description();
        qDebug() << port.manufacturer();
        qDebug() << port.vendorIdentifier();
        qDebug() << port.productIdentifier();
        qDebug() << "\n";
        //
        if (port.manufacturer().contains("arduino",Qt::CaseInsensitive)
                | (port.portName() == "rfcomm28"))
                mcuPorts.append(port);
    }

    if (mcuPorts.length() == 0) emit statusMessenger("No Microcontroller port was found.");

    else if (mcuPorts.length() > 1)
        emit statusMessenger("There are more than one port available");
        //TODO: Show the list of ports, letting the user choose the right MCU port.

    else {
        mcuPort.setPort(mcuPorts.at(0));
        if(openPort(mcuPort)){
            emit statusMessenger("Port "+mcuPort.portName()+" opened successfully.");
            mcuPort.write("CR"); //Get inicial relay state from microcontroller
        } else
            emit statusMessenger(mcuPort.errorString());
    }
}

void McuConnector::setRelayState(bool state){
    if(mcuPort.isOpen() && state!=relayState){
        if(state) mcuPort.write(QByteArray("R"));
        else mcuPort.write(QByteArray("r"));
    }
}

void McuConnector::serialAboutToClose(){
    emit statusMessenger("Port closed");
}

void McuConnector::serialIncomingHandler(){

    static QByteArray incoming;

    incoming.append(mcuPort.readAll());
    if (incoming.contains('#')){

        if(incoming.contains("RelayON")) {
            relayState = true;
            emit relayStateChanged(relayState);
        }
        else if(incoming.contains("RelayOFF")) {
            relayState = false;
            emit relayStateChanged(relayState);
        }
        else if(incoming.contains("LumLevel")) {
            lumLevel = 100 - incoming.mid(8).remove(incoming.length()-9,1).toInt()/10.23;
            emit lumLevelChanded(lumLevel);
        }
        else if(incoming.contains("VolUp")){
            system("amixer -q sset 'Master' 3%+");
        }
        else if(incoming.contains("VolDown")){
            system("amixer -q sset 'Master' 3%-");
        }
        qDebug() << incoming.data();
        incoming.clear();
    }
}

McuConnector::~McuConnector(){
    mcuPort.close();
}
