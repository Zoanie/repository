TEMPLATE = app

QT += qml quick
CONFIG += c++11

RESOURCES += Qt-hello.qrc

qml.files = Qt-hello.qml

launch_modeall {
	CONFIG(debug, debug|release) {
	    DESTDIR = debug
	} else {
	    DESTDIR = release
	}
}

SOURCES += Qt-hello.cpp
