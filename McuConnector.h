#ifndef MCU_CONNECTOR_H
#define MCU_CONNECTOR_H

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class MCU_Connector : public QObject
{
    Q_OBJECT

public:
    QList<QSerialPortInfo> sysPorts;
    QList<QSerialPortInfo> mcuPorts;
    QSerialPort mcuPort;
    QByteArray dataIn;
    bool relayState;
    int lumLevel = 0;

    explicit MCU_Connector(QObject *parent = 0);

    void startConnection();

    bool open_port(QSerialPort &port);

    void setRelayState(bool newState);

    ~MCU_Connector();

signals:
    void relayStateChanged(bool newState);
    void lumLevelChanded(int newLightLevel);
    void statusMessenger(QString msg, int timeout = 0);

private slots:
    void serialHandler();
    void serialAboutToClose();

public slots:
    void switchClicked(bool state);

};

#endif // MCU_CONNECTOR_H
