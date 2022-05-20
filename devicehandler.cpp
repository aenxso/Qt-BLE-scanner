#include "devicehandler.h"

DeviceHandler::DeviceHandler(QObject *parent) : QObject(parent)
{
    m_control = nullptr;
    m_currentDevice = nullptr;
    m_isConnected = false;
    m_batteryService = new BatteryService();

//    QObject::connect
}

void DeviceHandler::setDevice(Device *device) {
    if(m_currentDevice != device) {
        m_currentDevice = device;
        emit currentDeviceChanged();
    }
}

void DeviceHandler::startConnect() {
    if(m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = 0;
    }

    if(m_currentDevice) {
        m_control = QLowEnergyController::createCentral(m_currentDevice->getDevice());
        m_control->setRemoteAddressType(QLowEnergyController::PublicAddress);
        connect(m_control, &QLowEnergyController::serviceDiscovered, this, &DeviceHandler::serviceDiscovered);
        connect(m_control, &QLowEnergyController::discoveryFinished, this, &DeviceHandler::serviceScanDone);
        connect(m_control, &QLowEnergyController::connected, this, &DeviceHandler::deviceConnected);
        connect(m_control, &QLowEnergyController::disconnected, this, &DeviceHandler::deviceDisconnected);

        m_control->connectToDevice();
    }
}

void DeviceHandler::connectionError(QLowEnergyController::Error err) {
    emit error(err);
}

void DeviceHandler::deviceConnected() {
    m_isConnected = true;
    emit connected();
    m_control->discoverServices();
}

void DeviceHandler::deviceDisconnected() {
    m_isConnected = false;
    emit disconnected();
    // recconnecct
}

bool DeviceHandler::isConnected() {
    return m_isConnected;
}

Device *DeviceHandler::currentDevice() {
    return m_currentDevice;
}

void DeviceHandler::serviceDiscovered(const QBluetoothUuid &gatt) {
    m_batteryService->serviceDiscovered(gatt);
}

void DeviceHandler::serviceScanDone() {
    m_batteryService->serviceScanDone(m_control);

    emit servicesDiscovered();
}

BatteryService *DeviceHandler::batteryService() {
    return m_batteryService;
}

void DeviceHandler::disconnectService() {
    m_batteryService->disconnectService();

    if(m_control) {
        m_control->disconnectFromDevice();
    }
}
