#ifndef KEYFRAMEDATA_H
#define KEYFRAMEDATA_H
#include <vector>
#include "bonetransformdata.h"

using namespace std;

class KeyFrameData
{
public:
	KeyFrameData();
    KeyFrameData(float time);
    void addBoneTransform(BoneTransformData boneTransform);
    float getTime();
    vector<BoneTransformData> getBoneTransforms();

private:
	float m_time;
	vector<BoneTransformData> m_boneTransforms;
};


#endif // KEYFRAMEDATA_H
