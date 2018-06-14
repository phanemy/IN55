#include "keyframe.h"



KeyFrame::KeyFrame(float timeStamp, BoneTransform pose):m_pose(pose){
	m_timeStamp = timeStamp;
}

float KeyFrame::getTimeStamp(){
	return m_timeStamp;
}

BoneTransform KeyFrame::getPose(){
	return m_pose;
}
