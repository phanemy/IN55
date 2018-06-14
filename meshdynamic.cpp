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
//    cout<<"MeshDynamic create index"<<endl;
    m_nbrIndices = indices.size();
    m_indices = (GLushort*) malloc(sizeof(GLushort) * m_nbrIndices);
    for(int i = 0; i < m_nbrIndices; ++i){
        m_indices[i] = indices[i];
    }
    m_nbrVertices = vertices.size()/3;
//    cout<<"MeshDynamic create vertex m_nbrVertices: "<<m_nbrVertices<<endl;
	m_vertices = (VertexData*) malloc(sizeof(VertexData) * m_nbrVertices);

	for(int i = 0;i < m_nbrVertices; ++i){
		m_vertices[i].position = QVector3D(vertices[i*3],vertices[i*3+1],vertices[i*3+2]);
		m_vertices[i].color = QVector3D(0, 1, 0);
		m_vertices[i].normal = QVector3D(normals[i*3],normals[i*3+1],normals[i*3+2]);
		m_vertices[i].texCoords = QVector2D(textCoord[i*2],textCoord[i*2+1]);
//		m_verticesList.push_back(QVector3D(vertices[i*3],vertices[i*3+1],vertices[i*3+2]));
//		m_color.push_back(QVector3D(0, 0, 1));
//		m_normal.push_back(QVector3D(normals[i*3],normals[i*3+1],normals[i*3+2]));
	}
//	m_colorBuf.bind();
//	m_colorBuf.allocate(m_color.constData(), m_color.size() * sizeof(QVector3D));
//	m_colorBuf.release();
//	m_verticesBuf.bind();
//	m_verticesBuf.allocate(m_verticesList.constData(), m_verticesList.size() * sizeof(QVector3D));
//	m_verticesBuf.release();
//	m_normalBuf.bind();
//	m_normalBuf.allocate(m_normal.constData(), m_normal.size() * sizeof(QVector3D));
//	m_normalBuf.release();

//    cout<<"MeshDynamic create vertex end"<<endl;

}

void MeshDynamic::setAnimationData(vector<int> boneId,vector<float> boneWeight, int nbBone){
//	this->m_nbrBones = boneWeight.size()/3;
//    cout<<"animeData "<< m_nbrVertices<< " "<< boneWeight.size() << " "<< boneId.size()<<endl;
    for(int i = 0; i < m_nbrVertices; ++i)
	 {
//		m_vertices[i].joinIds = QVector3D(boneId[i*3],boneId[i*3+1],boneId[i*3+2]);
//		m_vertices[i].weights = QVector3D(boneWeight[i*3],boneWeight[i*3+1],boneWeight[i*3+2]);
//        int i = m_indices[j];
		m_joinIds.push_back(QVector3D(boneId[i*3],boneId[i*3+1],boneId[i*3+2]));
		m_weights.push_back(QVector3D(boneWeight[i*3],boneWeight[i*3+1],boneWeight[i*3+2]));
//		cout <<"i = "<<m_vertices[i].position.x()<<" "<<m_vertices[i].position.y()<<" "<<m_vertices[i].position.z()<<endl;
//        cout << boneId[i*3] <<" "<<boneId[i*3+1]<<" "<<boneId[i*3+2]<<endl;
//		cout << boneWeight[i*3] << " " <<boneWeight[i*3+1] << " " << boneWeight[i*3+2] <<endl;

	 }
//    cout<<"all Data "<<m_nbrIndices<<endl;
//    for(int j = 0; j < m_nbrIndices; ++j)
//     {
//        int i = m_indices[j];
//        cout<<"indice "<<i<<endl;
//        cout<< "vertice "<<i<<" : "<<m_vertices[i].position.x()<<" "<<m_vertices[i].position.y() <<" "<< m_vertices[i].position.z() <<endl;
//        cout<< "joinIds "<<m_joinIds[i].x()<<" "<<m_joinIds[i].y() <<" "<< m_joinIds[i].z() <<endl;
//        cout<< "weights "<<m_weights[i].x()<<" "<< m_weights[i].y() <<" "<< m_weights[i].z() <<endl;
//        cout<< ""<<endl;
//     }

	m_weightBuf.bind();
	m_weightBuf.allocate(m_weights.constData(), m_weights.size() * sizeof(QVector3D));
	m_weightBuf.release();

	m_jointIdBuf.bind();
	m_jointIdBuf.allocate(m_joinIds.constData(), m_joinIds.size() * sizeof(QVector3D));
	m_jointIdBuf.release();
}

void MeshDynamic::drawGeometry(QOpenGLShaderProgram *program)
{
	// Tell OpenGL which VBOs to use
	int test = m_nbrIndices;
//        cout << "nb vertice "<< m_nbrVertices<<endl;

//    for(int j = 0; j<m_nbrIndices; j++)
//    {
//        int i = m_indices[j];
//        cout<< "vertice "<<i<<" : "<<m_vertices[i].position.x()<<" "<<m_vertices[i].position.y() <<" "<< m_vertices[i].position.z() <<endl;
//        cout<< "joinIds "<<m_joinIds[i].x()<<" "<<m_joinIds[i].y() <<" "<< m_joinIds[i].z() <<endl;
//        cout<< "weights "<<m_weights[i].x()<<" "<< m_weights[i].y() <<" "<< m_weights[i].z() <<endl;
////		cout<< "next"<<endl;
//        if(j%3==2)
//            cout<<" "<<endl;
//    }
//    cout<<" "<<endl;
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

	// Tell OpenGL programmable pipeline how to locate vertex texture coordinate data

//	// Offset for texture coordinate
//	offset += sizeof(QVector3D);

//	// Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//	int boneLocation = program->attributeLocation("in_jointIndices");
//	program->enableAttributeArray(boneLocation);
//	program->setAttributeBuffer(boneLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	// Offset for texture coordinate
//	offset += sizeof(QVector3D);

	// Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//	int weightLocation = program->attributeLocation("in_weights");
//	program->enableAttributeArray(weightLocation);
//	program->setAttributeBuffer(weightLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

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

//	m_verticesBuf.bind();
//		int vertexLocation = program->attributeLocation("in_position");
//		program->enableAttributeArray(vertexLocation);
//		program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));
//	m_verticesBuf.destroy();
//	m_colorBuf.bind();
//		int colorLocation = program->attributeLocation("color");
//		program->enableAttributeArray(colorLocation);
//		program->setAttributeBuffer(colorLocation, GL_FLOAT, 0, 3, sizeof(VertexData));
//	m_colorBuf.release();
	m_jointIdBuf.bind();
		int boneLocation = program->attributeLocation("in_jointIndices");
		program->enableAttributeArray(boneLocation);
		program->setAttributeBuffer(boneLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));
	m_jointIdBuf.release();
//	m_normalBuf.bind();
//		int normalLocation = program->attributeLocation("in_normal");
//		program->enableAttributeArray(normalLocation);
//		program->setAttributeBuffer(normalLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));
//	m_normalBuf.release();

	m_weightBuf.bind();
	int weightLocation = program->attributeLocation("in_weights");
	program->enableAttributeArray(weightLocation);
	program->setAttributeBuffer(weightLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));
	m_weightBuf.release();

	m_indexBuf.bind();
	// Draw cube geometry using indices from VBO 1
//    glDrawElements(GL_POINTS, test, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLES, test, GL_UNSIGNED_SHORT, 0);

	m_indexBuf.release();
}

VertexData* MeshDynamic::getVertexData(){
	return m_vertices;
}

QVector<QVector3D> MeshDynamic::getJointID(){
	return m_joinIds;
}

QVector<QVector3D> MeshDynamic::getWeigth(){
	return m_weights;
}

int MeshDynamic::getNbrVertice(){
	return m_nbrVertices;
}
