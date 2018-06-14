#include "object3ddynamic.h"

Object3DDynamic::Object3DDynamic(){
	m_rootBone = 0;
	m_nbBone = 0;
	m_texture = 0;
}

Object3DDynamic::Object3DDynamic(vector<int> indices,vector<float> vertices,vector<float> normals,vector<float> textCoord, int nbBone, Bone* rootBone):m_rootBone(rootBone)
{
//    cout<< "Object3DDynamic "<<indices.size()<<" "<<vertices.size()<<" "<<normals.size()<<endl;
	initializeOpenGLFunctions();
	m_animator = Animator(m_rootBone);
	m_parent = 0;
	m_texture = 0;
	m_nbBone = nbBone;
	m_mesh = new MeshDynamic(indices, vertices,normals,textCoord);
	this->m_location = QVector3D(0,0,0);
	this->m_pivot = QVector3D(0,0,0);
	this->m_scale = QVector3D(1,1,1);
	this->m_rotation = QQuaternion();
	m_rootBone->calcInverseBindTransform(QMatrix4x4());
}

Object3DDynamic::~Object3DDynamic()
{
	for(int i = 0; i < m_child.size(); ++i)
	{
		delete m_child[i];
	}
	delete m_mesh;
	delete m_rootBone;
	delete m_texture;
}
void Object3DDynamic::setTexture(QString textUrl){
	if(textUrl!=""){
		QImage temp = QImage(QString(textUrl));
//				cout <<"aaaaaaaaaaaaaaa "<<temp.isNull()<<endl;
		m_texture = new QOpenGLTexture(QImage(QString(textUrl)));}
//	else
//		cout <<"no text"<<endl;
}

void Object3DDynamic::setRotation(QQuaternion rotation){
	this->m_rotation = rotation;
}

QQuaternion Object3DDynamic::getRotation(){
	return this->m_rotation;
}

void Object3DDynamic::setLocation(QVector3D location){
	this->m_location = location;
}

QVector3D Object3DDynamic::getLocation(){
	return this->m_location;
}

void Object3DDynamic::setScale(QVector3D scale){
	this->m_scale = scale;
}
QVector3D Object3DDynamic::getScale(){
	return this->m_scale;
}

void Object3DDynamic::setPivot(QVector3D pivot){
this->m_pivot = pivot;
}

QVector3D Object3DDynamic::getPivot(){
	return this->m_pivot;
}

void Object3DDynamic::setParent(Object3DDynamic* parent){
	m_parent = parent;
}

QMatrix4x4 Object3DDynamic::getTransform(){
	return this->m_transform;
}
void Object3DDynamic::setTransform(QMatrix4x4 transform){
	this->m_transform = m_transform;
}

MeshDynamic* Object3DDynamic::getMesh(){
	return m_mesh;
}

void Object3DDynamic::drawGeometry(QOpenGLShaderProgram *program,QMatrix4x4 projection)
{
//	m_rotation = QQuaternion::fromAxisAndAngle(1,1,0,1.0f)*m_rotation;

	if(m_parent != 0)
	{
		m_transform = m_parent->getTransform();
	}
	else
	{
		m_transform.setToIdentity();
	}

	m_transform.translate(m_pivot);
	m_transform.rotate(m_rotation);
	m_transform.translate(-m_pivot);
	m_transform.translate(m_location);

	m_transform.scale(m_scale);
	program->setUniformValue("mvp", projection * m_transform);
	vector<QMatrix4x4> temp1 = getBoneTransforms();

//	cout << "m_nbBone" <<endl;
//	for(QMatrix4x4 mat : temp1)
//	{
//		cout << "mat  "<< mat.column(0).x() << " " <<mat.column(1).x() << " " <<mat.column(2).x()<< " " <<mat.column(3).x()  <<endl;
//		cout << "mat  "<< mat.column(0).y() << " " <<mat.column(1).y() << " " <<mat.column(2).y()<< " " <<mat.column(3).y()  <<endl;
//		cout << "mat  "<< mat.column(0).z() << " " <<mat.column(1).z() << " " <<mat.column(2).z()<< " " <<mat.column(3).z()  <<endl;
//		cout << "mat  "<< mat.column(0).w() << " " <<mat.column(1).w() << " " <<mat.column(2).w()<< " " <<mat.column(3).w()  <<endl;
//		cout << " "<<endl;
//	}

	QMatrix4x4* temp = temp1.data();
	program->setUniformValueArray("jointTransforms", temp,m_nbBone);

//	cout << "ccccccccccccccccccc "<< m_rootBone->getId()<<endl;
//	VertexData* tempData = m_mesh->getVertexData();
//	QVector<QVector3D> temmJointID = m_mesh->getJointID();
//	QVector<QVector3D> tempWeigth =m_mesh->getWeigth();
//	for(int i =28; i <31;++i)
//	{
//		QVector4D pos = QVector4D(tempData[i].position,1);
//		cout<<"pos    "<<pos.x()<<" "<<pos.y()<<" "<<pos.z()<<" "<<pos.w()<<" id "<<(int)temmJointID[i].x()<<endl;
////		cout<<"jointid "<<(int)tempData[i].joinIds.x()<<endl;
////		cout<<"matrix id "<<(int)tempData[i].joinIds.x()<<" "<<(int)tempData[i].joinIds.y()<<" "<<(int)tempData[i].joinIds.z()<<endl;
//		QMatrix4x4 mat = temp[(int)temmJointID[i].x()];
//		cout << "draw matrix "<< mat.column(0).x() << " " <<mat.column(1).x() << " " <<mat.column(2).x()<< " " <<mat.column(3).x()  <<endl;
//		cout << "draw matrix "<< mat.column(0).y() << " " <<mat.column(1).y() << " " <<mat.column(2).y()<< " " <<mat.column(3).y()  <<endl;
//		cout << "draw matrix "<< mat.column(0).z() << " " <<mat.column(1).z() << " " <<mat.column(2).z()<< " " <<mat.column(3).z()  <<endl;
//		cout << "draw matrix "<< mat.column(0).w() << " " <<mat.column(1).w() << " " <<mat.column(2).w()<< " " <<mat.column(3).w()  <<endl;
//		QVector4D pospos = (mat * pos) *tempWeigth[i].x();
////        cout<<"pospos "<<pospos.x()<<" "<<pospos.y()<<" "<<pospos.z()<<" "<<pospos.w()<<endl;
////		cout<<"jointid "<<(int)tempData[i].joinIds.y()<<endl;
//		mat = temp[(int)temmJointID[i].y()];
////		cout << "addBonesToArray matrix2 "<< mat.column(0).x() << " " <<mat.column(1).x() << " " <<mat.column(2).x()<< " " <<mat.column(3).x()  <<endl;
////		cout << "addBonesToArray matrix2 "<< mat.column(0).y() << " " <<mat.column(1).y() << " " <<mat.column(2).y()<< " " <<mat.column(3).y()  <<endl;
////		cout << "addBonesToArray matrix2 "<< mat.column(0).z() << " " <<mat.column(1).z() << " " <<mat.column(2).z()<< " " <<mat.column(3).z()  <<endl;
////		cout << "addBonesToArray matrix2 "<< mat.column(0).w() << " " <<mat.column(1).w() << " " <<mat.column(2).w()<< " " <<mat.column(3).w()  <<endl;
//		pospos += (mat * pos) * tempWeigth[i].y();
////		cout<<"pospos "<<pospos.x()<<" "<<pospos.y()<<" "<<pospos.z()<<" "<<pospos.w()<<" id "<<(int)tempData[i].joinIds.z()<<endl;
////		cout<<"jointid "<<(int)tempData[i].joinIds.z()<<endl;
//		mat = temp[(int)temmJointID[i].z()];
////		cout << "addBonesToArray matrix3 "<< mat.column(0).x() << " " <<mat.column(1).x() << " " <<mat.column(2).x()<< " " <<mat.column(3).x()  <<endl;
////		cout << "addBonesToArray matrix3 "<< mat.column(0).y() << " " <<mat.column(1).y() << " " <<mat.column(2).y()<< " " <<mat.column(3).y()  <<endl;
////		cout << "addBonesToArray matrix3 "<< mat.column(0).z() << " " <<mat.column(1).z() << " " <<mat.column(2).z()<< " " <<mat.column(3).z()  <<endl;
////		cout << "addBonesToArray matrix3 "<< mat.column(0).w() << " " <<mat.column(1).w() << " " <<mat.column(2).w()<< " " <<mat.column(3).w()  <<endl;
//		pospos += (mat * pos) * tempWeigth[i].z();
//		pospos = pospos;
//		cout<<"pospos "<<pospos.x()<<" "<<pospos.y()<<" "<<pospos.z()<<" "<<pospos.w()<<"\n"<<endl;
//	}
//	cout <<"next "<<"\n"<<endl;

	if(m_texture !=0){
//		cout<<"have text"<<endl;
		m_texture->bind();
	}
//	cout<<"have fail"<<endl;
	m_mesh->drawGeometry(program);
//	m_rootBone->calculateGeometry();
//	cout <<""<<endl;

}

void Object3DDynamic::drawGeometry(QOpenGLShaderProgram *program,QMatrix4x4 projection, QQuaternion rotation)
{
	m_rotation = QQuaternion::fromAxisAndAngle(1,1,0,1.0f)*m_rotation;
	if(m_parent != 0)
	{
		m_transform = m_parent->getTransform();
	}
	else
	{
		m_transform.setToIdentity();
	}

	m_transform.translate(m_pivot);
	m_transform.rotate(rotation);
	m_transform.translate(-m_pivot);
	m_transform.translate(m_location);

	m_transform.scale(m_scale);
	program->setUniformValue("mvp", projection * m_transform);
//	program->setUniformValueArray("in_jointIndices", temp,m_nbBone);
	m_mesh->drawGeometry(program);
}

Bone* Object3DDynamic::getRootBone(){
//	cout << "export " << m_rootBone<<endl;
	return m_rootBone;
}

void Object3DDynamic::setAnimationList(Animation anim){
	this->m_animation = anim;
	this->m_animator.setupAnimation(&this->m_animation);
}

void Object3DDynamic::computeAnimation(float time){
	m_animator.update(time);
}

vector<QMatrix4x4> Object3DDynamic::getBoneTransforms(){
	vector<QMatrix4x4> listMatrix(m_nbBone);
	addBonesToArray(m_rootBone, listMatrix);
	return listMatrix;
}

void Object3DDynamic::addBonesToArray(Bone* headJoint, vector<QMatrix4x4>& boneMatrix)
{
//	cout << "addBonesToArray "<< headJoint->getId() << " " << headJoint->getName().toStdString()<<endl;
	QMatrix4x4 temp =headJoint->getAnimatedTransform();
	boneMatrix[headJoint->getId()] = temp;
//	cout << "addBonesToArray matrix "<< boneMatrix[headJoint->getId()].column(0).x() << " " <<boneMatrix[headJoint->getId()].column(1).x() << " " <<boneMatrix[headJoint->getId()].column(2).x()<< " " <<boneMatrix[headJoint->getId()].column(3).x()  <<endl;
//	cout << "addBonesToArray matrix "<< boneMatrix[headJoint->getId()].column(0).y() << " " <<boneMatrix[headJoint->getId()].column(1).y() << " " <<boneMatrix[headJoint->getId()].column(2).y()<< " " <<boneMatrix[headJoint->getId()].column(3).y()  <<endl;
//	cout << "addBonesToArray matrix "<< boneMatrix[headJoint->getId()].column(0).z() << " " <<boneMatrix[headJoint->getId()].column(1).z() << " " <<boneMatrix[headJoint->getId()].column(2).z()<< " " <<boneMatrix[headJoint->getId()].column(3).z()  <<endl;
//	cout << "addBonesToArray matrix "<< boneMatrix[headJoint->getId()].column(0).w() << " " <<boneMatrix[headJoint->getId()].column(1).w() << " " <<boneMatrix[headJoint->getId()].column(2).w()<< " " <<boneMatrix[headJoint->getId()].column(3).w()  <<endl;
//	cout<<" "<<endl;
	for (Bone* childJoint : headJoint->getChildren()) {
		addBonesToArray(childJoint, boneMatrix);
	}
}
