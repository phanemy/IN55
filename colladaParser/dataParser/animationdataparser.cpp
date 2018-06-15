#include "animationdataparser.h"

Animation AnimationDataParser::loadAnimation(AnimationData animData){
	vector<BoneAnimation> boneAnim;
	vector<QString> order;
	map<QString,BoneAnimation> listBoneTransform;
	map<QString,BoneAnimation>::iterator it;
	for (KeyFrameData data : animData.getKeyFrameData()) {
		for (BoneTransformData boneData : data.getBoneTransforms()) {
			BoneTransform tempTransform = createTransform(boneData.getBoneLocalTransform());
			QMatrix4x4 temp = tempTransform.getLocalTransform();
			KeyFrame frame = KeyFrame(data.getTime(), tempTransform);
			it = listBoneTransform.find(boneData.getBoneNameId());

			if(it!=listBoneTransform.end())
			{
				listBoneTransform[boneData.getBoneNameId()].getKeyFrame().push_back(frame);
			}
			else
			{
				listBoneTransform[boneData.getBoneNameId()] = BoneAnimation(boneData.getBoneNameId(),frame);
				order.push_back(boneData.getBoneNameId());
			}
		}
	}

	for(QString name : order)
	{
		boneAnim.push_back(listBoneTransform[name]);
	}
	return Animation(animData.getLengthSeconds(), boneAnim);
}

BoneTransform AnimationDataParser::createTransform(QMatrix4x4 mat){
//mat = mat.transposed();
	QVector3D  translation = QVector3D(mat.column(3).x(), mat.column(3).y(), mat.column(3).z());
	QQuaternion rotation = fromMatrix(mat);
	return BoneTransform(translation, rotation);
}

QQuaternion AnimationDataParser::fromMatrix(QMatrix4x4 matrix) {
	float w, x, y, z;
	float diagonal = matrix.column(0).x() + matrix.column(1).y() + matrix.column(2).z();
	if (diagonal > 0) {
		float w4 = sqrt(diagonal + 1) * 2;
		w = w4 / 4;
		x = (matrix.row(2).y() - matrix.row(1).z()) / w4;
		y = (matrix.row(0).z() - matrix.row(2).x()) / w4;
		z = (matrix.row(1).x() - matrix.row(0).y()) / w4;
	} else if ((matrix.row(0).x() > matrix.row(1).y()) && (matrix.row(0).x() > matrix.row(2).z())) {
		float x4 = sqrt(1 + matrix.row(0).x() - matrix.row(1).y() - matrix.row(2).z()) * 2;
		w = (matrix.row(2).y() - matrix.row(1).z()) / x4;
		x = x4 / 4;
		y = (matrix.row(0).y() + matrix.row(1).x()) / x4;
		z = (matrix.row(0).z() + matrix.row(2).x()) / x4;
	} else if (matrix.row(1).y() > matrix.row(2).z()) {
		float y4 = sqrt(1 + matrix.row(1).y() - matrix.row(0).x() - matrix.row(2).z()) * 2;
		w = (matrix.row(0).z() - matrix.row(2).x()) / y4;
		x = (matrix.row(0).y() + matrix.row(1).x()) / y4;
		y = y4 / 4;
		z = (matrix.row(1).z() + matrix.row(2).y()) / y4;
	} else {
	   float z4 = sqrt(1 + matrix.row(2).z() - matrix.row(0).x() - matrix.row(1).y()) * 2;
	   w = (matrix.row(1).x() - matrix.row(0).y()) / z4;
	   x = (matrix.row(0).z() + matrix.row(2).x()) / z4;
	   y = (matrix.row(1).z() + matrix.row(2).y()) / z4;
	   z = z4 / 4;
	}
	return QQuaternion(w, x, y, z);
}
