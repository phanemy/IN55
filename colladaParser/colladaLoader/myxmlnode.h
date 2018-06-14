#ifndef MYXMLNODE_H
#define MYXMLNODE_H
#include <QTXml>
#include <QString>

class MyXmlNode : public QDomNode
{
public:
    MyXmlNode();
    MyXmlNode(const QDomNode&);
    QString getAttribute(QString attr);
    QDomNode getChildWithAttribute(QString childName, QString attr, QString value);
    QDomNodeList getChildren(QString name);
    ~MyXmlNode();
private:

};

#endif // MYXMLNODE_H
