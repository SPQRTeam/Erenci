#-------------------------------------------------
#
# Project created by QtCreator 2012-03-01T00:24:28
# Erenci
# LabRoCoCo: labrococo.dis.uniroma1.it
# @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
#
#-------------------------------------------------

QT       += core gui network

TARGET = erenci
TEMPLATE = app

DEPENDPATH += . src
INCLUDEPATH += src

SOURCES += src/main.cpp\
        src/Erenci.cpp \
    src/Connection.cpp \
    src/JointsController.cpp \
    src/MotionMaker.cpp \
    src/Persistance.cpp \
    src/Vision.cpp \
    src/AdvancedControllers.cpp \
    src/DoublePicker.cpp \
    src/Pose.cpp

HEADERS  += src/Erenci.h \
    src/Connection.h \
    src/JointsController.h \
    src/MotionMaker.h \
    src/Persistance.h \
    src/Vision.h \
    src/AdvancedControllers.h \
    src/DoublePicker.h \
    src/Command.h \
    src/Pose.h

FORMS    += src/Erenci.ui \
    src/JointsController.ui \
    src/MotionMaker.ui \
    src/Vision.ui \
    src/AdvancedControllers.ui \
    src/DoublePicker.ui

OTHER_FILES += \
    src/TODO.txt


OBJECTS_DIR = .obj
UI_DIR = .ui
MOC_DIR = .moc






























