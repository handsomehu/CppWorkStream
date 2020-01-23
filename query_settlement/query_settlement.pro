TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        tradewrapper.cpp

DISTFILES += \
    libhead/error.dtd \
    libhead/error.xml

HEADERS += \
    libhead/ThostFtdcMdApi.h \
    libhead/ThostFtdcTraderApi.h \
    libhead/ThostFtdcUserApiDataType.h \
    libhead/ThostFtdcUserApiStruct.h \
    libhead/json.hpp \
    tradewrapper.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libfiles/release/ -lthosttraderapi_se
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libfiles/debug/ -lthosttraderapi_se
else:unix: LIBS += -L$$PWD/libfiles/ -lthosttraderapi_se

INCLUDEPATH += $$PWD/libfiles
DEPENDPATH += $$PWD/libfiles
