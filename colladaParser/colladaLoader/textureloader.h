#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <QDomNode>
#include "texturedata.h"

class TextureLoader
{
public:
	TextureLoader(QDomNode imagesData);
   ~TextureLoader();
	TextureData extractTexture();

private:
   QDomNode m_imagesData;
};

#endif // TEXTURELOADER_H
