#include "myxmlnode.h"
#include <iostream>

MyXmlNode::MyXmlNode() : QDomNode(){}

MyXmlNode::MyXmlNode(const QDomNode& node):QDomNode(node){}

QString MyXmlNode::getAttribute(QString attr){
    if (this->hasAttributes()) {
        QDomNamedNodeMap temp = QDomNode::attributes();
        if(temp.contains(attr))
        {
            return temp.namedItem(attr).toAttr().value();
        }else {
            return 0;
        }
    } else {
        return 0;
    }
}

QDomNode MyXmlNode::getChildWithAttribute(QString childName, QString attr, QString value){
    QDomNodeList childrenList = getChildren(childName);

    if(childrenList.isEmpty())
        return QDomNode();
    for(int i = 0; i<childrenList.length(); ++i)
    {
        QDomNode node = childrenList.item(i);
        QString val = node.attributes().namedItem(attr).toAttr().value();
        if(val == value)
            return node;
    }
    return QDomNode();
}

QDomNodeList MyXmlNode::getChildren(QString name){
    if(this->hasChildNodes())
    {
        QDomNodeList child = QDomNode::childNodes();
        QDomDocument  result("temparyDoc");
        QDomNode tempNode;
        int idx = 0;
        do
        {
            tempNode = child.item(idx);
            if(tempNode.toElement().tagName() == name)
            {
                result.appendChild(tempNode.cloneNode());
            }
            idx ++;
        }while(idx < child.length());
        if(result.hasChildNodes())
            return result.childNodes();
    }
    return QDomNodeList();
}

MyXmlNode::~MyXmlNode(){
}
