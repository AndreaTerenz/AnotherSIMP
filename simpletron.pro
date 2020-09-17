TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        runner/instructions.cpp \
        runner/memory.cpp \
        runner/runner.cpp

HEADERS += \
    runner/instructions.h \
    runner/memory.h \
    runner/runner.h
