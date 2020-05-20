QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

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
    init.cpp \
    main.cpp \
    mainwindow.cpp \
    vdatabasemanager.cpp \
    vgroup.cpp \
    vgroupmodel.cpp \
    vmeasurement.cpp \
    vmeasurementmodel.cpp \
    vpattern.cpp \
    vpatternmodel.cpp \
    vproperties.cpp \
    vpropertiesmodel.cpp

HEADERS += \
    init.h \
    mainwindow.h \
    vdatabasemanager.h \
    vgroup.h \
    vgroupmodel.h \
    vmeasurement.h \
    vmeasurementmodel.h \
    vpattern.h \
    vpatternmodel.h \
    vproperties.h \
    vpropertiesmodel.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    diagrams/Ap1.svg \
    diagrams/Ap2.svg \
    diagrams/Bp1.svg \
    diagrams/Bp2.svg \
    diagrams/Cp1.svg \
    diagrams/Cp2.svg \
    diagrams/Dp1.svg \
    diagrams/Dp2.svg \
    diagrams/Dp3.svg \
    diagrams/Ep1.svg \
    diagrams/Ep2.svg \
    diagrams/Fp1.svg \
    diagrams/Fp2.svg \
    diagrams/Fp3.svg \
    diagrams/Gp1.svg \
    diagrams/Gp2.svg \
    diagrams/Gp3.svg \
    diagrams/Gp4.svg \
    diagrams/Gp5.svg \
    diagrams/Gp6.svg \
    diagrams/Gp7.svg \
    diagrams/Gp8.svg \
    diagrams/Gp9.svg \
    diagrams/Hp1.svg \
    diagrams/Hp10.svg \
    diagrams/Hp11.svg \
    diagrams/Hp12.svg \
    diagrams/Hp13.svg \
    diagrams/Hp2.svg \
    diagrams/Hp3.svg \
    diagrams/Hp4.svg \
    diagrams/Hp5.svg \
    diagrams/Hp6.svg \
    diagrams/Hp7.svg \
    diagrams/Hp8.svg \
    diagrams/Hp9.svg \
    diagrams/Ip1.svg \
    diagrams/Ip2.svg \
    diagrams/Ip3.svg \
    diagrams/Ip4.svg \
    diagrams/Ip5.svg \
    diagrams/Ip6.svg \
    diagrams/Ip7.svg \
    diagrams/Jp1.svg \
    diagrams/Jp2.svg \
    diagrams/Jp3.svg \
    diagrams/Jp4.svg \
    diagrams/Jp5.svg \
    diagrams/Jp6.svg \
    diagrams/Kp1.svg \
    diagrams/Kp10.svg \
    diagrams/Kp11.svg \
    diagrams/Kp2.svg \
    diagrams/Kp3.svg \
    diagrams/Kp4.svg \
    diagrams/Kp5.svg \
    diagrams/Kp6.svg \
    diagrams/Kp7.svg \
    diagrams/Kp8.svg \
    diagrams/Kp9.svg \
    diagrams/Lp1.svg \
    diagrams/Lp10.svg \
    diagrams/Lp2.svg \
    diagrams/Lp3.svg \
    diagrams/Lp4.svg \
    diagrams/Lp5.svg \
    diagrams/Lp6.svg \
    diagrams/Lp7.svg \
    diagrams/Lp8.svg \
    diagrams/Lp9.svg \
    diagrams/Mp1.svg \
    diagrams/Mp2.svg \
    diagrams/Mp3.svg \
    diagrams/Np1.svg \
    diagrams/Np2.svg \
    diagrams/Np3.svg \
    diagrams/Np4.svg \
    diagrams/Np5.svg \
    diagrams/Op1.svg \
    diagrams/Op10.svg \
    diagrams/Op11.svg \
    diagrams/Op2.svg \
    diagrams/Op3.svg \
    diagrams/Op4.svg \
    diagrams/Op5.svg \
    diagrams/Op6.svg \
    diagrams/Op7.svg \
    diagrams/Op8.svg \
    diagrams/Op9.svg \
    diagrams/Pp1.svg \
    diagrams/Pp10.svg \
    diagrams/Pp11.svg \
    diagrams/Pp12.svg \
    diagrams/Pp2.svg \
    diagrams/Pp3.svg \
    diagrams/Pp4.svg \
    diagrams/Pp5.svg \
    diagrams/Pp6.svg \
    diagrams/Pp7.svg \
    diagrams/Pp8.svg \
    diagrams/Pp9.svg \
    diagrams/Qp1.svg \
    diagrams/Qp2.svg \
    diagrams/Qp3.svg

RESOURCES += \
    resource.qrc
