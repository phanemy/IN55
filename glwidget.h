//#ifndef GLWIDGET_H
//#define GLWIDGET_H

//#include <QOpenGLWidget>
//#include <QOpenGLFunctions>

//class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
//{
//	Q_OBJECT
//	public:
//		explicit GLWidget(QWidget *parent = 0);
//		~GLWidget();
//	protected:
//		void initializeGL() override;
//		void resizeGL(int w, int h) override;
//		void paintGL() override;

//};

//#endif // GLWIDGET_H

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QTime>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <math.h>
#include <QCoreApplication>
#include <QSet>
#include <vector>
#include <QDebug>
#include <random>
#include "object3ddynamic.h"
#include "colladaloader.h"
#include "camera.h"
#include "animationdataparser.h"
#include "modeldataparser.h"
#include <QFileDialog>

using namespace std;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
	~GLWidget();

protected:
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void timerEvent(QTimerEvent *e) override;

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void initShaders();
	void initTextures();

private:
	void computeAnimation(float time);
	QBasicTimer m_timer;
	QTime m_fps;
	QOpenGLShaderProgram m_program, m_billboard, m_computeProgramme;

	QVector2D m_mousePressPosition;
	QVector3D m_rotationAxis;
	qreal m_angularSpeed;
	QQuaternion m_rotation;

	Object3DDynamic *m_obj;

	Camera m_camera;

    bool m_runAnim;
    QString m_fileName;
	int m_lastUpdate, m_frameCounter, m_lastFrameTime;

	QSet<int> m_keysPressed;
};

#endif // GLWIDGET_H
