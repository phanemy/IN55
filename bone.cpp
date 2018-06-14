#include "bone.h"

Bone::Bone(){
}

Bone::Bone(int index, QString name, QMatrix4x4 bindLocalTransform): m_name(name),m_localBindTransform(bindLocalTransform){
	m_index = index;
	QMatrix4x4 temp = bindLocalTransform;
	cout << "\t\t\t"<<name.toStdString()<<" Bone create"<<endl;
	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).x() << " " <<temp.column(1).x() << " " <<temp.column(2).x()<< " " <<temp.column(3).x() <<endl;
	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).y() << " " <<temp.column(1).y() << " " <<temp.column(2).y()<< " " <<temp.column(3).y() <<endl;
	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).z() << " " <<temp.column(1).z() << " " <<temp.column(2).z()<< " " <<temp.column(3).z() <<endl;
	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).w() << " " <<temp.column(1).w() << " " <<temp.column(2).w()<< " " <<temp.column(3).w() <<endl;
//	temp = bindLocalTransform.transposed();
//	cout << "\t\t\tBone create"<<endl;
//	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).x() << " " <<temp.column(1).x() << " " <<temp.column(2).x()<< " " <<temp.column(3).x() <<endl;
//	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).y() << " " <<temp.column(1).y() << " " <<temp.column(2).y()<< " " <<temp.column(3).y() <<endl;
//	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).z() << " " <<temp.column(1).z() << " " <<temp.column(2).z()<< " " <<temp.column(3).z() <<endl;
//	cout << "Bone m_localBindTransform matrix "<<this->m_index<<" : "<< temp.column(0).w() << " " <<temp.column(1).w() << " " <<temp.column(2).w()<< " " <<temp.column(3).w() <<endl;
}

Bone::~Bone(){
	for(Bone* child: m_children)
		delete child;
}

void Bone::addChild(Bone* child){
	m_children.push_back(child);
}

QMatrix4x4 Bone::getAnimatedTransform(){
//	cout << "Animator getAnimatedTransform matrix "<<this->m_index<<" : "<< m_animatedTransform.column(0).x() << " " <<m_animatedTransform.column(1).x() << " " <<m_animatedTransform.column(2).x()<< " " <<m_animatedTransform.column(3).x() <<endl;
//	cout << "Animator getAnimatedTransform matrix "<<this->m_index<<" : "<< m_animatedTransform.column(0).y() << " " <<m_animatedTransform.column(1).y() << " " <<m_animatedTransform.column(2).y()<< " " <<m_animatedTransform.column(3).x() <<endl;
//	cout << "Animator getAnimatedTransform matrix "<<this->m_index<<" : "<< m_animatedTransform.column(0).z() << " " <<m_animatedTransform.column(1).z() << " " <<m_animatedTransform.column(2).z()<< " " <<m_animatedTransform.column(3).x() <<endl;
//	cout << "Animator getAnimatedTransform matrix "<<this->m_index<<" : "<< m_animatedTransform.column(0).w() << " " <<m_animatedTransform.column(1).w() << " " <<m_animatedTransform.column(2).w()<< " " <<m_animatedTransform.column(3).x() <<endl;
//	cout << " "<<endl;
	return m_animatedTransform;
}

void Bone::setAnimationTransform(QMatrix4x4 animationTransform){
//		cout << "Animator applyPoseToJoints matrix "<<this->m_index<<" : "<< animationTransform.column(0).x() << " " <<animationTransform.column(1).x() << " " <<animationTransform.column(2).x()<< " " <<animationTransform.column(3).x() <<endl;
//		cout << "Animator applyPoseToJoints matrix "<<this->m_index<<" : "<< animationTransform.column(0).y() << " " <<animationTransform.column(1).y() << " " <<animationTransform.column(2).y()<< " " <<animationTransform.column(3).x() <<endl;
//		cout << "Animator applyPoseToJoints matrix "<<this->m_index<<" : "<< animationTransform.column(0).z() << " " <<animationTransform.column(1).z() << " " <<animationTransform.column(2).z()<< " " <<animationTransform.column(3).x() <<endl;
//		cout << "Animator applyPoseToJoints matrix "<<this->m_index<<" : "<< animationTransform.column(0).w() << " " <<animationTransform.column(1).w() << " " <<animationTransform.column(2).w()<< " " <<animationTransform.column(3).x() <<endl;
//		cout << " "<<endl;
	m_animatedTransform = animationTransform;
}

QMatrix4x4 Bone::getInverseBindTransform(){
//		cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).x() << " " <<m_inverseBindTransform.column(1).x() << " " <<m_inverseBindTransform.column(2).x()<< " " <<m_inverseBindTransform.column(3).x() <<endl;
//		cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).y() << " " <<m_inverseBindTransform.column(1).y() << " " <<m_inverseBindTransform.column(2).y()<< " " <<m_inverseBindTransform.column(3).y() <<endl;
//		cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).z() << " " <<m_inverseBindTransform.column(1).z() << " " <<m_inverseBindTransform.column(2).z()<< " " <<m_inverseBindTransform.column(3).z() <<endl;
//		cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).w() << " " <<m_inverseBindTransform.column(1).w() << " " <<m_inverseBindTransform.column(2).w()<< " " <<m_inverseBindTransform.column(3).w() <<endl;
	return m_inverseBindTransform;
}

void Bone::calcInverseBindTransform(QMatrix4x4 parentBindTransform){

//	parentBindTransform = parentBindTransform.transposed();
	QMatrix4x4 bindTransform = parentBindTransform * m_localBindTransform;
	m_inverseBindTransform = bindTransform.inverted();
	cout << "\t\t\t"<<m_name.toStdString()<<" Bone create"<<endl;
	cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).x() << " " <<m_inverseBindTransform.column(1).x() << " " <<m_inverseBindTransform.column(2).x()<< " " <<m_inverseBindTransform.column(3).x() <<endl;
	cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).y() << " " <<m_inverseBindTransform.column(1).y() << " " <<m_inverseBindTransform.column(2).y()<< " " <<m_inverseBindTransform.column(3).y() <<endl;
	cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).z() << " " <<m_inverseBindTransform.column(1).z() << " " <<m_inverseBindTransform.column(2).z()<< " " <<m_inverseBindTransform.column(3).z() <<endl;
	cout << "Bone m_inverseBindTransform matrix "<<this->m_index<<" : "<< m_inverseBindTransform.column(0).w() << " " <<m_inverseBindTransform.column(1).w() << " " <<m_inverseBindTransform.column(2).w()<< " " <<m_inverseBindTransform.column(3).w() <<endl;

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

