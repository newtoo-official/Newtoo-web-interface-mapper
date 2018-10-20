QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webidl2cpp
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

# Project created by 2018-10-16T21:31:59

FORMS += \
    source/application/window.ui \
    source/application/output.ui \
    source/application/options.ui \
    source/application/finish.ui \
    source/application/about.ui

HEADERS += \
    source/application/window.h \
    source/application/output.h \
    source/application/options.h \
    source/application/finish.h \
    source/application/about.h

SOURCES += \
    source/application/window.cpp \
    source/application/output.cpp \
    source/application/options.cpp \
    source/application/finish.cpp \
    source/application/about.cpp \
    source/main.cpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/icon.png \
    resources/app_icon.ico
