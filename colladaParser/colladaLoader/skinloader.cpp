#include "skinloader.h"
#include<iostream>

SkinLoader::SkinLoader(QDomNode controllersNode, int maxWeights) : m_maxWeights(maxWeights){
        QDomNode temp = controllersNode.firstChildElement("controller");
        if(!temp.isNull())
            this->m_skinningData = temp.firstChildElement("skin");
        else
            this->m_skinningData = QDomNode();

    }

SkinningData SkinLoader::extractSkinData() {
		QStringList bonesList = loadBonesList();
        QList<float> weights = loadWeights();
        QDomNode weightsDataNode = this->m_skinningData.firstChildElement("vertex_weights");
		QList<int> effectorBoneCounts = getEffectiveBonesCounts(weightsDataNode);
		QList<VertexSkinData> vertexWeights = getSkinData(weightsDataNode, effectorBoneCounts, weights);
		return SkinningData(bonesList, vertexWeights);
    }

QStringList SkinLoader::loadBonesList() {
        MyXmlNode inputNode = MyXmlNode(this->m_skinningData.firstChildElement("vertex_weights"));
		QString boneDataId = inputNode.getChildWithAttribute("input", "semantic", "JOINT").attributes().namedItem("source").toAttr().value().mid(1);
		QDomNode bonesNode = MyXmlNode(m_skinningData).getChildWithAttribute("source", "id", boneDataId).namedItem("Name_array");
		QDomNode bla = MyXmlNode(m_skinningData).getChildWithAttribute("source", "id", boneDataId).namedItem("Name_array");
		QStringList names = bonesNode.firstChild().nodeValue().split(" ");
		QStringList bonesList = QStringList();
        for (QString name : names) {
			bonesList.append(name);
        }
		return bonesList;
    }

QList<float> SkinLoader::loadWeights() {
        QDomNode inputNode = m_skinningData.namedItem("vertex_weights");
        QString weightsDataId = MyXmlNode(inputNode).getChildWithAttribute("input", "semantic", "WEIGHT").attributes().namedItem("source").toAttr().value().mid(1);
        QDomNode weightsNode = MyXmlNode(m_skinningData).getChildWithAttribute("source", "id", weightsDataId).namedItem("float_array");
        QStringList rawData = weightsNode.firstChild().nodeValue().split(" ");
        QList<float> weights = QList<float>();
        for(QString data : rawData)
        {
            weights.push_back(data.toFloat());
        }
        return weights;
    }
QList<int> SkinLoader::getEffectiveBonesCounts(QDomNode weightsDataNode) {
        QStringList rawData = weightsDataNode.namedItem("vcount").firstChild().nodeValue().split(" ");
        QList<int> counts = QList<int>();
        for(QString data : rawData)
        {
            if(data!= "")
                counts.push_back(data.toInt());

        }
        return counts;
   }

QList<VertexSkinData> SkinLoader::getSkinData(QDomNode weightsDataNode, QList<int> counts, QList<float> weights){
        QStringList rawData = weightsDataNode.namedItem("v").firstChild().nodeValue().split(" ");
        QList<VertexSkinData> skinningData = QList<VertexSkinData>();
        QList<float>::iterator it;
        int pointer = 0;
        for (int count : counts) {
            VertexSkinData skinData = VertexSkinData();
            for (int i = 0; i < count; i++) {
				int boneId = QString(rawData[pointer++]).toInt();
                int weightId = QString(rawData[pointer++]).toInt();
                it = weights.begin();
                advance(it, weightId);
				skinData.addBoneEffect(boneId, *it);
            }
			skinData.limitBoneNumber(this->m_maxWeights);
            skinningData.push_back(skinData);
        }
        return skinningData;
    }
