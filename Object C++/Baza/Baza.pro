QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edycja.cpp \
    main.cpp \
    objawywin.cpp \
    obsluzbaze.cpp \
    pokazbaze.cpp \
    pokazpacjent.cpp \
    widget.cpp

HEADERS += \
    adres.h \
    choroba.h \
    data.h \
    edycja.h \
    lekarz.h \
    objawy.h \
    objawywin.h \
    obsluga.h \
    obsluzbaze.h \
    pacjent.h \
    pacjentstruct.h \
    pokazbaze.h \
    pokazpacjent.h \
    sprawdzPisanie.h \
    szyfrowanie.h \
    widget.h

FORMS += \
    edycja.ui \
    objawywin.ui \
    obsluzbaze.ui \
    pokazPacjent.ui \
    pokazbaze.ui \
    pokazpacjent.ui \
    pokazpacjent.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -LF:/Libsodium/x64/Debug/v141/dynamic/ -llibsodium

INCLUDEPATH += F:/Libsodium/include
DEPENDPATH += F:/Libsodium/include
