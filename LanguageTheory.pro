#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T21:58:17
#
#-------------------------------------------------

QT       += core gui

TARGET = LanguageTheory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ESP.cpp \
    rule.cpp \
    language.cpp \
    ruleexception.cpp \
    addrule.cpp

HEADERS  += mainwindow.h \
    ESP.h \
    rule.h \
    language.h \
    Bridge.h \
    ruleexception.h \
    Constants.h \
    addrule.h

FORMS    += mainwindow.ui \
    addrule.ui

RESOURCES += \
    Resource.qrc
