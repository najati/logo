
CONFIG += c++11
QT += widgets

HEADERS = src/*.h

SOURCES = src/*.cpp

TARGET = helloworld

QMAKE_CXXFLAGS += `pkg-config --cflags ruby-2.2`

QMAKE_LFLAGS += -L`pkg-config --variable=libdir ruby-2.2`
QMAKE_LFLAGS += `pkg-config --libs ruby-2.2`

