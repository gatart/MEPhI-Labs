include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
INCLUDEPATH += C:\Qt\Projects\Lab2_с

HEADERS += \
        tst_test_bigdec.h \
        ../Lab2_c/big_dec.h

SOURCES += \
        main.cpp \
        ../Lab2_c/big_dec.cpp
