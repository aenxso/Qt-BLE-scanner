#ifndef DEVICE_H
#define DEVICE_H

#include <QDialog>

#include <qbluetoothdeviceinfo.h>
#include <qbluetoothaddress.h>

class Device : public QDialog
{
    Q_OBJECT
public:
    Device(const QBluetoothDeviceInfo &d);
    QString getAddress() const;
    QString getName() const;
    QBluetoothDeviceInfo getDevice();
    void setDevice(const QBluetoothDeviceInfo &dev);

Q_SIGNALS:
    void deviceChanged();

private:
    QBluetoothDeviceInfo device;
};

#endif // DEVICE_H
