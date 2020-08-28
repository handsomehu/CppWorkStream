TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpthread

SOURCES += \
        copysov.cpp \
        funcbody.cpp \
        lzpersons.cpp \
        main.cpp \
        twothread.cpp

HEADERS += \
    funcheader.h \
    lzpersons.h \
    twothread.h
