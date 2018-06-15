#include "object3ddynamic.h"

Object3DDynamic::Object3DDynamic(){
	m_rootBone = 0;
	m_nbBone = 0;
	m_texture = 0;
}

Object3DDynamic::Object3DDynamic(vector<int> indices,vector<float> vertices,vector<float> normals,vector<float> textCoord, int nbBone, Bone* rootBone):m_rootBone(rootBone)
{
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
		m_texture = new QOpenGLTexture(QImage(QString(textUrl)));}
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

	QMatrix4x4* temp = temp1.data();
	program->setUniformValueArray("bonesTransforms", temp,m_nbBone);

	if(m_texture !=0){
		m_texture->bind();
	}
	m_mesh->drawGeometry(program);
}

Bone* Object3DDynamic::getRootBone(){
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

void Object3DDynamic::addBonesToArray(Bone* headBone, vector<QMatrix4x4>& boneMatrix)
{
	QMatrix4x4 temp =headBone->getAnimatedTransform();
	boneMatrix[headBone->getId()] = temp;
	for (Bone* childBone : headBone->getChildren()) {
		addBonesToArray(childBone, boneMatrix);
	}
}
