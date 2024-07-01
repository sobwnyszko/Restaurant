QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dodawanie_pracownikow.cpp \
    kelner.cpp \
    kucharz.cpp \
    main.cpp \
    mainwindow.cpp \
    menedzer.cpp \
    menu.cpp \
    potrawy.cpp \
    sekretarka.cpp \
    stoliki.cpp

HEADERS += \
    databaseManager.h \
    dodawanie_pracownikow.h \
    kelner.h \
    kucharz.h \
    mainwindow.h \
    menedzer.h \
    menu.h \
    potrawy.h \
    sekretarka.h \
    stoliki.h

FORMS += \
    dodawanie_pracownikow.ui \
    kelner.ui \
    kucharz.ui \
    mainwindow.ui \
    menedzer.ui \
    menu.ui \
    potrawy.ui \
    sekretarka.ui \
    stoliki.ui

TRANSLATIONS += \
    Bazy_danych_pl_PL.ts
CONFIG += lrelease
CONFIG += embed_translations


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
