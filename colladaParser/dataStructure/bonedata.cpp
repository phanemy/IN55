#include "bonedata.h"

BoneData::BoneData(int index, QString nameId, QMatrix4x4 bindLocalTransform): m_index(index), m_nameId(nameId), m_bindLocalTransform(bindLocalTransform){
	cout << "BoneData matrix "<< bindLocalTransform.column(0).x() <<" " <<bindLocalTransform.column(1).x() <<" "<<bindLocalTransform.column(2).x() <<" "<<bindLocalTransform.column(3).x() <<endl;
	cout << "BoneData matrix "<< bindLocalTransform.column(0).y() <<" " <<bindLocalTransform.column(1).y() <<" "<<bindLocalTransform.column(2).y() <<" "<<bindLocalTransform.column(3).y() <<endl;
	cout << "BoneData matrix "<< bindLocalTransform.column(0).z() <<" " <<bindLocalTransform.column(1).z() <<" "<<bindLocalTransform.column(2).z() <<" "<<bindLocalTransform.column(3).z() <<endl;
	cout << "BoneData matrix "<< bindLocalTransform.column(0).w() <<" " <<bindLocalTransform.column(1).w() <<" "<<bindLocalTransform.column(2).w() <<" "<<bindLocalTransform.column(3).w() <<"\n"<<endl;
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
