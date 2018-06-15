#include "skeletonloader.h"

SkeletonLoader::SkeletonLoader(QDomNode visualSceneNode, QStringList boneOrder):m_boneOrder(boneOrder){
    m_armatureData = MyXmlNode(visualSceneNode.namedItem("visual_scene")).getChildWithAttribute("node","id","Armature");
    m_CORRECTION = QMatrix4x4();
	m_CORRECTION.rotate(-90,QVector3D(1,0,0));
}

SkeletonData SkeletonLoader::extractBoneData(){
    QDomNode headNode = m_armatureData.namedItem("node");
	BoneData headBone = loadBoneData(headNode, true);
	return SkeletonData(m_boneCount, headBone);
}

BoneData SkeletonLoader::loadBoneData(QDomNode boneNode, bool isRoot){
	BoneData bone = extractMainBoneData(boneNode, isRoot);
	QDomNodeList listNode = MyXmlNode(boneNode).getChildren("node");
    for(int i = 0; i < listNode.size(); ++i){
		bone.addChild(loadBoneData(listNode.item(i), false));
    }
	return bone;
}

BoneData SkeletonLoader::extractMainBoneData(QDomNode boneNode, bool isRoot){
	QString nameId = boneNode.attributes().namedItem("id").toAttr().value();
	int index = m_boneOrder.indexOf(nameId);
	QStringList matrixData = boneNode.namedItem("matrix").firstChild().nodeValue().split(" ");
	QMatrix4x4 matrix = QMatrix4x4(convertData(matrixData));
//	matrix = matrix.transposed();
	if(isRoot){
		matrix = matrix * m_CORRECTION;
	}

	m_boneCount++;
    return BoneData(index, nameId, matrix);
}


float* SkeletonLoader::convertData(QStringList rawData){
    float matrixData[16];
    QStringList::iterator itData = rawData.begin();
    QString temp;
	for(int i=0; i < 16; i++){
        temp = *itData;
        matrixData[i] = temp.toFloat();
		itData++;
	}

    return matrixData;
}
