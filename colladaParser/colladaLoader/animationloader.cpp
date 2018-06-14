#include "animationloader.h"


AnimationLoader::AnimationLoader(QDomNode animationData, QDomNode jointHierarchy){
	this->m_animationData = animationData;
	this->m_jointHierarchy = jointHierarchy;
	m_CORRECTION = QMatrix4x4();
	m_CORRECTION.rotate(-90,QVector3D(1,0,0));
	cout << "m_CORRECTION  "<< m_CORRECTION.column(0).x() << " " <<m_CORRECTION.column(1).x() << " " <<m_CORRECTION.column(2).x()<< " " <<m_CORRECTION.column(3).x()  <<endl;
	cout << "m_CORRECTION  "<< m_CORRECTION.column(0).y() << " " <<m_CORRECTION.column(1).y() << " " <<m_CORRECTION.column(2).y()<< " " <<m_CORRECTION.column(3).y()  <<endl;
	cout << "m_CORRECTION  "<< m_CORRECTION.column(0).z() << " " <<m_CORRECTION.column(1).z() << " " <<m_CORRECTION.column(2).z()<< " " <<m_CORRECTION.column(3).z()  <<endl;
	cout << "m_CORRECTION  "<< m_CORRECTION.column(0).w() << " " <<m_CORRECTION.column(1).w() << " " <<m_CORRECTION.column(2).w()<< " " <<m_CORRECTION.column(3).w()  <<endl;
}
AnimationLoader::~AnimationLoader(){}

AnimationData AnimationLoader::extractAnimation(){
	QString rootNode = findRootJointName();
	vector<float> times = getKeyTimes();
	float duration = times[times.size()-1];
	vector<KeyFrameData> keyFrames = initKeyFrames(times);
	QDomNodeList animationNodes = MyXmlNode(m_animationData).getChildren("animation");
	for(int i =0 ; i < animationNodes.size(); ++i){
		loadJointTransforms(keyFrames, animationNodes.item(i), rootNode);
	}
	return AnimationData(duration, keyFrames);
}

vector<float> AnimationLoader::getKeyTimes(){
	QDomNode timeData = m_animationData.namedItem("animation").namedItem("source").namedItem("float_array");
	QStringList rawTimes = timeData.firstChild().nodeValue().split(" ");
	vector<float> times (rawTimes.size());
	for(int i=0;i<times.size();i++){
		times[i] = QString(rawTimes[i]).toFloat();
	}
	return times;
}

vector<KeyFrameData> AnimationLoader::initKeyFrames(vector<float> times){
	vector<KeyFrameData> frames(times.size());
	for(int i=0;i<frames.size();i++){
		frames[i] =  KeyFrameData(times[i]);
	}
	return frames;
}

void AnimationLoader::loadJointTransforms(vector<KeyFrameData>& frames, QDomNode jointData, QString rootNodeId){
	QString jointNameId = getJointName(jointData);
	QString dataId = getDataId(jointData);
	QDomNode transformData = MyXmlNode(jointData).getChildWithAttribute("source", "id", dataId);
	QStringList rawData = transformData.namedItem("float_array").firstChild().nodeValue().split(" ");
	processTransforms(jointNameId, rawData, frames, jointNameId==rootNodeId);
}

QString AnimationLoader::getDataId(QDomNode jointData){
	QDomNode node = MyXmlNode(jointData.namedItem("sampler")).getChildWithAttribute("input", "semantic", "OUTPUT");
	return node.attributes().namedItem("source").nodeValue().mid(1);
}

QString AnimationLoader::getJointName(QDomNode jointData){
	QDomNode channelNode = jointData.namedItem("channel");
	QString data = channelNode.attributes().namedItem("target").nodeValue();
	return *(data.split("/").begin());
}

void AnimationLoader::processTransforms(QString jointName, QStringList rawData, vector<KeyFrameData>& keyFrames, bool root){
	float matrixData[16];
	for(int i=0;i<keyFrames.size();i++){
		for(int j=0;j<16;j++){
			matrixData[j] = QString(rawData[i*16 + j]).toFloat();
		}
		QMatrix4x4 transform = QMatrix4x4(matrixData);
//		transform = transform.transposed();
		if(root){
//			cout <<"process Transforms root "<<jointName.toStdString()<<endl;
			transform =  transform * m_CORRECTION;
		}
//        transform = transform.transposed();

//		cout << "transform matrix "<< transform.column(0).x() <<" " <<transform.column(1).x() <<" " <<transform.column(2).x() <<" " <<transform.column(3).x() <<endl;
//		cout << "transform matrix "<< transform.column(0).y() <<" " <<transform.column(1).y() <<" " <<transform.column(2).y() <<" " <<transform.column(3).y() <<endl;
//		cout << "transform matrix "<< transform.column(0).z() <<" " <<transform.column(1).z() <<" " <<transform.column(2).z() <<" " <<transform.column(3).z() <<endl;
//		cout << "transform matrix "<< transform.column(0).w() <<" " <<transform.column(1).w() <<" " <<transform.column(2).w() <<" " <<transform.column(3).w() <<endl;

		BoneTransformData temp = BoneTransformData(jointName, transform);
		keyFrames[i].addBoneTransform(temp);
	}
}

QString AnimationLoader::findRootJointName(){
		QDomNode skeleton = MyXmlNode(m_jointHierarchy.namedItem("visual_scene")).getChildWithAttribute("node", "id", "Armature");
		return skeleton.namedItem("node").attributes().namedItem("id").nodeValue();
}
