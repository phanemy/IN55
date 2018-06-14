#ifndef COLLADAPARSERDATASTRUCTUREERTEX_H
#define COLLADAPARSERDATASTRUCTUREERTEX_H
#include "QVector3D"
#include "vertexskindata.h"
#include <vector>

using namespace std;

class Vertex
{
public:
	Vertex(int index,QVector3D position, VertexSkinData weightsData);
    VertexSkinData getWeightsData();
    void addTangent(QVector3D tangent);
    void averageTangents();
    QVector3D getAverageTangent();
    int getIndex();
    float getLength();
    bool isSet();
    bool hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther);
    void setTextureIndex(int textureIndex);
    void setNormalIndex(int normalIndex);
    QVector3D getPosition();
    int getTextureIndex();
    int getNormalIndex();
	Vertex* getDuplicateVertex();
	void setDuplicateVertex(Vertex* duplicateVertex);


private:
    QVector3D m_position;
    int m_textureIndex = m_NO_INDEX;
    int m_normalIndex = m_NO_INDEX;
	Vertex* m_duplicateVertex = 0;
    int m_index;
    float m_length;
    vector<QVector3D> m_tangents;
    QVector3D m_averagedTangent = QVector3D(0,0,0);
    VertexSkinData m_weightsData;
	static const int m_NO_INDEX = -1;
};

#endif // COLLADAPARSERDATASTRUCTUREERTEX_H
