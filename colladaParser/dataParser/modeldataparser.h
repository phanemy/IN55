#ifndef MODELDATAPARSER_H
#define MODELDATAPARSER_H
#include "object3ddynamic.h"
#include "animatedmodeldata.h"

class ModelDataParser
{
public:
	static Object3DDynamic* loadModel(AnimatedModelData modelData);
private:
	static Bone* createJoints(BoneData data);
};

#endif // MODELDATAPARSER_H
