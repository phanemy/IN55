#include "animationdataparser.h"

Animation AnimationDataParser::loadAnimation(AnimationData animData){
	vector<BoneAnimation> boneAnim;
	vector<QString> order;
	map<QString,BoneAnimation> listBoneTransform;
	map<QString,BoneAnimation>::iterator it;
    cout <<"\nAnim "<<animData.getKeyFrameData().size()<<endl;
	for (KeyFrameData data : animData.getKeyFrameData()) {
        cout <<"\ndata "<<data.getBoneTransforms().size()<< " " << data.getTime()<<endl;
		for (BoneTransformData boneData : data.getBoneTransforms()) {
            cout <<"boneData "<<boneData.getBoneNameId().toStdString()<< " "<<endl;
			cout << "AnimationDataParser before matrix "<< boneData.getBoneLocalTransform().column(0).x()<<" " <<boneData.getBoneLocalTransform().column(1).x()<<" "<<boneData.getBoneLocalTransform().column(2).x()<<" "<<boneData.getBoneLocalTransform().column(3).x() <<endl;
			cout << "AnimationDataParser before matrix "<< boneData.getBoneLocalTransform().column(0).y()<<" " <<boneData.getBoneLocalTransform().column(1).y()<<" "<<boneData.getBoneLocalTransform().column(2).y()<<" "<<boneData.getBoneLocalTransform().column(3).y() <<endl;
			cout << "AnimationDataParser before matrix "<< boneData.getBoneLocalTransform().column(0).z()<<" " <<boneData.getBoneLocalTransform().column(1).z()<<" "<<boneData.getBoneLocalTransform().column(2).z()<<" "<<boneData.getBoneLocalTransform().column(3).z() <<endl;
			cout << "AnimationDataParser before matrix "<< boneData.getBoneLocalTransform().column(0).w()<<" " <<boneData.getBoneLocalTransform().column(1).w()<<" "<<boneData.getBoneLocalTransform().column(2).w()<<" "<<boneData.getBoneLocalTransform().column(3).w() <<endl;
			cout << " "<<endl;
			BoneTransform tempTransform = createTransform(boneData.getBoneLocalTransform());
//			QMatrix4x4 temp = tempTransform.getLocalTransform();
//			cout <<"boneData "<<boneData.getBoneNameId().toStdString()<< " "<<endl;

			QMatrix4x4 temp = tempTransform.getLocalTransform();

			cout << "AnimationDataParser loadAnimation matrix "<< temp.column(0).x() <<" " <<temp.column(1).x() <<" " <<temp.column(2).x() <<" " <<temp.column(3).x() <<endl;
			cout << "AnimationDataParser loadAnimation matrix "<< temp.column(0).y() <<" " <<temp.column(1).y() <<" " <<temp.column(2).y() <<" " <<temp.column(3).y() <<endl;
			cout << "AnimationDataParser loadAnimation matrix "<< temp.column(0).z() <<" " <<temp.column(1).z() <<" " <<temp.column(2).z() <<" " <<temp.column(3).z() <<endl;
			cout << "AnimationDataParser loadAnimation matrix "<< temp.column(0).w() <<" " <<temp.column(1).w() <<" " <<temp.column(2).w() <<" " <<temp.column(3).w() <<endl;

//			cout << "loadAnimation matrix "<< tempTransform.m_position.x() <<" " <<tempTransform.m_position.y() <<" " <<tempTransform.m_position.z()<<endl;
			cout << " "<<endl;
			KeyFrame frame = KeyFrame(data.getTime(), tempTransform);
			it = listBoneTransform.find(boneData.getBoneNameId());

			if(it!=listBoneTransform.end())
			{
				listBoneTransform[boneData.getBoneNameId()].getKeyFrame().push_back(frame);
//				cout<< "aa "<<listBoneTransform[boneData.getBoneNameId()].getKeyFrame().size()<<endl;
			}
			else
			{
				listBoneTransform[boneData.getBoneNameId()] = BoneAnimation(boneData.getBoneNameId(),frame);
				order.push_back(boneData.getBoneNameId());
//				cout<<boneData.getBoneNameId().toStdString()<<endl;

			}
		}
	}
//	it = listBoneTransform.begin();
//	// Iterate over the map using Iterator till end.
//	while (it != listBoneTransform.end())
//	{
//		// Accessing KEY from element pointed by it.
//		cout <<it->first.toStdString()<<endl;
//		boneAnim.push_back(it->second);

//		// Increment the Iterator to point to next entry
//		it++;
//	}
	for(QString name : order)
	{
		boneAnim.push_back(listBoneTransform[name]);
//		cout << "bone order "<< name.toStdString()<<endl;
	}
	cout <<"end AnimationDataParser \n\n"<<endl;
	return Animation(animData.getLengthSeconds(), boneAnim);
}

BoneTransform AnimationDataParser::createTransform(QMatrix4x4 mat){
//mat = mat.transposed();
	QVector3D  translation = QVector3D(mat.column(3).x(), mat.column(3).y(), mat.column(3).z());
//possible error here
//	QQuaternion rotation = QQuaternion::fromAxes(QVector3D(mat.column(1).x(),mat.column(1).y(),mat.column(1).z()),QVector3D(mat.column(2).x(),mat.column(2).y(),mat.column(2).z()),QVector3D(mat.column(3).x(),mat.column(3).y(),mat.column(3).z()));
	QQuaternion rotation = fromMatrix(mat);
	cout << "translation " << translation.x() <<" "<<translation.y() <<" "<< translation.z()<<endl;
    float *x = (float*)malloc(sizeof(float));
    float *y = (float*)malloc(sizeof(float));
    float *z = (float*)malloc(sizeof(float));
    rotation.getEulerAngles(x,y,z);
	cout << "\tangle " << rotation.scalar() <<" "<<rotation.x() <<" "<< rotation.y()<<" "<<rotation.z()<<endl;
	return BoneTransform(translation, rotation);
}

QQuaternion AnimationDataParser::fromMatrix(QMatrix4x4 matrix) {
//    float w, x, y, z;
//    float diagonal = matrix.column(0).x() + matrix.column(1).y() + matrix.column(2).z();
//    if (diagonal > 0) {
//        float w4 = sqrt(diagonal + 1) * 2;
//        w = w4 / 4;
//        x = (matrix.column(2).y() - matrix.column(1).z()) / w4;
//        y = (matrix.column(0).z() - matrix.column(2).x()) / w4;
//        z = (matrix.column(1).x() - matrix.column(0).y()) / w4;
//    } else if ((matrix.column(0).x() > matrix.column(1).y()) && (matrix.column(0).x() > matrix.column(2).z())) {
//        float x4 = sqrt(1 + matrix.column(0).x() - matrix.column(1).y() - matrix.column(2).z()) * 2;
//        w = (matrix.column(2).y() - matrix.column(1).z()) / x4;
//        x = x4 / 4;
//        y = (matrix.column(0).y() + matrix.column(1).x()) / x4;
//        z = (matrix.column(0).z() + matrix.column(2).x()) / x4;
//    } else if (matrix.column(1).y() > matrix.column(2).z()) {
//        float y4 = sqrt(1 + matrix.column(1).y() - matrix.column(0).x() - matrix.column(2).z()) * 2;
//        w = (matrix.column(0).z() - matrix.column(2).x()) / y4;
//        x = (matrix.column(0).y() + matrix.column(1).x()) / y4;
//        y = y4 / 4;
//        z = (matrix.column(1).z() + matrix.column(2).y()) / y4;
//    } else {
//        float z4 = sqrt(1 + matrix.column(2).z() - matrix.column(0).x() - matrix.column(1).y()) * 2;
//        w = (matrix.column(1).x() - matrix.column(0).y()) / z4;
//        x = (matrix.column(0).z() + matrix.column(2).x()) / z4;
//        y = (matrix.column(1).z() + matrix.column(2).y()) / z4;
//        z = z4 / 4;
//    }
//    return QQuaternion(w, x, y, z);

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
