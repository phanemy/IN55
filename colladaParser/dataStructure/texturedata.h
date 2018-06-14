#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H
#include <QString>

class TextureData
{
public:
	TextureData(QString m_textUrl);
	QString getTextUrl();

private:
	QString m_textUrl;
};

#endif // TEXTUREDATA_H
