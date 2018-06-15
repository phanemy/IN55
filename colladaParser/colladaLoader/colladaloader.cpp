#include "colladaloader.h"
#include <QString>

AnimatedModelData ColladaLoader::loadColladaModel(QFile* colladaFile, int maxWeights) {

    QDomDocument dom("collada_file");
    if(!colladaFile->open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
		exit(-1);
    }
    if (!dom.setContent(colladaFile))
    {
     colladaFile->close();
     QMessageBox::warning(0, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
		exit(-1);
    }
    QDomElement dom_element = dom.documentElement();
	QDomNode library_controllers_node = dom_element.namedItem("library_controllers");
	if(library_controllers_node.isNull())
	{
		QMessageBox::warning(0, "Erreur à l'ouverture du document XML","impossible de trouver le neoud library_controllers");
		exit(-1);
	}
	QDomNode library_images_node = dom_element.namedItem("library_images");
	if(library_controllers_node.isNull())
	{
		QMessageBox::warning(0, "Erreur à l'ouverture du document XML","impossible de trouver le neoud library_images");
		exit(-1);
	}
    else
    {
        SkinLoader skinLoader = SkinLoader(library_controllers_node, maxWeights);
        SkinningData skinningData = skinLoader.extractSkinData();
        SkeletonLoader bonesLoader = SkeletonLoader(dom_element.namedItem("library_visual_scenes"), skinningData.getBoneOrder());
		SkeletonData bonesData = bonesLoader.extractBoneData();
		GeometryLoader g = GeometryLoader(dom_element.namedItem("library_geometries"), skinningData.getVertexSkinData());
		MeshData meshData = g.extractModelData();
		TextureLoader t = TextureLoader(library_images_node);
		TextureData textureData = t.extractTexture();
		colladaFile->close();
		return AnimatedModelData(meshData, bonesData,textureData);
	}
}

AnimationData ColladaLoader::loadColladaAnimation(QFile* colladaFile) {
	QDomDocument dom("collada_file");
	if(!colladaFile->open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(0, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
		exit(-1);
	}
	if (!dom.setContent(colladaFile))
	{
	 colladaFile->close();
	 QMessageBox::warning(0, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
		exit(-1);
	}
	QDomElement dom_element = dom.documentElement();
	QDomNode library_animations_node = dom_element.namedItem("library_animations");
	QDomNode library_visual_scenes_node = dom_element.namedItem("library_visual_scenes");
	if(library_animations_node.isNull() || library_visual_scenes_node.isNull())
	{
		exit(-1);
	}
	else
	{
		AnimationLoader loader = AnimationLoader(library_animations_node, library_visual_scenes_node);
		AnimationData animData = loader.extractAnimation();
		colladaFile->close();
		return animData;
	}


}
