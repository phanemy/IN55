#ifndef SKELETONLOADER_H
#define SKELETONLOADER_H
#include <QDomNode>
#include <list>
#include <QString>
#include <QMatrix4x4>
#include<skeletondata.h>
#include <QVector3D>
#include <bonedata.h>
#include <QStringList>
#include <myxmlnode.h>
#include <iostream>

using namespace std;

class SkeletonLoader
{
public:
    SkeletonLoader(QDomNode visualSceneNode, QStringList boneOrder);
    SkeletonData extractBoneData();

private:
    QDomNode m_armatureData;
    QStringList m_boneOrder;
    int m_boneCount = 0 ;
    QMatrix4x4 m_CORRECTION;
	BoneData loadBoneData(QDomNode boneNode, bool isRoot);
	BoneData extractMainBoneData(QDomNode boneNode, bool isRoot);
    float* convertData(QStringList rawData);
};

#endif // SKELETONLOADER_H
