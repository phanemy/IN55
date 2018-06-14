#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <map>
#include "bone.h"
#include "animation.h"

class Animator
{
public:
	Animator();
	Animator(Bone* bone);
	void setupAnimation(Animation* anim);
	void update(float time);
	void increaseAnimationTime(float time);
	map<QString, QMatrix4x4> calculateCurrentAnimationPose();
	void applyPoseToJoints(map<QString, QMatrix4x4> currentPose, Bone* joint, QMatrix4x4 parentTransform);
	vector<KeyFrame> getPreviousAndNextFrames(BoneAnimation boneAnim);
	float calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame);
	QMatrix4x4 interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression);
private:
	Animation* m_currentAnimation = 0;
	Bone* m_rootBone = 0;
	float m_animationTime;
};

#endif // ANIMATOR_H
