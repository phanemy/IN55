#include "animationloader.h"


AnimationLoader::AnimationLoader(QDomNode animationData, QDomNode boneHierarchy){
	this->m_animationData = animationData;
	this->m_boneHierarchy = boneHierarchy;
	m_CORRECTION = QMatrix4x4();
	m_CORRECTION.rotate(-90,QVector3D(1,0,0));}
AnimationLoader::~AnimationLoader(){}

AnimationData AnimationLoader::extractAnimation(){
	QString rootNode = findRootBoneName();
	vector<float> times = getKeyTimes();
	float duration = times[times.size()-1];
	vector<KeyFrameData> keyFrames = initKeyFrames(times);
	QDomNodeList animationNodes = MyXmlNode(m_animationData).getChildren("animation");
	for(int i =0 ; i < animationNodes.size(); ++i){
		loadBoneTransforms(keyFrames, animationNodes.item(i), rootNode);
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

void AnimationLoader::loadBoneTransforms(vector<KeyFrameData>& frames, QDomNode boneData, QString rootNodeId){
	QString boneNameId = getBoneName(boneData);
	QString dataId = getDataId(boneData);
	QDomNode transformData = MyXmlNode(boneData).getChildWithAttribute("source", "id", dataId);
	QStringList rawData = transformData.namedItem("float_array").firstChild().nodeValue().split(" ");
	processTransforms(boneNameId, rawData, frames, boneNameId==rootNodeId);
}

QString AnimationLoader::getDataId(QDomNode boneData){
	QDomNode node = MyXmlNode(boneData.namedItem("sampler")).getChildWithAttribute("input", "semantic", "OUTPUT");
	return node.attributes().namedItem("source").nodeValue().mid(1);
}

QString AnimationLoader::getBoneName(QDomNode boneData){
	QDomNode channelNode = boneData.namedItem("channel");
	QString data = channelNode.attributes().namedItem("target").nodeValue();
	return *(data.split("/").begin());
}

void AnimationLoader::processTransforms(QString boneName, QStringList rawData, vector<KeyFrameData>& keyFrames, bool root){
	float matrixData[16];
	for(int i=0;i<keyFrames.size();i++){
		for(int j=0;j<16;j++){
			matrixData[j] = QString(rawData[i*16 + j]).toFloat();
		}
		QMatrix4x4 transform = QMatrix4x4(matrixData);
		if(root){
			transform =  transform * m_CORRECTION;
		}

		BoneTransformData temp = BoneTransformData(boneName, transform);
		keyFrames[i].addBoneTransform(temp);
	}
}

QString AnimationLoader::findRootBoneName(){
		QDomNode skeleton = MyXmlNode(m_boneHierarchy.namedItem("visual_scene")).getChildWithAttribute("node", "id", "Armature");
		return skeleton.namedItem("node").attributes().namedItem("id").nodeValue();
}
