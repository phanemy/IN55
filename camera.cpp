#include "camera.h"

Camera::Camera() : position(0,0,0), direction(0,0,1), projection(), up(0,1,0), speed(1),pivot(0,0,0)
{
}

Camera::Camera(QVector3D pos, QVector3D dir) : position(pos), direction(dir), projection(), up(0,1,0), speed(1),pivot(0,0,0)
{
}

void Camera::moveTo(QVector3D vect)
{
	position = vect;
}

void Camera::moveTo(float x, float y, float z)
{
	position.setX(x);
	position.setY(y);
	position.setZ(z);
}

void Camera::moveForward(QVector3D vect)
{
	position += vect;
}

void Camera::moveUp(QVector3D vect)
{
    position += vect;
    pivot += vect;
}

void Camera::rotate(QQuaternion q)
{
	q.normalize();
    QQuaternion qp = QQuaternion(position-pivot);
	qp = qp * q;
	QVector4D temp = qp.toVector4D();
    temp = temp + pivot;
	position.setX(temp.x());
	position.setY(temp.y());
	position.setZ(temp.z());
	direction = -position;
//	up = q.rotatedVector(up);
}

void Camera::calculateProjection(int w, int h)
{
	qreal aspect = qreal(w) / qreal(h ? h : 1);

	const qreal zNear = 0.5, zFar = 50.0, fov = 45.0;

	projection.setToIdentity();

	projection.perspective(fov, aspect, zNear, zFar);
}

QMatrix4x4 Camera::cameraMatrix() const
{
	QMatrix4x4 view;
	view.setToIdentity();
    view.lookAt(position, pivot, up);

	return projection * view;
}

void Camera::setSpeed(const float v)
{
	if (v < 0)
		speed = 0;
	else
		speed = v;
}

float Camera::getSpeed() const
{
	return speed;
}

QVector3D Camera::getUp() const
{
	return up;
}

QVector3D Camera::getDir() const
{
	return direction;
}

QVector3D Camera::getPosition() const
{
	return position;
}
