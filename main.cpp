#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#include <QtXml>
#include <QMessageBox>
#include <vector>
#include "colladaloader.h"
#include "mainwindow.h"
#include <QFileDialog>

using namespace std;

int main(int argc, char *argv[])
{
//	QApplication app(argc, argv);

//	QSurfaceFormat format;
//	format.setDepthBufferSize(24);
//	QSurfaceFormat::setDefaultFormat(format);

//	app.setApplicationName("Template IN55");
//	app.setApplicationVersion("1.0");

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
