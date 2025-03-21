QT       += \
    core gui \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/helpers/addplayer.cpp \
    src/aboutdialog.cpp \
    src/addplayerdialog.cpp \
    src/database.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/onstartupdialog.cpp \
    src/sectiondialog.cpp \
    src/setupdialog.cpp \
    src/tournamentdialog.cpp \


HEADERS += \
    src/helpers/headers/info.h \
    src/helpers/headers/addplayer.h \
    src/headers/aboutdialog.h \
    src/headers/addplayerdialog.h \
    src/headers/database.h \
    src/headers/mainwindow.h \
    src/headers/onstartupdialog.h \
    src/headers/sectiondialog.h \
    src/headers/setupdialog.h \
    src/headers/tournamentdialog.h \

FORMS += \
    src/forms/aboutdialog.ui \
    src/forms/addplayerdialog.ui \
    src/forms/mainwindow.ui \
    src/forms/sectiondialog.ui \
    src/forms/setupdialog.ui \
    src/forms/tournamentdialog.ui \
    src/forms/onstartupdialog.ui \

TRANSLATIONS += \
    translations/ChessFerret_en_US.ts \
    translations/ChessFerret_es_419.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES = application.qrc

