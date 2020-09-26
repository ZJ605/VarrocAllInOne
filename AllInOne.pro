#-------------------------------------------------
#
# Project created by QtCreator 2019-07-25T09:22:47
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION,4): QT += widgets printsupport

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Program
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        basicobject.cpp \
        detector.cpp \
        geometrydialog.cpp \
        geometrymodel.cpp \
        geometryscene.cpp \
        geometryviewer.cpp \
        layer.cpp \
        main.cpp \
        mainwindow.cpp \
        matrix.cpp \
        neuralnetwork.cpp \
        neuron.cpp \
        nurbs.cpp \
        plyreader.cpp \
        point.cpp \
        qcustomplot.cpp \
        ray.cpp \
        smaz.cpp \
        source.cpp \
        tracer.cpp \
        vao_vbo_object.cpp

HEADERS += \
        basicobject.h \
        detector.h \
        geometrydialog.h \
        geometrymodel.h \
        geometryscene.h \
        geometryviewer.h \
        layer.h \
        mainwindow.h \
        matrix.h \
        neuralnetwork.h \
        neuron.h \
        nurbs.h \
        plyreader.h \
        point.h \
        qcustomplot.h \
        ray.h \
        smaz.h \
        source.h \
        tracer.h \
        vao_vbo_object.h
        UI_CreateGeometryDialog.h

FORMS += \
    detector.ui \
    geometrydialog.ui \
    source.ui \
    tracer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    sim.frag \
    sim.vert \
    sourceShader.frag \
    sourceShader.vert



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../library/build-Nurbs2D-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/release/ -lNurbs2D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../library/build-Nurbs2D-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/debug/ -lNurbs2D

INCLUDEPATH += $$PWD/../library/build-Nurbs2D-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/debug
DEPENDPATH += $$PWD/../library/build-Nurbs2D-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/debug

INCLUDEPATH += $$PWD/../../../Program/C_Cxx/library/Nurbs2D

INCLUDEPATH += C:\Users\Ray\Programy\opencv\release\install\include

win32: LIBS += -L$$PWD/../../../Programy/opencv/release/install/x64/mingw/lib/ -llibopencv_calib3d420.dll
win32: LIBS += -L$$PWD/../../../Programy/opencv/release/install/x64/mingw/lib/ -llibopencv_core420.dll
win32: LIBS += -L$$PWD/../../../Programy/opencv/release/install/x64/mingw/lib/ -llibopencv_highgui420.dll
win32: LIBS += -L$$PWD/../../../Programy/opencv/release/install/x64/mingw/lib/ -llibopencv_imgcodecs420.dll
win32: LIBS += -L$$PWD/../../../Programy/opencv/release/install/x64/mingw/lib/ -llibopencv_imgproc420.dll

INCLUDEPATH += $$PWD/../../../Programy/opencv/release/install/x64/mingw
DEPENDPATH += $$PWD/../../../Programy/opencv/release/install/x64/mingw
