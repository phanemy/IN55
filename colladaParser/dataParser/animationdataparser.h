#ifndef ANIMATIONDATAPARSER_H
#define ANIMATIONDATAPARSER_H
#include "animationdata.h"
#include "animation.h"
#include "colladaloader.h"
#include <map>
#include <QVector3D>
#include <math.h>

using namespace std;

class AnimationDataParser
{
public:
	static Animation loadAnimation(AnimationData animData);
private:
//	KeyFrame createKeyFrame(KeyFrameData data);
	static BoneTransform createTransform(QMatrix4x4 mat);
	static QQuaternion fromMatrix(QMatrix4x4 matrix);
};



#endif // ANIMATIONDATAPARSER_H
