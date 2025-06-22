#-------------------------------------------------
#
# Project created by QtCreator 2016-02-06T12:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = irctc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    database.cpp \
    signup.cpp \
    login.cpp \
    available.cpp \
    confirm.cpp \
    debit.cpp \
    details.cpp \
    payment.cpp \
    indirect.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    database.h \
    signup.h \
    userpass.h \
    login.h \
    available.h \
    confirm.h \
    debit.h \
    details.h \
    payment.h \
    indirect.h

FORMS    += mainwindow.ui \
    dialog.ui \
    signup.ui \
    login.ui \
    available.ui \
    confirm.ui \
    debit.ui \
    details.ui \
    payment.ui \
    indirect.ui

RESOURCES +=

OTHER_FILES += \
    file1.txt

DISTFILES += \
    user.txt \
    mon.txt \
    temp.txt \
    select.txt \
    p-detail.txt \
    tue.txt \
    wed.txt \
    thu.txt \
    fri.txt \
    sat.txt \
    sun.txt \
    code.txt \
    extra.txt
