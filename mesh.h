#ifndef MESH_H
#define MESH_H
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

struct VertexData
{
    QVector3D position;
	QVector3D color;
//	QVector3D joinIds;
//	QVector3D weights;
	QVector3D normal;
	QVector3D texCoords;
};

class Mesh: protected QOpenGLFunctions
{
public:
    Mesh();
    ~Mesh();
    virtual void drawGeometry(QOpenGLShaderProgram *program) = 0;

protected:
    virtual void initGeometry() = 0;
	QOpenGLBuffer m_arrayBuf;
    QOpenGLBuffer m_indexBuf;
	QOpenGLBuffer m_boneIdBuf;
	QOpenGLBuffer m_weightBuf;

	GLushort* m_indices;
	VertexData* m_vertices;
	QVector<QVector3D> m_boneIds;
	QVector<QVector3D> m_weights;

    int m_nbrVertices;
    int m_nbrIndices;
	int m_nbrBones;
};

#endif // MESH_H
