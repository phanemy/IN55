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
	 AnimationLoader(QDomNode animationData, QDomNode jointHierarchy);
	~AnimationLoader();
	 AnimationData extractAnimation();

private:
	vector<float> getKeyTimes();
	vector<KeyFrameData> initKeyFrames(vector<float> times);
	void loadJointTransforms(vector<KeyFrameData>& frames, QDomNode jointData, QString rootNodeId);
	QString getDataId(QDomNode jointData);
	QString getJointName(QDomNode jointData);
	void processTransforms(QString jointName, QStringList rawData, vector<KeyFrameData>& keyFrames, bool root);
	QString findRootJointName();
	QMatrix4x4 m_CORRECTION;
	QDomNode m_animationData;
	QDomNode m_jointHierarchy;
};


#endif // ANIMATIONLOADER_H
