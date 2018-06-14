#ifndef COLLADALOADER_H
#define COLLADALOADER_H
#include "animatedmodeldata.h"
#include "animationdata.h"
#include <QFile>
#include <QMessageBox>
#include <QtXml>
#include "skinloader.h"
#include "skeletonloader.h"
#include "skeletondata.h"
#include <iostream>
#include "geometryloader.h"
#include "meshdata.h"
#include "animationloader.h"
#include "textureloader.h"
#include "texturedata.h"

using namespace std;

class ColladaLoader
{
public:
	static AnimatedModelData loadColladaModel(QFile* colladaFile, int maxWeights);
	static AnimationData loadColladaAnimation(QFile* colladaFile);
};

#endif // COLLADALOADER_H
