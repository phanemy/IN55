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
//	QOpenGLBuffer m_normalBuf;
//	QOpenGLBuffer m_colorBuf;
	QOpenGLBuffer m_jointIdBuf;
	QOpenGLBuffer m_weightBuf;
//	QOpenGLBuffer m_verticesBuf;

	GLushort* m_indices;
	VertexData* m_vertices;
//	QVector<QVector3D> m_position;
//	QVector<QVector3D> m_color;
	QVector<QVector3D> m_joinIds;
	QVector<QVector3D> m_weights;
//	QVector<QVector3D> m_normal;
//	QVector<QVector3D> m_verticesList;

    int m_nbrVertices;
    int m_nbrIndices;
	int m_nbrBones;
};

#endif // MESH_H
