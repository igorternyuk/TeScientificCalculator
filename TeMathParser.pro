TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    matematica.cpp \
    parser.cpp \
    matrix_error.cpp

HEADERS += \
    matematica.h \
    matrix.h \
    parser.h \
    matrix_error.h \
    polynom.h

QMAKE_CXXFLAGS += -std=c++14
