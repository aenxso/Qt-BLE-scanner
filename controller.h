#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <device.h>
#include <devicehandler.h>
#include <scanner.h>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject *parent = nullptr);

private slots:
    void onDeviceFound(Device*);
    void batteryServiceReady();
    void batteryLevelChanged(quint8 level);

private:
    Device *m_device;
    DeviceHandler *m_deviceHandler;
    Scanner *m_scanner;
    BatteryService *m_batteryService;
};

#endif // CONTROLLER_H
