#include "meshdata.h"

MeshData::MeshData(vector<float> vertices, vector<float> textureCoords, vector<float> normals, vector<int> indices,
				   vector<int> boneIds, vector<float> vertexWeights){
    this->m_vertices = vertices;
    this->m_textureCoords = textureCoords;
    this->m_normals = normals;
    this->m_indices = indices;
    this->m_boneIds = boneIds;
    this->m_vertexWeights = vertexWeights;
}

vector<int> MeshData::getBoneIds(){
    return this->m_boneIds;
}

vector<float> MeshData::getVertexWeights(){
    return this->m_vertexWeights;
}

vector<float> MeshData::getVertices(){
    return this->m_vertices;
}

vector<float> MeshData::getTextureCoords(){
    return this->m_textureCoords;
}

vector<float> MeshData::getNormals(){
    return this->m_normals;
}

vector<int> MeshData::getIndices(){
    return this->m_indices;
}

int MeshData::getVertexCount(){
    return this->m_vertices.size()/m_DIMENSIONS;
}
