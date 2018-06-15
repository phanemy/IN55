#include "bonedata.h"

BoneData::BoneData(int index, QString nameId, QMatrix4x4 bindLocalTransform): m_index(index), m_nameId(nameId), m_bindLocalTransform(bindLocalTransform){
}

void BoneData::addChild(BoneData child){
    this->m_children.push_back(child);
}

int BoneData::getIndex(){
    return this->m_index;
}

QString BoneData::getNameId(){
    return this->m_nameId;
}

QMatrix4x4 BoneData::getBindLocalTransform(){
    return this->m_bindLocalTransform;
}

list<BoneData> BoneData::getChildren(){
    return this->m_children;
}
