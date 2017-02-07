#ifndef MCU_CONNECTOR_H
#define MCU_CONNECTOR_H

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class McuConnector : public QObject
{
private:
    Q_OBJECT
    QSerialPort mcuPort;
    bool relayState;
    int lumLevel = 0;

public:
    explicit McuConnector(QObject *parent = 0);
    void startConnection();
    ~McuConnector();

signals:
    void relayStateChanged(bool newState);
    void lumLevelChanded(int newLightLevel);
    void statusMessenger(QString msg, int timeout = 3000);

private slots:
    void serialIncomingHandler();
    void serialAboutToClose();

public slots:
    void setRelayState(bool newState);

};

#endif // MCU_CONNECTOR_H
