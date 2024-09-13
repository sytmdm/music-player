QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientsocket.cpp \
    customlabel.cpp \
    main.cpp \
    mainwindow.cpp \
    musicitem.cpp \
    musiclirc.cpp \
    musiclist.cpp \
    musicmenu.cpp \
    onlineplayer.cpp \
    selectmenu.cpp

HEADERS += \
    clientsocket.h \
    customlabel.h \
    mainwindow.h \
    musicitem.h \
    musiclirc.h \
    musiclist.h \
    musicmenu.h \
    onlineplayer.h \
    selectmenu.h

FORMS += \
    mainwindow.ui \
    musicitem.ui \
    musiclirc.ui \
    musiclist.ui \
    musicmenu.ui \
    selectmenu.ui

TRANSLATIONS += \
    musicPlayer_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    musicimg/歌词.png
