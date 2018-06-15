#include "geometryloader.h"
#include <iostream>

GeometryLoader::GeometryLoader(QDomNode geometryNode, QList<VertexSkinData> vertexWeights):m_vertices(),m_textures(),m_normals(),m_indices(){
    this->m_vertexWeights = vertexWeights;
	this->m_meshData = geometryNode.namedItem("geometry").namedItem("mesh");
	m_CORRECTION = QMatrix4x4();
	m_CORRECTION.rotate(-90,QVector3D(1,0,0));
}

MeshData GeometryLoader::extractModelData(){
	readRawData();
	assembleVertices();
	removeUnusedVertices();
	initArrays();
	convertDataToArrays();
	convertIndicesListToArray();
	return MeshData(m_verticesArray.toStdVector(), m_texturesArray.toStdVector(), m_normalsArray.toStdVector(), m_indicesArray.toStdVector(), m_boneIdsArray.toStdVector(), m_weightsArray.toStdVector());
}

void GeometryLoader::readRawData(){
	readPositions();
	readNormals();
	readTextureCoords();
}

void GeometryLoader::readPositions(){
	QString positionsId = m_meshData.namedItem("vertices").namedItem("input").attributes().namedItem("source").toAttr().nodeValue().mid(1);
	QDomNode positionsData =MyXmlNode(m_meshData).getChildWithAttribute("source", "id", positionsId).namedItem("float_array");
	int count = positionsData.attributes().namedItem("count").nodeValue().toInt();
	QStringList posData = positionsData.firstChild().nodeValue().split(" ");
    QList<VertexSkinData>::iterator it = m_vertexWeights.begin();
	for (int i = 0; i < count/3; i++) {
		double x = QString(posData[i * 3]).toDouble();
		double y = QString(posData[i * 3 + 1]).toDouble();
		double z = QString(posData[i * 3 + 2]).toDouble();
		QVector4D position = QVector4D(x, y, z, 1);
		position = m_CORRECTION * position;
		m_vertices.push_back(Vertex(m_vertices.size(), QVector3D(position.x(), position.y(), position.z()), *it));
		it++;
	}
}

void GeometryLoader::readNormals(){
	QString normalsId = MyXmlNode(m_meshData.namedItem("polylist")).getChildWithAttribute("input", "semantic", "NORMAL")
			.attributes().namedItem("source").nodeValue().mid(1);
	QDomNode normalsData = MyXmlNode(m_meshData).getChildWithAttribute("source", "id", normalsId).namedItem("float_array");
	int count = normalsData.attributes().namedItem("count").nodeValue().toInt();
	QStringList normData = normalsData.firstChild().nodeValue().split(" ");
	for (int i = 0; i < count/3; i++) {
		float x = QString(normData[i * 3]).toFloat();
		float y = QString(normData[i * 3 + 1]).toFloat();
		float z = QString(normData[i * 3 + 2]).toFloat();
		QVector4D norm = QVector4D(x, y, z, 0);
		norm = m_CORRECTION * norm;
		m_normals.push_back(QVector3D(norm.x(), norm.y(), norm.z()));
	}
}

void GeometryLoader::readTextureCoords(){
	QString texCoordsId = MyXmlNode(m_meshData.namedItem("polylist")).getChildWithAttribute("input", "semantic", "TEXCOORD")
			.attributes().namedItem("source").nodeValue().mid(1);
	QDomNode texCoordsData = MyXmlNode(m_meshData).getChildWithAttribute("source", "id", texCoordsId).namedItem("float_array");
	int count = texCoordsData.attributes().namedItem("count").nodeValue().toInt();
	QStringList texData = texCoordsData.firstChild().nodeValue().split(" ");
	for (int i = 0; i < count/2; i++) {
		float x = QString(texData[i * 2]).toFloat();
		float y = QString(texData[i * 2 + 1]).toFloat();
		m_textures.push_back(QVector2D(x, y));
	}
}

void GeometryLoader::assembleVertices(){
	QDomNode poly = m_meshData.namedItem("polylist");
	int typeCount = MyXmlNode(poly).getChildren("input").size();
	QStringList indexData = poly.namedItem("p").firstChild().nodeValue().split(" ");
	for(int i=0;i<indexData.size()/typeCount;i++){
		int positionIndex=-1;
		int normalIndex=-1;
		int texCoordIndex=-1;
		if(m_vertices.size()!=0)
			positionIndex = QString(indexData[i * typeCount]).toInt();
		if(m_normals.size()!=0)
			normalIndex = QString(indexData[i * typeCount + 1]).toInt();
		if(m_textures.size()!=0)
			texCoordIndex = QString(indexData[i * typeCount + 2]).toInt();
		processVertex(positionIndex, normalIndex, texCoordIndex);
	}
}

Vertex GeometryLoader::processVertex(int posIndex, int normIndex, int texIndex){
    QList<Vertex>::iterator it = m_vertices.begin();
	advance(it,posIndex);
	if (!it->isSet()) {
		it->setTextureIndex(texIndex);
		it->setNormalIndex(normIndex);
		m_indices.push_back(posIndex);
		return *it;
	} else {
		return dealWithAlreadyProcessedVertex(*it, texIndex, normIndex);
	}
}

QVector<int> GeometryLoader::convertIndicesListToArray(){
    QList<int>::iterator it;
	for (it = m_indices.begin(); it != m_indices.end(); ++it) {
		m_indicesArray.push_back(*it);
	}
	return m_indicesArray;
}

float GeometryLoader::convertDataToArrays(){
	float furthestPoint = 0;
	int i = 0;
    QList<Vertex>::iterator it;
	for (it = m_vertices.begin(); it != m_vertices.end(); ++it,++i) {
		if (it->getLength() > furthestPoint) {
			furthestPoint = it->getLength();
		}
        QList<QVector2D>::iterator itText = m_textures.begin();
		advance(itText,it->getTextureIndex());
        QList<QVector3D>::iterator itNorm = m_normals.begin();
		advance(itNorm,it->getNormalIndex());
		m_verticesArray[i * 3] = it->getPosition().x();
		m_verticesArray[i * 3 + 1] = it->getPosition().y();
		m_verticesArray[i * 3 + 2] = it->getPosition().z();
		if(it->isSet()){
			m_normalsArray[i * 3] = itNorm->x();
			m_normalsArray[i * 3 + 1] = itNorm->y();
			m_normalsArray[i * 3 + 2] = itNorm->z();
			m_texturesArray[i * 2] = itText->x();
			m_texturesArray[i * 2 + 1] = 1 - itText->y();
		}
		else
		{
			m_normalsArray[i * 3] = 0;
			m_normalsArray[i * 3 + 1] = 0;
			m_normalsArray[i * 3 + 2] = 0;
			m_texturesArray[i * 2] = 0;
			m_texturesArray[i * 2 + 1] = 1;
		}
		VertexSkinData weights = it->getWeightsData();
        QList<int>::iterator itBone = weights.getBoneIds().begin();
		m_boneIdsArray[i * 3] = *itBone++;
		m_boneIdsArray[i * 3 + 1] = *itBone++;
		m_boneIdsArray[i * 3 + 2] = *itBone++;
        QList<float>::iterator itWeights = weights.getWeights().begin();
		m_weightsArray[i * 3] = *itWeights++;
		m_weightsArray[i * 3 + 1] = *itWeights++;
		m_weightsArray[i * 3 + 2] = *itWeights++;
	}
	return furthestPoint;
}

Vertex GeometryLoader::dealWithAlreadyProcessedVertex(Vertex previousVertex, int newTextureIndex, int newNormalIndex){
	if (previousVertex.hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
		m_indices.push_back(previousVertex.getIndex());
		return previousVertex;
	} else {
		Vertex* anotherVertex = previousVertex.getDuplicateVertex();
		if (anotherVertex != 0) {
			return dealWithAlreadyProcessedVertex(*anotherVertex, newTextureIndex, newNormalIndex);
		} else {
			Vertex duplicateVertex = Vertex(m_vertices.size(), previousVertex.getPosition(), previousVertex.getWeightsData());
			duplicateVertex.setTextureIndex(newTextureIndex);
			duplicateVertex.setNormalIndex(newNormalIndex);
			previousVertex.setDuplicateVertex(&duplicateVertex);
			m_vertices.push_back(duplicateVertex);
			m_indices.push_back(duplicateVertex.getIndex());
			return duplicateVertex;
		}

	}
}

void GeometryLoader::initArrays(){
    this->m_verticesArray = QVector<float>(m_vertices.size() * 3);
    this->m_texturesArray = QVector<float>(m_vertices.size() * 2);
    this->m_normalsArray = QVector<float>(m_vertices.size() * 3);
	this->m_boneIdsArray = QVector<int>(m_vertices.size() * 3);
    this->m_weightsArray = QVector<float>(m_vertices.size() * 3);
}
void GeometryLoader::removeUnusedVertices(){
	for (Vertex vertex : m_vertices) {
		vertex.averageTangents();
		if (!vertex.isSet()) {
			vertex.setTextureIndex(0);
			vertex.setNormalIndex(0);
		}
	}
}
