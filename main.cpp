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

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
