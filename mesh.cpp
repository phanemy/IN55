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
//	m_colorBuf.create();
	m_jointIdBuf.create();
//	m_normalBuf.create();
	m_weightBuf.create();
//	m_verticesBuf.create();
}

Mesh::~Mesh()
{
	m_arrayBuf.destroy();
    m_indexBuf.destroy();
//	m_colorBuf.destroy();
	m_jointIdBuf.destroy();
//	m_normalBuf.destroy();
	m_weightBuf.destroy();
//	m_verticesBuf.destroy();

	free(m_vertices);
	free(m_indices);
}


