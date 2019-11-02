#-------------------------------------------------
#
# Project created by QtCreator 2019-08-05T15:38:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InputMethod
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


SOURCES += \
        main.cpp \
        dialog.cpp \
    softkeyboard.cpp \
    googlepinyinmanager.cpp

HEADERS += \
        dialog.h \
    softkeyboard.h \
    googlepinyinmanager.h \
    include/head/dictdef.h \
    include/head/pinyinime.h \
    include/head/utf16char.h





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/lib/ -lGoogleChineseSpell
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/lib/ -lGoogleChineseSpelld
else:unix: LIBS += -L$$PWD/include/lib/ -lGoogleChineseSpell

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/include/lib/libGoogleChineseSpell.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/include/lib/libGoogleChineseSpelld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/include/lib/GoogleChineseSpell.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/include/lib/GoogleChineseSpelld.lib
else:unix: PRE_TARGETDEPS += $$PWD/include/lib/libGoogleChineseSpell.a
