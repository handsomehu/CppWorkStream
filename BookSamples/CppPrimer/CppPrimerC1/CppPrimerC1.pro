TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sales_data.cpp \
        hasptr.cpp \
        main.cpp \
        screen.cpp \
        strblob.cpp

HEADERS += \
    Sales_data.h \
    Sales_item.h \
    hasptr.h \
    screen.h \
    strblob.h

DISTFILES += \
    memo.txt
