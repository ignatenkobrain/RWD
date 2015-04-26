QMAKE_CXXFLAGS += -ldl -Wl,-E -std=c++11 -I$$PWD/include
QT += xml
HEADERS += \
    include/RWDFramework/integrate.hpp \
    include/models/osc-model.h \
    include/RWDFramework/odeint_eigen_integration.hpp \
    include/RWDFramework/ModelFactory.hpp \
    include/RWDFramework/ModelWrapper.h \
    include/RWDFramework/Model.h \
    include/RWDFramework/ModelConfiguration.h \
    include/RWDFramework/observers/StoreInMemoryObserver.h
SOURCES += \
    src/RWDFramework/main.cpp \
    src/RWDFramework/ModelConfiguration.cpp


message($$QMAKE_CXXFLAGS)

LIBS=-ldl
