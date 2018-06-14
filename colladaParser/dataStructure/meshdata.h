#ifndef MESHDATA_H
#define MESHDATA_H
#include <vector>
#include "iostream"

using namespace std;

class MeshData
{
public:
	MeshData(vector<float> vertices, vector<float> textureCoords, vector<float> normals, vector<int> indices,
			 vector<int> boneIds, vector<float> vertexWeights);
	vector<int> getBoneIds();
	vector<float> getVertexWeights();
	vector<float> getVertices();
	vector<float> getTextureCoords();
	vector<float> getNormals();
	vector<int> getIndices();
    int getVertexCount();

private:
    static const int m_DIMENSIONS = 3;
	vector<float> m_vertices;
	vector<float> m_textureCoords;
	vector<float> m_normals;
	vector<int> m_indices;
	vector<int> m_boneIds;
	vector<float> m_vertexWeights;
};

#endif // MESHDATA_H
