QT      += xml
QT       += core gui widgets opengl

TARGET = template
TEMPLATE = app

SOURCES += main.cpp \
    mesh.cpp \
    colladaParser/dataStructure/skeletondata.cpp \
    colladaParser/dataStructure/meshdata.cpp \
    colladaParser/dataStructure/bonetransformdata.cpp \
    colladaParser/dataStructure/animatedmodeldata.cpp \
    colladaParser/dataStructure/bonedata.cpp \
    colladaParser/dataStructure/keyframedata.cpp \
    colladaParser/dataStructure/skinningdata.cpp \
    colladaParser/dataStructure/vertex.cpp \
    colladaParser/dataStructure/vertexskindata.cpp \
    main.cpp \
    colladaParser/colladaLoader/animationloader.cpp \
    colladaParser/colladaLoader/colladaloader.cpp \
    colladaParser/colladaLoader/geometryloader.cpp \
    colladaParser/colladaLoader/skeletonloader.cpp \
    colladaParser/colladaLoader/skinloader.cpp \
    colladaParser/colladaLoader/myxmlnode.cpp \
    meshdynamic.cpp \
    object3ddynamic.cpp \
    colladaParser/dataStructure/animationdata.cpp \
    animation/animation.cpp \
    animation/boneanimation.cpp \
    animation/keyframe.cpp \
    animation/bonetransform.cpp \
    animation/animator.cpp \
    bone.cpp \
    glwidget.cpp \
    mainwindow.cpp \
    camera.cpp \
    colladaParser/dataParser/animationdataparser.cpp \
    colladaParser/dataParser/modeldataparser.cpp \
    colladaParser/colladaLoader/textureloader.cpp \
    colladaParser/dataStructure/texturedata.cpp

HEADERS += \
    mesh.h \
    colladaParser/dataStructure/skeletondata.h \
    colladaParser/dataStructure/meshdata.h \
    colladaParser/dataStructure/bonetransformdata.h \
    colladaParser/dataStructure/bonedata.h \
    colladaParser/dataStructure/animatedmodeldata.h \
    colladaParser/dataStructure/keyframedata.h \
    colladaParser/dataStructure/skinningdata.h \
    colladaParser/dataStructure/vertex.h \
    colladaParser/dataStructure/vertexskindata.h \
    colladaParser/colladaLoader/animationloader.h \
    colladaParser/colladaLoader/colladaloader.h \
    colladaParser/colladaLoader/geometryloader.h \
    colladaParser/colladaLoader/skeletonloader.h \
    colladaParser/colladaLoader/skinloader.h \
    colladaParser/colladaLoader/myxmlnode.h \
    meshdynamic.h \
    object3ddynamic.h \
    colladaParser/dataStructure/animationdata.h \
    animation/animation.h \
    animation/boneanimation.h \
    animation/keyframe.h \
    animation/bonetransform.h \
    animation/animator.h \
    bone.h \
    glwidget.h \
    mainwindow.h \
    camera.h \
    colladaParser/dataParser/animationdataparser.h \
    colladaParser/dataParser/modeldataparser.h \
    colladaParser/colladaLoader/textureloader.h \
    colladaParser/dataStructure/texturedata.h

RESOURCES += \
    ressources/shaders.qrc \



INCLUDEPATH += colladaParser/dataStructure\
               colladaParser/colladaLoader\
               colladaParser/dataParser\
               animation\

FORMS += \
    mainwindow.ui
