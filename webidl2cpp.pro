QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewtooWebInterfaceMapper
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
    source/application/about.h \
    source/shared/settings.h \
    source/application/log.h \
    source/core/definition.h \
    source/core/idl.h \
    source/core/definitionlist.h \
    source/core/interface.h \
    source/core/extattr.h \
    source/core/extattrmap.h

SOURCES += \
    source/application/window.cpp \
    source/application/output.cpp \
    source/application/options.cpp \
    source/application/finish.cpp \
    source/application/about.cpp \
    source/main.cpp \
    source/shared/settings.cpp \
    source/application/log.cpp \
    source/core/definition.cpp \
    source/core/idl.cpp \
    source/core/definitionlist.cpp \
    source/core/interface.cpp \
    source/core/extattr.cpp \
    source/core/extattrmap.cpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/icon.png \
    resources/app_icon.ico \
    source/core/todo.md \
    README.md
