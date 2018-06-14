#include "vertex.h"

using namespace std;

Vertex::Vertex(int index,QVector3D position, VertexSkinData weightsData):m_position(position){
	m_index = index;
	m_weightsData = weightsData;
	m_length = position.length();
}

VertexSkinData Vertex::getWeightsData(){
    return this->m_weightsData;
}

void Vertex::addTangent(QVector3D tangent){
    this->m_tangents.push_back(tangent);
}

void Vertex::averageTangents(){
    if(m_tangents.empty()){
        return;
    }
    for(QVector3D tangent : m_tangents){
        m_averagedTangent = tangent + m_averagedTangent;
    }
    m_averagedTangent.normalize();
}

QVector3D Vertex::getAverageTangent(){
    return this->m_averagedTangent;
}

int Vertex::getIndex(){
    return this->m_index;
}

float Vertex::getLength(){
    return this->m_length;
}

bool Vertex::isSet(){
	return (m_textureIndex!=m_NO_INDEX || m_normalIndex!=m_NO_INDEX);
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther){
    return textureIndexOther==this->m_textureIndex && normalIndexOther==this->m_normalIndex;
}

void Vertex::setTextureIndex(int textureIndex){
    this->m_textureIndex = textureIndex;
}

void Vertex::setNormalIndex(int normalIndex){
    this->m_normalIndex = normalIndex;
}

QVector3D Vertex::getPosition(){
    return m_position;
}

int Vertex::getTextureIndex(){
    return this->m_textureIndex;
}

int Vertex::getNormalIndex(){
    return this->m_normalIndex;
}

Vertex* Vertex::getDuplicateVertex(){
    return this->m_duplicateVertex;
}

void Vertex::setDuplicateVertex(Vertex* duplicateVertex){
	this->m_duplicateVertex = m_duplicateVertex;
}
