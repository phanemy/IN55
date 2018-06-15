#include "animator.h"

Animator::Animator(){
}

Animator::Animator(Bone* bone){
	m_rootBone = bone;
}

void Animator::setupAnimation(Animation* anim){
	m_animationTime = 0;
	m_currentAnimation = anim;
}


//add time to the current animation time and calculate the new pose of bone
void Animator::update(float time){
	if (m_currentAnimation == 0) {
		return;
	}
	increaseAnimationTime(time);
	map<QString, QMatrix4x4> currentPose = calculateCurrentAnimationPose();
	applyPoseToBones(currentPose, m_rootBone, QMatrix4x4());
}


void Animator::increaseAnimationTime(float time){
	m_animationTime += time;
	if (m_animationTime > m_currentAnimation->getLength()) {
		this->m_animationTime = fmod(this->m_animationTime,m_currentAnimation->getLength());
	}
}

//for all bone calculate the new local pose
map<QString, QMatrix4x4> Animator::calculateCurrentAnimationPose(){
	map<QString, QMatrix4x4> poseStorage = map<QString, QMatrix4x4>();
	for(BoneAnimation boneAnim :m_currentAnimation->getBoneAnimation()){
		vector<KeyFrame> frames = getPreviousAndNextFrames(boneAnim);
		float progression = calculateProgression(frames[0], frames[1]);
		poseStorage[boneAnim.getName()] = interpolatePoses(frames[0], frames[1], progression);
	}
	return poseStorage;
}

//for all bone calculate the new pose global pose and apply it
void Animator::applyPoseToBones(map<QString, QMatrix4x4> currentPose, Bone* bone, QMatrix4x4 parentTransform){
	QMatrix4x4 currentLocalTransform = currentPose[bone->getName()];
	QMatrix4x4 currentTransform = parentTransform * currentLocalTransform;
	for (Bone* childBone : bone->getChildren()) {
		applyPoseToBones(currentPose, childBone, currentTransform);
	}
	currentTransform = currentTransform * bone->getInverseBindTransform();
	bone->setAnimationTransform(currentTransform);
}

//get the previous and the next keyfrmae for a doned time
vector<KeyFrame> Animator::getPreviousAndNextFrames(BoneAnimation bonaAnim){
	vector<KeyFrame> allFrames = bonaAnim.getKeyFrame();
	KeyFrame previousFrame = allFrames[0];
	KeyFrame nextFrame = allFrames[0];
	for (int i = 1; i < allFrames.size(); i++) {
		nextFrame = allFrames[i];
		if (nextFrame.getTimeStamp() > m_animationTime) {
			break;
		}
		previousFrame = allFrames[i];
	}

	vector<KeyFrame> temp;
	temp.push_back(previousFrame);
	temp.push_back(nextFrame);
	return temp;
}

float Animator::calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame){
	float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
	float currentTime = m_animationTime - previousFrame.getTimeStamp();
	if(currentTime<0)
		return 0;
	return currentTime / totalTime;
}

QMatrix4x4 Animator::interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression){
	BoneTransform previousTransform = previousFrame.getPose();
	BoneTransform nextTransform = nextFrame.getPose();
	BoneTransform currentTransform = BoneTransform::interpolate(previousTransform, nextTransform, progression);
	return currentTransform.getLocalTransform();
}
