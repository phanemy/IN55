#include "skinningdata.h"

using namespace std;


SkinningData::SkinningData(QStringList boneOrder, QList<VertexSkinData> vertexSkinData):m_boneOrder(boneOrder),m_vertexSkinData(vertexSkinData){}

QStringList SkinningData::getBoneOrder(){
    return this->m_boneOrder;
}

QList<VertexSkinData> SkinningData::getVertexSkinData(){
    return this->m_vertexSkinData;
}

