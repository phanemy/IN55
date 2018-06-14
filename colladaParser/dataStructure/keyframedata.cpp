#include "keyframedata.h"

KeyFrameData::KeyFrameData(){
	m_time = 0;
}

KeyFrameData::KeyFrameData(float time){
	m_time = time;
}

void KeyFrameData::addBoneTransform(BoneTransformData boneTransform){
	m_boneTransforms.push_back(boneTransform);
}

float KeyFrameData::getTime(){
    return this->m_time;
}

vector<BoneTransformData> KeyFrameData::getBoneTransforms(){
	return this->m_boneTransforms;
}
