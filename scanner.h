#ifndef SCANNER_H
#define SCANNER_H

#include <QBluetoothDeviceDiscoveryAgent>
#include <QObject>
#include <QList>
#include <QVariant>
#include <device.h>


class Scanner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant devicesList READ getDevices NOTIFY devicesUpdated);
public:
    Scanner();
    Scanner(QObject *parent = nullptr);
    ~Scanner();
    QVariant getDevices();

public slots:
    void startDeviceDiscovery();
    void stopDeviceDiscovery();

private slots:
    // QBluetoothDevicDiscoveryAgent related
    void deviceScanFinished();
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);
    void addDevice(const QBluetoothDeviceInfo&);

Q_SIGNALS:
    void deviceFound(Device *d);
    void updateChanged();
    void devicesUpdated();

private:
    void setUpdate(const QString &message);
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList<QObject *> devices;
    QString m_message;
};

#endif // SCANNER_H
