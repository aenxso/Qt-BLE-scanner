#include "device.h"

#include <qbluetoothuuid.h>

Device::Device(const QBluetoothDeviceInfo &d) {
    device = d;
}

QString Device::getAddress() const {
    return device.address().toString();
}

QString Device::getName() const {
    return device.name();
}

QBluetoothDeviceInfo Device::getDevice() {
    return device;
}

void Device::setDevice(const QBluetoothDeviceInfo &dev) {
    device = QBluetoothDeviceInfo(dev);
    Q_EMIT deviceChanged();
}
