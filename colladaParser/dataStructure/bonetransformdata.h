#ifndef BONETRANSFORMDATA_H
#define BONETRANSFORMDATA_H
#include <QMatrix4x4>
#include <QString>

using namespace std;

class BoneTransformData
{
public:
    BoneTransformData(QString boneNameId, QMatrix4x4 boneLocalTransform);
	QString getBoneNameId();
    QMatrix4x4 getBoneLocalTransform();
private:
	QString m_boneNameId;
	QMatrix4x4 m_boneLocalTransform;
};

#endif // BONETRANSFORMDATA_H
