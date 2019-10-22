TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sales_data.cpp \
        main.cpp \
        screen.cpp

HEADERS += \
    Sales_data.h \
    Sales_item.h \
    screen.h

DISTFILES += \
    memo.txt
