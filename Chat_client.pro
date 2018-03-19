QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = Chat_client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    chatclient.cpp

HEADERS += \
    chatclient.h
