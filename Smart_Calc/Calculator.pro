QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    HelpfulFunc.c \
#    SyntaxCheck.c \
    HelpfulFunc.c \
    SyntaxCheck.c \
    main.cpp \
    mainwindow.cpp \
 \#    s21_smartCalc.c
    qcustomplot.cpp \
    s21_smartCalc.c

HEADERS += \
    mainwindow.h \
    qcustomplot.h \
    s21_smartCalc.h

FORMS += \
    mainwindow.ui

ICON = CFE.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CFE.icns
