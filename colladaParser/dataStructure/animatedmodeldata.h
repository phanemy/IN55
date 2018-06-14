#ifndef ANIMATEDMODELDATA_H
#define ANIMATEDMODELDATA_H
#include "meshdata.h"
#include "skeletondata.h"
#include "texturedata.h"

class AnimatedModelData
{
public:
	AnimatedModelData(MeshData mesh, SkeletonData bones,TextureData text);
    ~AnimatedModelData();
	SkeletonData getBonesData();
	MeshData getMeshData();
	TextureData getTextureData();
private:
	SkeletonData m_bones;
	MeshData m_mesh;
	TextureData m_texture;
};

#endif // ANIMATEDMODELDATA_H
