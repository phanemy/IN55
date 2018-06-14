#include "skeletondata.h"

SkeletonData::SkeletonData(int boneCount, BoneData headBone) : m_boneCount(boneCount), m_headBone(headBone){
}

int SkeletonData::getBoneCount(){
    return this->m_boneCount;
}

BoneData& SkeletonData::getHeadBone(){
    return this->m_headBone;
}
