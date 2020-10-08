include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
INCLUDEPATH += C:\Qt\Projects\Lab1_2

HEADERS += \
        tst_test_lab1_2.h \
    ../Lab1_2/catenary.h

SOURCES += \
        main.cpp \
    ../Lab1_2/catenary.cpp
