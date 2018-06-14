#include "animationdata.h"

AnimationData::AnimationData(const float lengthSeconds, vector<KeyFrameData> keyFrames): m_keyFrameData(keyFrames){
	this->m_lengthSeconds = lengthSeconds;
}

float AnimationData::getLengthSeconds(){
	return m_lengthSeconds;
}

vector<KeyFrameData> AnimationData::getKeyFrameData(){
	return m_keyFrameData;
}
