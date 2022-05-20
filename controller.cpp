#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    m_device = nullptr;
    m_deviceHandler = new DeviceHandler();
    m_scanner = new Scanner(this);
    m_batteryService = m_deviceHandler->batteryService();

    connect(m_scanner, SIGNAL(deviceFound(Device*)), this, SLOT(onDeviceFound(Device*)));

    m_scanner->startDeviceDiscovery();
}

void Controller::onDeviceFound(Device *d) {
    m_scanner->stopDeviceDiscovery();
    m_deviceHandler->setDevice(d);
    qInfo() << d->getName() <<" found.";
    connect(m_batteryService, SIGNAL(ready()), this, SLOT(batteryServiceReady()));
    connect(m_batteryService, &BatteryService::levelChanged, this, &Controller::batteryLevelChanged);
}

void Controller::batteryServiceReady() {
    auto batteryLevel = m_batteryService->level();
    qInfo() << "Battery service: ";
    qInfo() << " level = " << batteryLevel;
}

void Controller::batteryLevelChanged(quint8 level) {
    qInfo() << "Battery percentage changed to " << level << "%";
}
