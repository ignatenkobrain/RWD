QMAKE_CXXFLAGS += -std=c++11 -I$$PWD/include
HEADERS += \
    include/RWDFramework/integrate.hpp \
    include/models/osc-model.h \
    include/RWDFramework/integrable.h \
    include/RWDFramework/config.h \
    include/RWDFramework/odeint_eigen_integration.hpp
SOURCES += \
    src/RWDFramework/main.cpp


message($$QMAKE_CXXFLAGS)
