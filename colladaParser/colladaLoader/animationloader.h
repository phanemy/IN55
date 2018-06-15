#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#include <QDomNode>
#include <QMatrix4x4>
#include <vector>
#include "animationdata.h"
#include "myxmlnode.h"
#include "bonetransformdata.h"
#include "keyframedata.h"
#include <QString>
#include <iostream>

using namespace std;

class AnimationLoader
{
public:
	 AnimationLoader(QDomNode animationData, QDomNode boneHierarchy);
	~AnimationLoader();
	 AnimationData extractAnimation();

private:
	vector<float> getKeyTimes();
	vector<KeyFrameData> initKeyFrames(vector<float> times);
	void loadBoneTransforms(vector<KeyFrameData>& frames, QDomNode boneData, QString rootNodeId);
	QString getDataId(QDomNode boneData);
	QString getBoneName(QDomNode boneData);
	void processTransforms(QString boneName, QStringList rawData, vector<KeyFrameData>& keyFrames, bool root);
	QString findRootBoneName();
	QMatrix4x4 m_CORRECTION;
	QDomNode m_animationData;
	QDomNode m_boneHierarchy;
};


#endif // ANIMATIONLOADER_H
