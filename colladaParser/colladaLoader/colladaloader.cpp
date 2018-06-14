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
//    QMessageBox::information(0, "Nom de la balise", "Le nom de la balise est " + dom_element.tagName());
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
		cout << "import skinningData"<<endl;
//        QDomNode skin = dom_element.namedItem("library_controllers").namedItem("controller").namedItem("skin");
        SkinLoader skinLoader = SkinLoader(library_controllers_node, maxWeights);
        SkinningData skinningData = skinLoader.extractSkinData();
		cout << "import jointsData"<<endl;
        SkeletonLoader bonesLoader = SkeletonLoader(dom_element.namedItem("library_visual_scenes"), skinningData.getBoneOrder());
        SkeletonData jointsData = bonesLoader.extractBoneData();
		cout << "import meshData"<<endl;
		GeometryLoader g = GeometryLoader(dom_element.namedItem("library_geometries"), skinningData.getVertexSkinData());
		MeshData meshData = g.extractModelData();
		cout << "import texture"<<endl;
		TextureLoader t = TextureLoader(library_images_node);
		TextureData textureData = t.extractTexture();
//		cout <<"textureData "<<textureData.getTextUrl().toStdString()<<endl;
		colladaFile->close();
		cout << "import end"<<endl;
		return AnimatedModelData(meshData, jointsData,textureData);
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
//	QMessageBox::information(0, "Nom de la balise", "Le nom de la balise est " + dom_element.tagName());
	QDomNode library_animations_node = dom_element.namedItem("library_animations");
	QDomNode library_visual_scenes_node = dom_element.namedItem("library_visual_scenes");
	if(library_animations_node.isNull() || library_visual_scenes_node.isNull())
	{
//		QMessageBox::warning(0, "Erreur à l'ouverture du document XML","impossible de trouver le noeuds library_animations et/ou le noeud library_visual_scenes");
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
