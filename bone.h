#ifndef BONE_H
#define BONE_H
#include<QMatrix4x4>
#include<vector>
#include <iostream>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

using namespace std;

class Bone
{
public:
	Bone();
	Bone(int index, QString name, QMatrix4x4 bindLocalTransform);
	~Bone();
	void addChild(Bone* child);
	QMatrix4x4 getAnimatedTransform();
	void setAnimationTransform(QMatrix4x4 animationTransform);
	QMatrix4x4 getInverseBindTransform();
	void calcInverseBindTransform(QMatrix4x4 parentBindTransform);
	QString getName();
	vector<Bone*>& getChildren();
	int getId();
	void calculateGeometry();
private:
	int m_index;// ID
	QString m_name;
	vector<Bone*> m_children;
	QMatrix4x4 m_animatedTransform;
	QMatrix4x4 m_localBindTransform;
	QMatrix4x4 m_inverseBindTransform;
};

#endif // BONE_H
