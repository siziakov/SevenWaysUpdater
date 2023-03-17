QT       += core gui network gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lz

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    downloader.cpp \
    httpfilesize.cpp \
    main.cpp \
    mainwindow.cpp \
    mapdescriptor.cpp \
    maps.cpp \
    mapsgroup.cpp \
    zip.c

HEADERS += \
    downloader.h \
    downloader.h \
    httpfilesize.h \
    httpfilesize.h \
    mainwindow.h \
    mapdescriptor.h \
    maps.h \
    maps.h \
    mapsgroup.h \
    mapsgroup.h \
    miniz.h \
    zip.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icon/7ways.ico
