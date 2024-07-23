QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app/colorlabel.cpp \
    app/customlistdelegate.cpp \
    app/editableitemdelegate.cpp \
    # app/gdsdialog.cpp \
    app/graphicsview.cpp \
    app/gridwidget.cpp \
    app/listitemwidget.cpp \
    app/main.cpp \
    app/mainwindow.cpp \
    app/pdk_manage_dialog.cpp \
    app/pdkitemmodel.cpp \
    app/pdklistmodel.cpp \
    app/rightdockwidget.cpp \
    app/styledialog.cpp \
    app/styleframe.cpp

HEADERS += \
    app/colorlabel.h \
    app/customlistdelegate.h \
    app/editableitemdelegate.h \
    # app/gdsdialog.h \
    app/graphicsview.h \
    app/gridwidget.h \
    app/listitemwidget.h \
    app/mainwindow.h \
    app/pdk_info.h \
    app/pdk_manage_dialog.h \
    app/pdkitemmodel.h \
    app/pdklistmodel.h \
    app/rightdockwidget.h \
    app/styledialog.h \
    app/styleframe.h

FORMS += \
    # app/gdsdialog.ui \
    app/mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
