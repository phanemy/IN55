#include "skeletonloader.h"

SkeletonLoader::SkeletonLoader(QDomNode visualSceneNode, QStringList boneOrder):m_boneOrder(boneOrder){
    m_armatureData = MyXmlNode(visualSceneNode.namedItem("visual_scene")).getChildWithAttribute("node","id","Armature");
    m_CORRECTION = QMatrix4x4();
	m_CORRECTION.rotate(-90,QVector3D(1,0,0));
}

SkeletonData SkeletonLoader::extractBoneData(){
    QDomNode headNode = m_armatureData.namedItem("node");
    BoneData headJoint = loadJointData(headNode, true);
    return SkeletonData(m_boneCount, headJoint);
}

BoneData SkeletonLoader::loadJointData(QDomNode jointNode, bool isRoot){
    BoneData joint = extractMainJointData(jointNode, isRoot);
//	cout<<"loadJointData "<< joint.getIndex()<< " "<<joint.getNameId().toStdString() <<endl;
	QDomNodeList listNode = MyXmlNode(jointNode).getChildren("node");
    for(int i = 0; i < listNode.size(); ++i){
        joint.addChild(loadJointData(listNode.item(i), false));
    }
    return joint;
}

BoneData SkeletonLoader::extractMainJointData(QDomNode jointNode, bool isRoot){
    QString nameId = jointNode.attributes().namedItem("id").toAttr().value();
	int index = m_boneOrder.indexOf(nameId);
	QStringList matrixData = jointNode.namedItem("matrix").firstChild().nodeValue().split(" ");
	QMatrix4x4 matrix = QMatrix4x4(convertData(matrixData));
//	cout << "SkeletonLoader matrix "<< matrix.column(0).x() <<" " <<matrix.column(1).x() <<" "<<matrix.column(2).x() <<" "<<matrix.column(3).x() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).y() <<" " <<matrix.column(1).y() <<" "<<matrix.column(2).y() <<" "<<matrix.column(3).y() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).z() <<" " <<matrix.column(1).z() <<" "<<matrix.column(2).z() <<" "<<matrix.column(3).z() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).w() <<" " <<matrix.column(1).w() <<" "<<matrix.column(2).w() <<" "<<matrix.column(3).w() <<"\n"<<endl;

//	matrix = matrix.transposed();
//	cout << "SkeletonLoader matrix "<< matrix.column(0).x() <<" " <<matrix.column(1).x() <<" "<<matrix.column(2).x() <<" "<<matrix.column(3).x() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).y() <<" " <<matrix.column(1).y() <<" "<<matrix.column(2).y() <<" "<<matrix.column(3).y() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).z() <<" " <<matrix.column(1).z() <<" "<<matrix.column(2).z() <<" "<<matrix.column(3).z() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).w() <<" " <<matrix.column(1).w() <<" "<<matrix.column(2).w() <<" "<<matrix.column(3).w() <<"\n"<<endl;
//	matrix = matrix.transposed();
	if(isRoot){
		//because in Blender z is up, but in our game y is up.
		matrix = matrix * m_CORRECTION;
	}
//	cout << "SkeletonLoader matrix "<< matrix.column(0).x() <<" " <<matrix.column(1).x() <<" "<<matrix.column(2).x() <<" "<<matrix.column(3).x() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).y() <<" " <<matrix.column(1).y() <<" "<<matrix.column(2).y() <<" "<<matrix.column(3).y() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).z() <<" " <<matrix.column(1).z() <<" "<<matrix.column(2).z() <<" "<<matrix.column(3).z() <<endl;
//	cout << "SkeletonLoader matrix "<< matrix.column(0).w() <<" " <<matrix.column(1).w() <<" "<<matrix.column(2).w() <<" "<<matrix.column(3).w() <<"\n"<<endl;
	cout<<"\n"<<endl;

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
