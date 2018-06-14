#include "animatedmodeldata.h"


	AnimatedModelData::AnimatedModelData(MeshData mesh, SkeletonData bones, TextureData text):m_bones(bones), m_mesh(mesh),m_texture(text){
//        this->m_bones = bones;
//        this->m_mesh = mesh;
    }
    AnimatedModelData::~AnimatedModelData(){
//		delete m_mesh;
//		delete m_bones;
    }

	SkeletonData AnimatedModelData::getBonesData(){
        return this->m_bones;
    }

	MeshData AnimatedModelData::getMeshData(){
        return this->m_mesh;
    }

	TextureData AnimatedModelData::getTextureData(){
		return this->m_texture;
	}
