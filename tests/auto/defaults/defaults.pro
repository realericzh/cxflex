QT += qml quick testlib

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    defaults.cpp

include(../../../cxflex/cxflex.pri)
