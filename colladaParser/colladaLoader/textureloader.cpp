#include "textureloader.h"


TextureLoader::TextureLoader(QDomNode imagesData){
	m_imagesData = imagesData;
}

TextureLoader::~TextureLoader(){}

TextureData TextureLoader::extractTexture(){
	QString temp = m_imagesData.namedItem("image").namedItem("init_from").firstChild().nodeValue();
	return TextureData(temp);
}
