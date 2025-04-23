TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#=====================OpenCV Includes=======================
<<<<<<< Updated upstream
INCLUDEPATH +=C:\opencv\opencv\build\include

LIBS +=-LC:\opencv\opencv\build\x64\vc16\lib

LIBS += -lopencv_core411 \
=======
INCLUDEPATH += C:\AINT308Lib\OpenCV41\release\install\include
#              C:\opencv\AINT308Lib\OpenCV41\release\install\include

LIBS += -LC:\AINT308Lib\OpenCV41\release\bin
#LIBS += -LC:\AINT308Lib\OpenCV41\release\bin
LIBS +=    -lopencv_core411 \
>>>>>>> Stashed changes
    -lopencv_highgui411 \
    -lopencv_imgproc411 \
    -lopencv_calib3d411 \
    -lopencv_videoio411 \
    -lopencv_video411 \
    -lopencv_imgcodecs411 \
    -lopencv_face411 \
    -lopencv_objdetect411 \
    -lopencv_features2d411 \

LIBS += -lws2_32

SOURCES += \
    checkloaded.cpp \
    main.cpp \
    matching.cpp \
    testing.cpp


DISTFILES += \
   ../images \

HEADERS += \
    checkloaded.hpp \
    matching.hpp \
    testing.hpp
