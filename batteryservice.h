#ifndef BATTERYSERVICE_H
#define BATTERYSERVICE_H

#include <QObject>
#include <QBluetoothUuid>
#include <QLowEnergyService>
#include <QLowEnergyController>

class BatteryService : public QObject
{
    Q_OBJECT
public:
    BatteryService(QObject *parent = nullptr);

    quint8 level();

    void serviceDiscovered(const QBluetoothUuid &uuid);
    void serviceScanDone(QLowEnergyController *control);
    void disconnectService();

Q_SIGNALS:
    void levelChanged(quint8 newLevel);
    void ready();

private slots:
    void serviceStateChanged(QLowEnergyService::ServiceState state);
    void characteristicChanged(const QLowEnergyCharacteristic &ch, const QByteArray &val);
    void characteristicRead(const QLowEnergyCharacteristic &ch, const QByteArray &val);
    void descriptorWritten(const QLowEnergyDescriptor &d, const QByteArray &val);

protected:
    void onServiceDiscovered();
    void onCharacteristicChanged(const QLowEnergyCharacteristic &ch, const QByteArray &val);
    void onCharacteristicRead(const QLowEnergyCharacteristic &ch, const QByteArray &val);

    bool m_foundService;
    QLowEnergyService *m_service = nullptr;
    QBluetoothUuid m_uuid = QBluetoothUuid::ServiceClassUuid::BatteryService;

private:
    QLowEnergyCharacteristic m_levelChar;
    QLowEnergyDescriptor notification;

};

#endif // BATTERYSERVICE_H
