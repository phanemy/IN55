#ifndef MESHDYNAMIC_H
#define MESHDYNAMIC_H

#include "mesh.h"
#include "math.h"
#include <vector>
#include "bone.h"
#include "animation.h"
#include <iostream>

using namespace std;


class MeshDynamic : public Mesh
{
public:
	MeshDynamic(vector<int> indices,vector<float> vertices,vector<float> m_normals,vector<float> textCoord);
	virtual ~MeshDynamic();
	void drawGeometry(QOpenGLShaderProgram *program);
	void setVertexData(vector<int> indices,vector<float> vertices,vector<float> normals,vector<float> textureCoords);
	void setAnimationData(vector<int> boneId,vector<float> boneWeight, int nbBone);
	VertexData* getVertexData();
	QVector<QVector3D> getJointID();
	QVector<QVector3D> getWeigth();
    int getNbrVertice();
private:
	void createVertice(vector<int> indices,vector<float> vertices,vector<float> m_normals,vector<float> textCoord);
	void initGeometry();
};


#endif // MESHDYNAMIC_H
