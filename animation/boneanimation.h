#ifndef BONEANIMATION_H
#define BONEANIMATION_H
#include "keyframe.h"
#include <vector>

//this class contains all keyframe of a bone

using namespace std;

class BoneAnimation
{
public:
	BoneAnimation();
	BoneAnimation(QString name, KeyFrame frames);
	BoneAnimation(QString name, vector<KeyFrame> frames);
	vector<KeyFrame>& getKeyFrame();
	QString getName();
private:
	vector<KeyFrame> m_keyFrames;
	QString m_name;
};

#endif // BONEANIMATION_H
