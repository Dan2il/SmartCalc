QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Handler_button.cpp \
    bin/allocate_memory/allocate_memory.c \
    bin/credit_calculator/credit_calculator.c \
    bin/deposit_calculator/deposit_calculator.c \
    bin/expression/calculation.c \
    bin/expression/expression.c \
    bin/expression/read_lexems.c \
    bin/list/list.c \
    bin/processing_errors/processing_errors.c \
    bin/sort_station/sort_station.c \
    finance.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    bin/allocate_memory/allocate_memory.h \
    bin/credit_calculator/credit_calculator.h \
    bin/deposit_calculator/deposit_calculator.h \
    bin/expression/calculation.h \
    bin/expression/expression.h \
    bin/expression/read_lexems.h \
    bin/expression/structures.h \
    bin/list/list.h \
    bin/processing_errors/processing_errors.h \
    bin/sort_station/sort_station.h \
    finance.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    finance.ui \
    graph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
