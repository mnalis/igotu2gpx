CLEBS *= buildplugin visualizer igotu
TARGET = listvisualizer
include(../../../clebs.pri)

QT *= gui widgets

SOURCES *= $$files(*.cpp)
