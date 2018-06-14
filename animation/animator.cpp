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

void Animator::update(float time){
	if (m_currentAnimation == 0) {
//		cout << "Animator: No anim"<<endl;
		return;
	}
//	cout << "bbbbbbb"<<endl;
	increaseAnimationTime(time);
//	cout << "ccccccc"<<endl;
	map<QString, QMatrix4x4> currentPose = calculateCurrentAnimationPose();
//	cout << "ddddddd"<<endl;
	applyPoseToJoints(currentPose, m_rootBone, QMatrix4x4());
//	cout << "eeeeeee"<<endl;
}

void Animator::increaseAnimationTime(float time){
	m_animationTime += time;
	if (m_animationTime > m_currentAnimation->getLength()) {
		this->m_animationTime = fmod(this->m_animationTime,m_currentAnimation->getLength());
	}
}

map<QString, QMatrix4x4> Animator::calculateCurrentAnimationPose(){
	map<QString, QMatrix4x4> poseStorage = map<QString, QMatrix4x4>();
	for(BoneAnimation boneAnim :m_currentAnimation->getBoneAnimation()){
		vector<KeyFrame> frames = getPreviousAndNextFrames(boneAnim);
		float progression = calculateProgression(frames[0], frames[1]);
//        cout<<" progression "<< frames[0].getTimeStamp()<< " " << frames[1].getTimeStamp()<<" "<<progression <<endl;
		poseStorage[boneAnim.getName()] = interpolatePoses(frames[0], frames[1], progression);
	}
//	cout <<""<<endl;
	return poseStorage;
}

void Animator::applyPoseToJoints(map<QString, QMatrix4x4> currentPose, Bone* joint, QMatrix4x4 parentTransform){
//	cout << "d_0000000 "<<joint->getName().toStdString()<<endl;
	QMatrix4x4 currentLocalTransform = currentPose[joint->getName()];
//	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).x() << " " <<currentLocalTransform.column(1).x() << " " <<currentLocalTransform.column(2).x() << " " <<currentLocalTransform.column(3).x() <<endl;
//	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).y() << " " <<currentLocalTransform.column(1).y() << " " <<currentLocalTransform.column(2).y() << " " <<currentLocalTransform.column(3).x() <<endl;
//	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).z() << " " <<currentLocalTransform.column(1).z() << " " <<currentLocalTransform.column(2).z() << " " <<currentLocalTransform.column(3).x() <<endl;
//	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).w() << " " <<currentLocalTransform.column(1).w() << " " <<currentLocalTransform.column(2).w() << " " <<currentLocalTransform.column(3).x() <<endl;
//		cout << " "<<endl;

//	cout << "Animator applyPoseToJoints parentTransform "<< parentTransform.column(0).x() << " " <<parentTransform.column(1).x() << " " <<parentTransform.column(2).x() << " " <<parentTransform.column(3).x() <<endl;
//	cout << "Animator applyPoseToJoints parentTransform "<< parentTransform.column(0).y() << " " <<parentTransform.column(1).y() << " " <<parentTransform.column(2).y() << " " <<parentTransform.column(3).y() <<endl;
//	cout << "Animator applyPoseToJoints parentTransform "<< parentTransform.column(0).z() << " " <<parentTransform.column(1).z() << " " <<parentTransform.column(2).z() << " " <<parentTransform.column(3).z() <<endl;
//	cout << "Animator applyPoseToJoints parentTransform "<< parentTransform.column(0).w() << " " <<parentTransform.column(1).w() << " " <<parentTransform.column(2).w() << " " <<parentTransform.column(3).w() <<endl;
//		cout << " "<<endl;

//	cout << "d_aaaaaaaaaaaa"<<endl;
	QMatrix4x4 currentTransform = parentTransform * currentLocalTransform;
//	cout << "d_bbbbbbbbbbb"<<endl;
	for (Bone* childJoint : joint->getChildren()) {
        applyPoseToJoints(currentPose, childJoint, currentTransform);
	}
//	cout << "dcccccccccccccc"<<endl;
	currentTransform = currentTransform * joint->getInverseBindTransform();
//	cout << "d_ddddddddddd"<<endl;
	joint->setAnimationTransform(currentTransform);
	cout<<joint->getName().toStdString()<<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).x() << " " <<currentLocalTransform.column(1).x() << " " <<currentLocalTransform.column(2).x()<< " " <<currentLocalTransform.column(3).x() <<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).y() << " " <<currentLocalTransform.column(1).y() << " " <<currentLocalTransform.column(2).y()<< " " <<currentLocalTransform.column(3).y() <<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).z() << " " <<currentLocalTransform.column(1).z() << " " <<currentLocalTransform.column(2).z()<< " " <<currentLocalTransform.column(3).z() <<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentLocalTransform.column(0).w() << " " <<currentLocalTransform.column(1).w() << " " <<currentLocalTransform.column(2).w()<< " " <<currentLocalTransform.column(3).w() <<endl;
	cout << " "<<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentTransform.column(0).x() << " " <<currentTransform.column(1).x() << " " <<currentTransform.column(2).x()<< " " <<currentTransform.column(3).x() <<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentTransform.column(0).y() << " " <<currentTransform.column(1).y() << " " <<currentTransform.column(2).y()<< " " <<currentTransform.column(3).y() <<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentTransform.column(0).z() << " " <<currentTransform.column(1).z() << " " <<currentTransform.column(2).z()<< " " <<currentTransform.column(3).z() <<endl;
	cout << "Animator applyPoseToJoints matrix "<< currentTransform.column(0).w() << " " <<currentTransform.column(1).w() << " " <<currentTransform.column(2).w()<< " " <<currentTransform.column(3).w() <<endl;
		cout << "d_eeeeeeeeee"<<endl;
}


//todo here
vector<KeyFrame> Animator::getPreviousAndNextFrames(BoneAnimation bonaAnim){
	vector<KeyFrame> allFrames = bonaAnim.getKeyFrame();
	KeyFrame previousFrame = allFrames[0];
	KeyFrame nextFrame = allFrames[0];
	for (int i = 1; i < allFrames.size(); i++) {
		nextFrame = allFrames[i];
		if (nextFrame.getTimeStamp() > m_animationTime) {
//			cout << "fail"<<endl;
			break;
		}
		previousFrame = allFrames[i];
//		cout <<"next " <<nextFrame.getTimeStamp() <<endl;
	}
//		cout << "Animator getPreviousAndNextFrames previousFrame "<< previousFrame..column(0).x() << " " <<previousFrame.column(1).x() << " " <<previousFrame.column(2).x()<< " " <<previousFrame.column(3).x() <<endl;
//		cout << "Animator getPreviousAndNextFrames previousFrame "<< previousFrame.column(0).y() << " " <<previousFrame.column(1).y() << " " <<previousFrame.column(2).y()<< " " <<previousFrame.column(3).x() <<endl;
//		cout << "Animator getPreviousAndNextFrames previousFrame "<< previousFrame.column(0).z() << " " <<previousFrame.column(1).z() << " " <<previousFrame.column(2).z()<< " " <<previousFrame.column(3).x() <<endl;
//		cout << "Animator getPreviousAndNextFrames previousFrame "<< previousFrame.column(0).w() << " " <<previousFrame.column(1).w() << " " <<previousFrame.column(2).w()<< " " <<previousFrame.column(3).x() <<endl;

//		cout << "Animator getPreviousAndNextFrames nextFrame "<< nextFrame.column(0).x() << " " <<nextFrame.column(1).x() << " " <<nextFrame.column(2).x()<< " " <<nextFrame.column(3).x() <<endl;
//		cout << "Animator getPreviousAndNextFrames nextFrame "<< nextFrame.column(0).y() << " " <<nextFrame.column(1).y() << " " <<nextFrame.column(2).y()<< " " <<nextFrame.column(3).x() <<endl;
//		cout << "Animator getPreviousAndNextFrames nextFrame "<< nextFrame.column(0).z() << " " <<nextFrame.column(1).z() << " " <<nextFrame.column(2).z()<< " " <<nextFrame.column(3).x() <<endl;
//		cout << "Animator getPreviousAndNextFrames nextFrame "<< nextFrame.column(0).w() << " " <<nextFrame.column(1).w() << " " <<nextFrame.column(2).w()<< " " <<nextFrame.column(3).x() <<endl;

//		cout <<"prev next " <<previousFrame.getTimeStamp() << " "<<nextFrame.getTimeStamp()<< " "<<allFrames.size() <<endl;
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
