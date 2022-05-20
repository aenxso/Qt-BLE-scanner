#include "scanner.h"

#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothservicediscoveryagent.h>
#include <QDebug>
#include <QList>
#include <QMetaEnum>
#include <QTimer>

Scanner::Scanner(QObject *parent) : QObject(parent) {
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    // connect(ui->scan, &QAbstractButton::clicked, this, &DeviceDiscoveryDialog::startDeviceDiscovery );

    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Scanner::addDevice);
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000);
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &Scanner::deviceScanError);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &Scanner::deviceScanFinished);

    setUpdate("Search");
}

Scanner::~Scanner() {
    delete discoveryAgent;
    qDeleteAll(devices);
    devices.clear();
}

void Scanner::addDevice(const QBluetoothDeviceInfo &info) {
    if(info.coreConfigurations() &QBluetoothDeviceInfo::LowEnergyCoreConfiguration
            && info.serviceUuids().contains(QBluetoothUuid::ServiceClassUuid::BatteryService)) {
         setUpdate("Last device added: " + info.name());
    }
    Device *dev = new Device(info); // may be redundant with devicescanfinished
    devices.append(dev);
    emit deviceFound(dev);
}

void Scanner::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error) {
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        setUpdate("The Bluetooth adaptor is powered off, power it on before doing discovery.");
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        setUpdate("Writing or reading from the device resulted in an error.");
    else {
        static QMetaEnum qme = discoveryAgent->metaObject()->enumerator(
                    discoveryAgent->metaObject()->indexOfEnumerator("Error"));
        setUpdate("Error: " + QLatin1String(qme.valueToKey(error)));
    }

    emit devicesUpdated();
}

void Scanner::startDeviceDiscovery() {
    qDeleteAll(devices);
    devices.clear();
    emit devicesUpdated();

    setUpdate("Scanning for devices...");

    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void Scanner::stopDeviceDiscovery() {
    discoveryAgent->stop();
}

void Scanner::deviceScanFinished() {
    const QList<QBluetoothDeviceInfo> foundDevices = discoveryAgent->discoveredDevices();
    for(auto dev : foundDevices) {
        if(dev.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) { // & is a bitwise operator, not boolean
            devices.append(new Device(dev));
        }
    }
    emit devicesUpdated();
}

void Scanner::setUpdate(const QString &message) {
    m_message = message;
    emit updateChanged();
}

QVariant Scanner::getDevices() {
    // return devices
    return QVariant::fromValue(devices);
}


