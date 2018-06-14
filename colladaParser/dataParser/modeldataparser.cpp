#include "modeldataparser.h"

Object3DDynamic* ModelDataParser::loadModel(AnimatedModelData modelData){
	cout << "ModelDataParser create Joint start"<<endl;
	Bone* rootBone = createJoints(modelData.getBonesData().getHeadBone());
//	cout << "ModelDataParser create Object3D "<< modelData.getMeshData().getTextureCoords().size()<<endl;
//	for(int i = 0;  i < modelData.getMeshData().getTextureCoords().size()/2;++i)
//	{
//		cout << modelData.getMeshData().getTextureCoords()[i*2] <<" "<<modelData.getMeshData().getTextureCoords()[i*2+1]<<endl;
//	}
	Object3DDynamic* obj = new Object3DDynamic(modelData.getMeshData().getIndices(),modelData.getMeshData().getVertices(),modelData.getMeshData().getNormals(),modelData.getMeshData().getTextureCoords(),modelData.getBonesData().getBoneCount(), rootBone);
	cout << "ModelDataParser add AnimData"<<endl;
    obj->getMesh()->setAnimationData(modelData.getMeshData().getBoneIds(),modelData.getMeshData().getVertexWeights(),modelData.getBonesData().getBoneCount());
	 cout << "ModelDataParser texture"<<endl;
	 obj->setTexture(modelData.getTextureData().getTextUrl());
	 cout << "ModelDataParser texture"<<endl;
    return obj;
}

Bone* ModelDataParser::createJoints(BoneData data){

	Bone* joint = new Bone(data.getIndex(), data.getNameId(), data.getBindLocalTransform());
	for (BoneData child : data.getChildren()) {
		joint->addChild(createJoints(child));
	}
	return joint;
}
