#include "meshdynamic.h"

MeshDynamic::MeshDynamic(vector<int> indices,vector<float> vertices,vector<float> normals,vector<float> textCoord):Mesh()
{
	m_vertices=0;
	m_indices=0;
	createVertice(indices,vertices,normals,textCoord);
	initGeometry();
}

MeshDynamic::~MeshDynamic()
{}

void MeshDynamic::initGeometry()
{
////! [1]
	// Transfer vertex data to VBO 0
	m_arrayBuf.bind();
	m_arrayBuf.allocate(m_vertices, m_nbrVertices * sizeof(VertexData));

	// Transfer index data to VBO 1
	m_indexBuf.bind();
	m_indexBuf.allocate(m_indices, m_nbrIndices * sizeof(GLushort));
	m_indexBuf.release();
//! [1]
}


void MeshDynamic::createVertice(vector<int> indices,vector<float> vertices,vector<float> normals,vector<float> textCoord){
    m_nbrIndices = indices.size();
    m_indices = (GLushort*) malloc(sizeof(GLushort) * m_nbrIndices);
    for(int i = 0; i < m_nbrIndices; ++i){
        m_indices[i] = indices[i];
    }
    m_nbrVertices = vertices.size()/3;
	m_vertices = (VertexData*) malloc(sizeof(VertexData) * m_nbrVertices);

	for(int i = 0;i < m_nbrVertices; ++i){
		m_vertices[i].position = QVector3D(vertices[i*3],vertices[i*3+1],vertices[i*3+2]);
		m_vertices[i].color = QVector3D(0, 1, 0);
		m_vertices[i].normal = QVector3D(normals[i*3],normals[i*3+1],normals[i*3+2]);
		m_vertices[i].texCoords = QVector2D(textCoord[i*2],textCoord[i*2+1]);
	}


}

void MeshDynamic::setAnimationData(vector<int> boneId,vector<float> boneWeight, int nbBone){

    for(int i = 0; i < m_nbrVertices; ++i)
	 {
		m_boneIds.push_back(QVector3D(boneId[i*3],boneId[i*3+1],boneId[i*3+2]));
		m_weights.push_back(QVector3D(boneWeight[i*3],boneWeight[i*3+1],boneWeight[i*3+2]));
	 }

	m_weightBuf.bind();
	m_weightBuf.allocate(m_weights.constData(), m_weights.size() * sizeof(QVector3D));
	m_weightBuf.release();

	m_boneIdBuf.bind();
	m_boneIdBuf.allocate(m_boneIds.constData(), m_boneIds.size() * sizeof(QVector3D));
	m_boneIdBuf.release();
}

void MeshDynamic::drawGeometry(QOpenGLShaderProgram *program)
{
	// Tell OpenGL which VBOs to use

	m_arrayBuf.bind();

	// Offset for position
	quintptr offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertexLocation = program->attributeLocation("in_position");
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	// Offset for texture coordinate
	offset += sizeof(QVector3D);
	int colorLocation = program->attributeLocation("in_color");
	program->enableAttributeArray(colorLocation);
	program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	// Offset for texture coordinate
	offset += sizeof(QVector3D);

	// Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
	int normalLocation = program->attributeLocation("in_normal");
	program->enableAttributeArray(normalLocation);
	program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	offset += sizeof(QVector3D);

	// Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
	int textCoordLocation = program->attributeLocation("in_textureCoords");
	program->enableAttributeArray(textCoordLocation);
	program->setAttributeBuffer(textCoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

	m_arrayBuf.release();

	m_boneIdBuf.bind();
		int boneLocation = program->attributeLocation("in_boneIndices");
		program->enableAttributeArray(boneLocation);
		program->setAttributeBuffer(boneLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));
	m_boneIdBuf.release();

	m_weightBuf.bind();
	int weightLocation = program->attributeLocation("in_weights");
	program->enableAttributeArray(weightLocation);
	program->setAttributeBuffer(weightLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));
	m_weightBuf.release();

	m_indexBuf.bind();
	// Draw cube geometry using indices from VBO 1
	glDrawElements(GL_TRIANGLES, m_nbrIndices, GL_UNSIGNED_SHORT, 0);

	m_indexBuf.release();
}

VertexData* MeshDynamic::getVertexData(){
	return m_vertices;
}

QVector<QVector3D> MeshDynamic::getBoneID(){
	return m_boneIds;
}

QVector<QVector3D> MeshDynamic::getWeigth(){
	return m_weights;
}

int MeshDynamic::getNbrVertice(){
	return m_nbrVertices;
}
