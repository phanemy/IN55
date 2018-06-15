#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include "boneanimation.h"

//animation classe

using namespace std;

class Animation
{
public:
	Animation();
	Animation(float length, vector<BoneAnimation> boneAnim);
	float getLength();
	vector<BoneAnimation> getBoneAnimation();
private:
	float m_length;
	vector<BoneAnimation> m_boneAnim;
};

#endif // ANIMATION_H
