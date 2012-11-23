######################################################################
# Automatically generated by qmake (2.01a) vie abr 27 13:08:44 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

QT += opengl

#Descomentar para linux
#LIBS += -lGL
#LIBS += -lGLU

# Input
HEADERS += box.h \
           cameraFirst.h \
           cameraIDI.h \
           color.h \
           face.h \
           glwidget.h \
           ground.h \
           lights.h \
           material.h \
           material_lib.h \
           model.h \
           objectInstance.h \
           point.h \
           principal.h \
           scene.h \
           tinystr.h \
           tinyxml.h \
           vertex.h \
           XML.h
FORMS += principal.ui
SOURCES += box.cpp \
           cameraFirst.cpp \
           cameraIDI.cpp \
           color.cpp \
           face.cpp \
           glwidget.cpp \
           ground.cpp \
           lights.cpp \
           main.cpp \
           material.cpp \
           material_lib.cpp \
           model.cpp \
           objectInstance.cpp \
           point.cpp \
           principal.cpp \
           scene.cpp \
           tinystr.cpp \
           tinyxml.cpp \
           tinyxmlerror.cpp \
           tinyxmlparser.cpp \
           vertex.cpp \
           XML.cpp