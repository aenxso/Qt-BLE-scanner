#include "batteryservice.h"

#include <QDebug>

BatteryService::BatteryService(QObject *parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO << __FILE__ << __LINE__;
}

void BatteryService::onServiceDiscovered() {
    m_levelChar = m_service->characteristic(QBluetoothUuid::CharacteristicType::BatteryLevel);
    qDebug() << "Valid characteristic: " << m_levelChar.isValid();

    notification = m_levelChar.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);
    qDebug() << "Valid notif: " << notification.isValid();
    m_service->writeDescriptor(notification, QByteArray::fromHex("0100"));
}

quint8 BatteryService::level() {
    if(m_service && m_levelChar.isValid()) {
        QByteArray value = m_levelChar.value();
        return value.at(0);
    } else {
        return 0;
    }
}

void BatteryService::onCharacteristicChanged(const QLowEnergyCharacteristic &ch, const QByteArray &val) {
    if(ch.uuid() == QBluetoothUuid::CharacteristicType::BatteryLevel) {
        quint8 value = val[0];
        emit levelChanged(value);
    }
}

void BatteryService::onCharacteristicRead(const QLowEnergyCharacteristic &ch, const QByteArray &val) {
    if(ch.uuid() == QBluetoothUuid::CharacteristicType::BatteryLevel) {
        quint8 value = val[0];
        emit levelChanged(value);
    }
}

void BatteryService::serviceDiscovered(const QBluetoothUuid &uuid) {
    if(uuid == m_uuid) {
        qDebug() << "Found battery service";
        m_foundService = true;
    }
}

void BatteryService::serviceScanDone(QLowEnergyController *control) {
    if(m_service) {
        delete m_service;
        m_service = 0;
    }

    if(m_foundService) {
        m_service = control->createServiceObject(m_uuid, this);
    }

    if(m_service) {
        connect(m_service, &QLowEnergyService::stateChanged, this, &BatteryService::serviceStateChanged);
        connect(m_service, &QLowEnergyService::characteristicChanged, this, &BatteryService::characteristicChanged);
        connect(m_service, &QLowEnergyService::characteristicRead, this, &BatteryService::characteristicRead);
        connect(m_service, &QLowEnergyService::descriptorWritten, this, &BatteryService::descriptorWritten);
        m_service->discoverDetails();
    }
}

void BatteryService::disconnectService() {
    qDebug() << "Disconnect from service";
    m_foundService = false;
    delete m_service;
    m_service = nullptr;
}

void BatteryService::serviceStateChanged(QLowEnergyService::ServiceState state) {
    if(state == QLowEnergyService::ServiceState::ServiceDiscovered) { // apparently servicediscovered was deprecated and renamed to RemoteServiceDiscovered but this thing is rejecting that
        onServiceDiscovered();
    }
}

void BatteryService::characteristicChanged(const QLowEnergyCharacteristic &ch, const QByteArray &val) {
    onCharacteristicRead(ch, val);
}

void BatteryService::characteristicRead(const QLowEnergyCharacteristic &ch, const QByteArray &val) {
    onCharacteristicRead(ch, val);
}

void BatteryService::descriptorWritten(const QLowEnergyDescriptor &d, const QByteArray &val) {
    qDebug() << "Descriptor: " << d.name();
    qDebug() << "Value: " << val;

    m_service->readCharacteristic(m_levelChar);

    if(m_levelChar.isValid()) {
            emit ready();
    }
}




