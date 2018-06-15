#include "bonetransform.h"

BoneTransform::BoneTransform(QVector3D pos, QQuaternion rot):m_position(pos),m_rotation(rot.normalized())
{
}

QMatrix4x4 BoneTransform::getLocalTransform(){
	QMatrix4x4 transform;
	transform.translate(m_position);
	transform.rotate(m_rotation);
	return transform;
}

BoneTransform BoneTransform::interpolate(BoneTransform frameA, BoneTransform frameB, float progression){
	QVector3D pos = interpolate(frameA.m_position, frameB.m_position, progression);
	QQuaternion rot = QQuaternion::slerp(frameA.m_rotation,frameB.m_rotation, progression);
	return BoneTransform(pos, rot);
}

QVector3D BoneTransform::interpolate(QVector3D start, QVector3D end, float progression) {
	float x = start.x() + (end.x() - start.x()) * progression;
	float y = start.y() + (end.y() - start.y()) * progression;
	float z = start.z() + (end.z() - start.z()) * progression;
	return QVector3D(x, y, z);
}
