include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
INCLUDEPATH += C:\Qt\Projects\Lab_4_console

HEADERS += \
        tst_testtemplate.h
        ..\Lab_4_console\template.h

SOURCES += \
        main.cpp
