#include "bonetransformdata.h"

BoneTransformData::BoneTransformData(QString boneNameId, QMatrix4x4 boneLocalTransform){
    this->m_boneNameId = boneNameId;
    this->m_boneLocalTransform = boneLocalTransform;
}

QString BoneTransformData::getBoneNameId(){
    return this->m_boneNameId;
}

QMatrix4x4 BoneTransformData::getBoneLocalTransform(){
    return this->m_boneLocalTransform;
}
