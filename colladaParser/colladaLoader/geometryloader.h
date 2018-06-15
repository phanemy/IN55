#ifndef GEOMETRYLOADER_H
#define GEOMETRYLOADER_H
#include <QMatrix4x4>
#include <QDomNode>
#include <list>
#include <vector>
#include <vertexskindata.h>
#include <vertex.h>
#include <QVector2D>
#include <QVector3D>
#include <meshdata.h>
#include <QString>
#include <myxmlnode.h>

using namespace std;

class GeometryLoader
{
public:
    GeometryLoader(QDomNode geometryNode, QList<VertexSkinData> vertexWeights);
    MeshData extractModelData();

private:
	QMatrix4x4 m_CORRECTION;

    QDomNode m_meshData;

    QList<VertexSkinData> m_vertexWeights;

    QVector<float> m_verticesArray;
    QVector<float> m_normalsArray;
    QVector<float> m_texturesArray;
    QVector<int> m_indicesArray;
	QVector<int> m_boneIdsArray;
    QVector<float> m_weightsArray;

    QList<Vertex> m_vertices;
    QList<QVector2D> m_textures;
    QList<QVector3D> m_normals;
    QList<int> m_indices;

    void readRawData();
    void readPositions();
    void readNormals();
    void readTextureCoords();
    void assembleVertices();
    Vertex processVertex(int posIndex, int normIndex, int texIndex);
    QVector<int> convertIndicesListToArray();
    float convertDataToArrays();
    Vertex dealWithAlreadyProcessedVertex(Vertex previousVertex, int newTextureIndex, int newNormalIndex);
    void initArrays();
    void removeUnusedVertices();
};

#endif // GEOMETRYLOADER_H
