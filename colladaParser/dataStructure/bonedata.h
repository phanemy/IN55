#ifndef BONEDATA_H
#define BONEDATA_H
#include <QString>
#include <QMatrix4x4>
#include <list>
#include <iostream>

using namespace std;

class BoneData
{
public:
    BoneData(int index, QString nameId, QMatrix4x4 bindLocalTransform);
    void addChild(BoneData child);
    int getIndex();
    QString getNameId();
    QMatrix4x4 getBindLocalTransform();
    list<BoneData> getChildren();

private:
    const int m_index;
    const QString m_nameId;
    const QMatrix4x4 m_bindLocalTransform;
    list<BoneData> m_children;
};

#endif // BONEDATA_H
