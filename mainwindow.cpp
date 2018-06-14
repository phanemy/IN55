#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    MainWindow::m_fileName =QString();/* QFileDialog::getOpenFileName(0,
//    tr("Open Collada File"), "", tr("Collada Files (*.dae)"));*/

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

//QString MainWindow::getFileName(){
//    return m_fileName;
//}

