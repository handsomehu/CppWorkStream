TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        calc_engine.cpp \
        main.cpp \
        token_stream.cpp

HEADERS += \
    basic_type.h \
    token_stream.h
