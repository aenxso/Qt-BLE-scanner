#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <device.h>
#include <batteryservice.h>

#include <QObject>
#include <QLowEnergyController>
#include <QLowEnergyService>

class DeviceHandler : public QObject
{
    Q_OBJECT
public:
    DeviceHandler(QObject *parent = nullptr);
    void setDevice(Device *d);
    bool isConnected();
    Device *currentDevice();
    BatteryService *batteryService();

Q_SIGNALS:
    void connected();
    void disconnected();
    void error(QLowEnergyController::Error);
    void servicesDiscovered();
    void currentDeviceChanged();

public slots:
    void disconnectService();

private slots:
    void deviceConnected();
    void deviceDisconnected();
    void connectionError(QLowEnergyController::Error error);

private:
    QLowEnergyController *m_control;
    Device *m_currentDevice;
    BatteryService *m_batteryService;

    bool m_isConnected;

    void serviceDiscovered(const QBluetoothUuid&);
    void serviceScanDone();
    void startConnect();

    void serviceStateChanged(QLowEnergyService::ServiceState state);
    void confirmedDescriptorWrite(const QLowEnergyDescriptor &d, const QByteArray &val);
};

#endif // DEVICEHANDLER_H
