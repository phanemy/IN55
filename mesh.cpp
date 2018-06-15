#include "mesh.h"

#include <QVector2D>
#include <QVector3D>
using namespace std;

Mesh::Mesh()
    : m_indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    // Generate 2 VBOs
	m_arrayBuf.create();
    m_indexBuf.create();
	m_boneIdBuf.create();
	m_weightBuf.create();
}

Mesh::~Mesh()
{
	m_arrayBuf.destroy();
    m_indexBuf.destroy();
	m_boneIdBuf.destroy();
	m_weightBuf.destroy();

	free(m_vertices);
	free(m_indices);
}


