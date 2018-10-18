QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webidl2cpp
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

OTHER_FILES += \
        source/main.cpp \
        source/application/window.cpp \
        source/application/window.h \
        source/application/window.ui

win32 {
    SOURCES = \
            source/main.cpp \
            source/application/window.cpp

    HEADERS = \
            source/application/window.h

    FORMS = \
            source/application/window.ui
 }

# Project created by 2018-10-16T21:31:59

FORMS += \
    source/application/output.ui \
    source/application/options.ui \
    source/application/finish.ui

HEADERS += \
    source/application/output.h \
    source/application/options.h \
    source/application/finish.h

SOURCES += \
    source/application/output.cpp \
    source/application/options.cpp \
    source/application/finish.cpp
