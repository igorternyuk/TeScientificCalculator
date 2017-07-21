#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T22:27:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScientificCalculator
TEMPLATE = app

DEFINES -= DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp \
    formequations.cpp \
    formderivative.cpp \
    formintegral.cpp \
    formconverter.cpp \
    doublespinboxdelegate.cpp \
    formsquareequation.cpp \
    matematica.cpp \
    formcubicequation.cpp \
    formtablintegral.cpp \
    formpartialderivatives.cpp \
    formtabldiff.cpp \
    formsystemofnonlinearequations.cpp

HEADERS  += mainwindow.h \
    parser.h \
    formequations.h \
    formderivative.h \
    formintegral.h \
    formconverter.h \
    doublespinboxdelegate.h \
    formsquareequation.h \
    matematica.h \
    formcubicequation.h \
    formtablintegral.h \
    formpartialderivatives.h \
    matrix.h \
    formtabldiff.h \
    formsystemofnonlinearequations.h

FORMS    += mainwindow.ui \
    formequations.ui \
    formderivative.ui \
    formintegral.ui \
    formconverter.ui \
    formsquareequation.ui \
    formcubicequation.ui \
    formtablintegral.ui \
    formpartialderivatives.ui \
    formtabldiff.ui \
    formsystemofnonlinearequations.ui

RC_ICONS = icono.ico

RESOURCES += \
    recursos.qrc

QMAKE_CXXFLAGS += -std=c++14
