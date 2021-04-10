QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/local/opencv4.5.0/include/opencv4 \
               /usr/local/opencv4.5.0/include/opencv4/opencv2
#这里INCLUDEPATH的路径是本人的安装位置，自己在写入的时候一定要查看清楚
LIBS += /usr/local/opencv4.5.0/lib/libopencv_highgui.so \
       /usr/local/opencv4.5.0/lib/libopencv_core.so    \
       /usr/local/opencv4.5.0/lib/libopencv_imgproc.so  \
       /usr/local/opencv4.5.0/lib/libopencv_imgcodecs.so

#INCLUDEPATH +=   /usr/local/arm/opencv3.4.4/include \
#                /usr/local/arm/opencv3.4.4/include/opencv \
#               /usr/local/arm/opencv3.4.4/include/opencv2
##这里INCLUDEPATH的路径是本人的安装位置，自己在写入的时候一定要查看清楚
#LIBS += /usr/local/arm/opencv3.4.4/lib/libopencv_highgui.so \
#       /usr/local/arm/opencv3.4.4/lib/libopencv_core.so    \
#       /usr/local/arm/opencv3.4.4/lib/libopencv_imgproc.so  \
#       /usr/local/arm/opencv3.4.4/lib/libopencv_imgcodecs.so







