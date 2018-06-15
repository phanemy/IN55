#ifndef SKINNINGDATA_H
#define SKINNINGDATA_H
#include <list>
#include <QString>
#include <QStringList>
#include "vertexskindata.h"

using namespace std;

class SkinningData
{
public:
	SkinningData(QStringList bonesOrder, QList<VertexSkinData> verticesSkinData);
    QStringList getBoneOrder();
    QList<VertexSkinData> getVertexSkinData();

private:
    const QStringList m_boneOrder;
    const QList<VertexSkinData> m_vertexSkinData;
};

#endif // SKINNINGDATA_H
