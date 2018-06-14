#ifndef ANIMATIONDATA_H
#define ANIMATIONDATA_H

#include "keyframedata.h"
#include <vector>

class AnimationData
{
public:
	AnimationData(float lengthSeconds, vector<KeyFrameData> keyFrames);
	float getLengthSeconds();
	vector<KeyFrameData> getKeyFrameData();
private:
	float m_lengthSeconds;
	vector<KeyFrameData> m_keyFrameData;
};

#endif // ANIMATIONDATA_H
