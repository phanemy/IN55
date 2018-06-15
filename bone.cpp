#include "bone.h"

Bone::Bone(){
}

Bone::Bone(int index, QString name, QMatrix4x4 bindLocalTransform): m_name(name),m_localBindTransform(bindLocalTransform){
	m_index = index;
}

Bone::~Bone(){
	for(Bone* child: m_children)
		delete child;
}

void Bone::addChild(Bone* child){
	m_children.push_back(child);
}

QMatrix4x4 Bone::getAnimatedTransform(){
	return m_animatedTransform;
}

void Bone::setAnimationTransform(QMatrix4x4 animationTransform){
	m_animatedTransform = animationTransform;
}

QMatrix4x4 Bone::getInverseBindTransform(){
	return m_inverseBindTransform;
}

void Bone::calcInverseBindTransform(QMatrix4x4 parentBindTransform){

//	parentBindTransform = parentBindTransform.transposed();
	QMatrix4x4 bindTransform = parentBindTransform * m_localBindTransform;
	m_inverseBindTransform = bindTransform.inverted();
	for(Bone* child : m_children)
	{
		child->calcInverseBindTransform(bindTransform);
	}
}

QString Bone::getName(){
	return m_name;
}

vector<Bone*>& Bone::getChildren(){
	return m_children;
}

int Bone::getId(){
	return this->m_index;
}

