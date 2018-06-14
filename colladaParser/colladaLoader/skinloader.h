#ifndef SKINLOADER_H
#define SKINLOADER_H
#include "skinningdata.h"
#include "vertexskindata.h"
#include <list>
#include <string>
#include <vector>
#include <QtXml>
#include "myxmlnode.h"
using namespace std;

class SkinLoader
{
public:
    SkinLoader(QDomNode controllersNode, int maxWeights);
    SkinningData extractSkinData();
private:
    QDomNode m_skinningData;
    const int m_maxWeights;
    QStringList loadJointsList();
    QList<float> loadWeights();
    QList<int> getEffectiveJointsCounts(QDomNode weightsDataNode);
    QList<VertexSkinData> getSkinData(QDomNode weightsDataNode, QList<int> counts, QList<float> weights);
};

#endif // SKINLOADER_H
