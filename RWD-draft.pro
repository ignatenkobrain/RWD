QMAKE_CXXFLAGS += -ldl -Wl,-E -std=c++11 -I$$PWD/include
HEADERS += \
    include/RWDFramework/integrate.hpp \
    include/models/osc-model.h \
    include/RWDFramework/config.h \
    include/RWDFramework/odeint_eigen_integration.hpp \
    include/RWDFramework/ModelFactory.hpp \
    include/RWDFramework/ModelWrapper.h \
    include/RWDFramework/Model.h
SOURCES += \
    src/RWDFramework/main.cpp


message($$QMAKE_CXXFLAGS)

LIBS=-ldl
