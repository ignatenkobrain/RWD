CONFIG += plugin
CONFIG -= qt
TEMPLATE = lib

HEADERS += \
    include/models/osc-model.h \
    include/models/create_model.h

SOURCES += \
    src/models/main.cpp \
    src/models/create_model.cpp
