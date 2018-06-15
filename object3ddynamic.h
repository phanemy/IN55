#ifndef OBJECT3DDYNAMIC_H
#define OBJECT3DDYNAMIC_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "meshdynamic.h"
#include <qquaternion.h>
#include<vector>
#include "iostream"
#include "animator.h"
#include <QOpenGLTexture>
#include <QGLContext>

using namespace std;

class Object3DDynamic : protected QOpenGLFunctions{
public:
	Object3DDynamic();
	Object3DDynamic(vector<int> indices,vector<float> vertices,vector<float> m_normals,vector<float> textCoord, int nbBone, Bone* rootBone);
	~Object3DDynamic();
	void drawGeometry(QOpenGLShaderProgram *program,QMatrix4x4 projection);
	MeshDynamic* getMesh();
	void setLocation(QVector3D location);
	QVector3D getLocation();
	void setScale(QVector3D scale);
	QVector3D getScale();
	void setPivot(QVector3D pivot);
	QVector3D getPivot();
	void setRotation(QQuaternion rotation);
	QQuaternion getRotation();
	void setParent(Object3DDynamic* parent);
	QMatrix4x4 getTransform();
	void setTransform(QMatrix4x4 transform);
	void setAnimationList(Animation);
	Bone* getRootBone();
	void computeAnimation(float time);
	vector<QMatrix4x4> getBoneTransforms();
	void setTexture(QString textUrl);
protected:
	std::vector<Object3DDynamic*> m_child;
	Object3DDynamic* m_parent;
	MeshDynamic* m_mesh;
	QVector3D m_location;
	QVector3D m_scale;
	QVector3D m_pivot;
	QQuaternion m_rotation;
	QMatrix4x4 m_transform;
	Bone* m_rootBone;
	Animation m_animation;
	Animator m_animator;
	int m_nbBone;
	void addBonesToArray(Bone* headBone, vector<QMatrix4x4>& boneMatrix);
	QOpenGLTexture* m_texture;
};

#endif // OBJECT3DDYNAMIC_H
