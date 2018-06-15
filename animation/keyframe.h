#ifndef KEYFRAME_H
#define KEYFRAME_H
#include <map>
#include <QString>
#include "bonetransform.h"

//map a time and a bone transform

using namespace std;

class KeyFrame
{
public:
	KeyFrame(float timeStamp, BoneTransform pose);
	float getTimeStamp();
	BoneTransform getPose();
private:
	float m_timeStamp;
	BoneTransform m_pose;
};

#endif // KEYFRAME_H
