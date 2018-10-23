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
    source/application/about.h \
    source/shared/settings.h \
    source/application/log.h \
    source/core/object/object.h \
    source/core/parser.h \
    source/core/object/field.h \
    source/core/extattr/extattr.h \
    source/core/object/interface.h \
    source/core/object/enumeration.h \
    source/core/object/collection/interfacelist.h \
    source/core/object/listitem.h \
    source/core/object/dictonary.h \
    source/core/object/collection/dictonarylist.h \
    source/core/object/collection/collection.h \
    source/core/output/oheader.h \
    source/core/output/osource.h \
    source/core/extattr/constructor.h \
    source/core/object/attribute.h \
    source/core/object/typedefine.h \
    source/core/extattr/namedconstructor.h \
    source/core/extattr/extattrlist.h \
    source/core/idefinition.h

SOURCES += \
    source/application/window.cpp \
    source/application/output.cpp \
    source/application/options.cpp \
    source/application/finish.cpp \
    source/application/about.cpp \
    source/main.cpp \
    source/shared/settings.cpp \
    source/application/log.cpp \
    source/core/object/object.cpp \
    source/core/parser.cpp \
    source/core/object/field.cpp \
    source/core/extattr/extattr.cpp \
    source/core/object/interface.cpp \
    source/core/object/enumeration.cpp \
    source/core/object/collection/interfacelist.cpp \
    source/core/object/listitem.cpp \
    source/core/object/dictonary.cpp \
    source/core/object/collection/dictonarylist.cpp \
    source/core/object/collection/collection.cpp \
    source/core/output/oheader.cpp \
    source/core/output/osource.cpp \
    source/core/extattr/constructor.cpp \
    source/core/object/attribute.cpp \
    source/core/object/typedefine.cpp \
    source/core/extattr/namedconstructor.cpp \
    source/core/extattr/extattrlist.cpp \
    source/core/idefinition.cpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/icon.png \
    resources/app_icon.ico \
    source/core/todo.md \
    README.md
