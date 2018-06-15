#ifndef BONETRANSFORM_H
#define BONETRANSFORM_H
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <iostream>

//Contains the transformation information and matrix of a bone

using namespace std;

class BoneTransform
{
public:
	BoneTransform(QVector3D pos, QQuaternion rot);
	QMatrix4x4 getLocalTransform();
	static BoneTransform interpolate(BoneTransform frameA, BoneTransform frameB, float progression);
	static QVector3D interpolate(QVector3D start, QVector3D end, float progression);

private:
	QVector3D m_position;
	QQuaternion m_rotation;
};

#endif // BONETRANSFORM_H
