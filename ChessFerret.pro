QT       += \
    core gui \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addplayerdialog.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    sectiondialog.cpp \
    setupdialog.cpp \
    tournamentdialog.cpp

HEADERS += \
    addplayerdialog.h \
    database.h \
    mainwindow.h \
    sectiondialog.h \
    setupdialog.h \
    tournamentdialog.h

FORMS += \
    addplayerdialog.ui \
    mainwindow.ui \
    sectiondialog.ui \
    setupdialog.ui \
    tournamentdialog.ui

TRANSLATIONS += \
    ChessFerret_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    configs/default-config.txt
    configs/personal-config.txt
