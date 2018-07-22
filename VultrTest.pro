TEMPLATE         = app
TARGET           = VultrTest
QT              += core gui widgets network
CONFIG          -= flat

QMAKE_TARGET_OS  = xp
QMAKE_LFLAGS    += /SUBSYSTEM:CONSOLE,"5.01"
QMAKE_CXXFLAGS  += /D "_USING_V110_SDK71_"

QMAKE_INCDIR    += src src/UI src/HttpDownload

win32 {
    contains(QT_ARCH, i386) {
        MOC_DIR = moc
        CONFIG(debug, debug|release) {
            DESTDIR = bin/debug
            OBJECTS_DIR = debug
        }
        CONFIG(release, debug|release) {
            DESTDIR = bin/release
            OBJECTS_DIR = release
        }
    } else {
        TARGET = VultrTest64
        MOC_DIR = moc_x64
        CONFIG(debug, debug|release) {
            DESTDIR = bin/debug_x64
            OBJECTS_DIR = debug_x64
        }
        CONFIG(release, debug|release) {
            DESTDIR = bin/release
            OBJECTS_DIR = release_64
        }
    }
}

PRECOMPILED_HEADER = src/PrecompiledHeader.h

HEADERS += src/PrecompiledHeader.h\
           src/Download/HttpDownloader.h\
           src/Download/HeadTester.h\
           src/UI/DownloadTestWidget.h\
           src/UI/HeadTestWidget.h\
           src/UI/MainWindow.h

SOURCES += src/main.cpp\
           src/Download/HttpDownloader.cpp\
           src/Download/HeadTester.cpp\
           src/UI/DownloadTestWidget.cpp\
           src/UI/HeadTestWidget.cpp\
           src/UI/MainWindow.cpp