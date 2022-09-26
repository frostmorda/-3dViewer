QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    model/model.cpp \
    model/mvpmatrix.cpp \
    gif_src/3rdParty/giflib/dgif_lib.c \
    gif_src/3rdParty/giflib/egif_lib.c \
    gif_src/3rdParty/giflib/gif_err.c \
    gif_src/3rdParty/giflib/gif_font.c \
    gif_src/3rdParty/giflib/gif_hash.c \
    gif_src/3rdParty/giflib/gifalloc.c \
    gif_src/3rdParty/giflib/quantize.c \
    gif_src/gifimage/doc/snippets/doc_src_qtgifimage.cpp \
    gif_src/gifimage/qgifimage.cpp \
    main.cpp \
    view/mainwindow.cpp \
    view/myopenglwidget.cpp \
    view/settings.cpp

HEADERS += \
    controller/controller.h \
    model/m_caretaker.h \
    model/m_memento.h \
    model/matrix.h \
    model/model.h \
    model/mvpmatrix.h \
    model/polygon.h \
    gif_src/3rdParty/giflib/gif_hash.h \
    gif_src/3rdParty/giflib/gif_lib.h \
    gif_src/3rdParty/giflib/gif_lib_private.h \
    gif_src/gifimage/qgifglobal.h \
    gif_src/gifimage/qgifimage.h \
    gif_src/gifimage/qgifimage_p.h \
    view/mainwindow.h \
    misc.h \
    view/myopenglwidget.h \
    view/settings.h

FORMS += \
    view/mainwindow.ui

RESOURCES += \
    OpenGL.qrc\

macx:ICON = view/3DViewer.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    3DViewer.pro.user \
    Makefile \
    model/a.out \
    cube.obj \
    settings.txt \
    gif_src/3rdParty/giflib.pri \
    gif_src/3rdParty/giflib/AUTHORS \
    gif_src/3rdParty/giflib/COPYING \
    gif_src/3rdParty/giflib/README \
    gif_src/gifimage/doc/qtgifimage.qdocconf \
    gif_src/gifimage/doc/src/examples.qdoc \
    gif_src/gifimage/doc/src/index.qdoc \
    gif_src/gifimage/doc/src/qtgifimage.qdoc \
    gif_src/gifimage/doc/src/usage.qdoc \
    gif_src/gifimage/qtgifimage.pri \
    shaders/frag_shader.frag \
    shaders/vert_shader.vert

SUBDIRS += \
    gif_src/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    gif_src/gifimage/gifimage.pro \
    gif_src/src.pro
