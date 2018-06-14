#ifndef SKELETONDATA_H
#define SKELETONDATA_H
#include "bonedata.h"

class SkeletonData
{
public:
    SkeletonData(int boneCount, BoneData headBone);
    int getBoneCount();
	BoneData& getHeadBone();

private:
    int m_boneCount;
    BoneData m_headBone;
};

#endif // SKELETONDATA_H
