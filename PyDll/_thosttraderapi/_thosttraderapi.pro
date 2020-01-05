CONFIG -= qt

TEMPLATE = lib
DEFINES += _THOSTTRADERAPI_LIBRARY

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
    _thosttraderapi.cpp \
    thosttraderapi_wrap.cxx

HEADERS += \
    ThostFtdcTraderApi.h \
    ThostFtdcUserApiDataType.h \
    ThostFtdcUserApiStruct.h \
    _thosttraderapi_global.h \
    _thosttraderapi.h \
    thosttraderapi_wrap.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lthosttraderapi_se
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lthosttraderapi_se
else:unix: LIBS += -L$$PWD/./ -lthosttraderapi_se

INCLUDEPATH += $$PWD/.
INCLUDEPATH += /home/leon/anaconda2/include/
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../anaconda2/lib/release/ -lpython2.7
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../anaconda2/lib/debug/ -lpython2.7
else:unix: LIBS += -L$$PWD/../../../../anaconda2/lib/ -lpython2.7

INCLUDEPATH += $$PWD/../../../../anaconda2/lib
DEPENDPATH += $$PWD/../../../../anaconda2/lib
INCLUDEPATH += $$PWD/../../../../anaconda2/include/python2.7
DEPENDPATH += $$PWD/../../../../anaconda2/include/python2.7
