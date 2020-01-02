QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tradewrapper.cpp

HEADERS += \
    libhead/ThostFtdcMdApi.h \
    libhead/ThostFtdcTraderApi.h \
    libhead/ThostFtdcUserApiDataType.h \
    libhead/ThostFtdcUserApiStruct.h \
    libhead/json.hpp \
    mainwindow.h \
    tradewrapper.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cfg/CTP_connect.json \
    cfg/j123.json \
    libhead/error.dtd \
    libhead/error.xml

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libfiles/release/ -lthosttraderapi_se
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libfiles/debug/ -lthosttraderapi_se
else:unix: LIBS += -L$$PWD/libfiles/ -lthosttraderapi_se

INCLUDEPATH += $$PWD/libfiles
DEPENDPATH += $$PWD/libfiles
