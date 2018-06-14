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
        QStringList jointsList = loadJointsList();
        QList<float> weights = loadWeights();
        QDomNode weightsDataNode = this->m_skinningData.firstChildElement("vertex_weights");
        QList<int> effectorJointCounts = getEffectiveJointsCounts(weightsDataNode);
//        for(int count : effectorJointCounts)
//            cout<<count <<endl;

        QList<VertexSkinData> vertexWeights = getSkinData(weightsDataNode, effectorJointCounts, weights);
        return SkinningData(jointsList, vertexWeights);
    }

QStringList SkinLoader::loadJointsList() {
        MyXmlNode inputNode = MyXmlNode(this->m_skinningData.firstChildElement("vertex_weights"));
        QString jointDataId = inputNode.getChildWithAttribute("input", "semantic", "JOINT").attributes().namedItem("source").toAttr().value().mid(1);
        QDomNode jointsNode = MyXmlNode(m_skinningData).getChildWithAttribute("source", "id", jointDataId).namedItem("Name_array");
        QDomNode bla = MyXmlNode(m_skinningData).getChildWithAttribute("source", "id", jointDataId).namedItem("Name_array");
        QStringList names = jointsNode.firstChild().nodeValue().split(" ");
        QStringList jointsList = QStringList();
        for (QString name : names) {
            jointsList.append(name);
        }
        return jointsList;
    }

QList<float> SkinLoader::loadWeights() {
        QDomNode inputNode = m_skinningData.namedItem("vertex_weights");
        QString weightsDataId = MyXmlNode(inputNode).getChildWithAttribute("input", "semantic", "WEIGHT").attributes().namedItem("source").toAttr().value().mid(1);

//        cout << "b" << weightsDataId.toStdString() <<endl;

//        cout << "b" << test.toElement().tagName().toStdString() <<endl;

        QDomNode weightsNode = MyXmlNode(m_skinningData).getChildWithAttribute("source", "id", weightsDataId).namedItem("float_array");


        QStringList rawData = weightsNode.firstChild().nodeValue().split(" ");
        QList<float> weights = QList<float>();
        for(QString data : rawData)
        {
//			cout << "b" << data.toFloat() <<endl;
            weights.push_back(data.toFloat());
        }
        return weights;
    }
QList<int> SkinLoader::getEffectiveJointsCounts(QDomNode weightsDataNode) {
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
                int jointId = QString(rawData[pointer++]).toInt();
                int weightId = QString(rawData[pointer++]).toInt();
                it = weights.begin();
                advance(it, weightId);
//				cout << "a "<<jointId<<endl;
                skinData.addJointEffect(jointId, *it);
            }

            skinData.limitJointNumber(this->m_maxWeights);
            skinningData.push_back(skinData);
        }
        return skinningData;
    }
