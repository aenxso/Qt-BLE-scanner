QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += quick bluetooth

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    batteryservice.cpp \
    controller.cpp \
    device.cpp \
    devicehandler.cpp \
    main.cpp \
    scanner.cpp

HEADERS += \
    batteryservice.h \
    controller.h \
    device.h \
    devicehandler.h \
    scanner.h

FORMS += \
    mainscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
