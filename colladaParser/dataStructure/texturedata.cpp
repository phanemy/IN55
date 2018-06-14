#include "texturedata.h"


TextureData::TextureData(QString textUrl)
{
	m_textUrl = textUrl;
}


QString TextureData::getTextUrl()
{
	return m_textUrl;
}
