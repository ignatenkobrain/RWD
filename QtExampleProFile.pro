#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T22:05:12
#
#-------------------------------------------------

#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = QtMathGLProjectSimple
#TEMPLATE = app

#QMAKE_CXXFLAGS += -fopenmp -std=c++11
#-std=c++11 - not work on Windows MinGW

QMAKE_CXXFLAGS += -fopenmp -std=c++0x

win32{
    $$(USERPROFILE)/usr/include
    LIBSPATH=$$(USERPROFILE)/usr/lib
}
unix{
    $$(HOME)/usr/include
    LIBSPATH=$$(HOME)/usr/lib
}
macx{
    $$(HOME)/usr/include
    LIBSPATH=$$(HOME)/usr/lib
}

#for example add libs:
#macx{
# LIBS += -L$$LIBSPATH -lpng16 -ljpeg -lmgl -lmgl-qt5
# PRE_TARGETDEPS += $$LIBSPATH/libpng16.a
#}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32 {
    #message($$(USERPROFILE))
    headers.files=$$HEADERS
    headers.path=$$(USERPROFILE)/usr/include
    target.path = $$(USERPROFILE)/usr/lib
}
unix {
    #message($$(HOME))
    headers.files=$$HEADERS
    headers.path=$$(HOME)/usr/include
    target.path = $$(HOME)/usr/lib
}
INSTALLS += headers
INSTALLS += target


