#include "modeldataparser.h"

Object3DDynamic* ModelDataParser::loadModel(AnimatedModelData modelData){
	Bone* rootBone = createBones(modelData.getBonesData().getHeadBone());
	Object3DDynamic* obj = new Object3DDynamic(modelData.getMeshData().getIndices(),modelData.getMeshData().getVertices(),modelData.getMeshData().getNormals(),modelData.getMeshData().getTextureCoords(),modelData.getBonesData().getBoneCount(), rootBone);
    obj->getMesh()->setAnimationData(modelData.getMeshData().getBoneIds(),modelData.getMeshData().getVertexWeights(),modelData.getBonesData().getBoneCount());
	 obj->setTexture(modelData.getTextureData().getTextUrl());
    return obj;
}

Bone* ModelDataParser::createBones(BoneData data){

	Bone* bone = new Bone(data.getIndex(), data.getNameId(), data.getBindLocalTransform());
	for (BoneData child : data.getChildren()) {
		bone->addChild(createBones(child));
	}
	return bone;
}
