#include "animation.h"

Animation::Animation(){

}

Animation::Animation(float length, vector<BoneAnimation> boneAnim):m_boneAnim(boneAnim){
	m_length = length;
}

float Animation::getLength(){
	return m_length;
}

vector<BoneAnimation> Animation::getBoneAnimation(){
	return m_boneAnim;
}
