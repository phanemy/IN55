#include "boneanimation.h"
BoneAnimation::BoneAnimation(){}

BoneAnimation::BoneAnimation(QString name, KeyFrame frames):m_name(name)
{
	m_keyFrames.push_back(frames);
}

BoneAnimation::BoneAnimation(QString name, vector<KeyFrame> frames):m_keyFrames(frames),m_name(name)
{

}

vector<KeyFrame>& BoneAnimation::getKeyFrame(){
	return m_keyFrames;
};

QString BoneAnimation::getName(){
	return m_name;
}
