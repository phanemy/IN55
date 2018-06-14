#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	m_angularSpeed(0),
	m_camera()
{
//    m_fileName = QFileDialog::getOpenFileName(0,tr("Open Callada File"), "", tr("Callada Files (*.dae)"));
    m_runAnim = false;
	this->setFocusPolicy(Qt::StrongFocus);
	m_camera.setSpeed(3);
}

GLWidget::~GLWidget()
{
	// Make sure the context is current when deleting the texture
	// and the buffers.
	makeCurrent();
	delete m_obj;
	doneCurrent();
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	m_keysPressed += event->key();
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	m_keysPressed -= event->key();
}

void GLWidget::timerEvent(QTimerEvent *)
{
//	cout << "\ntime "<<m_fps.elapsed()<< " "<<m_frameCounter<<endl;
	float temp = (m_fps.elapsed() - m_lastUpdate) / 1000.0;
	m_lastUpdate = m_fps.elapsed();

	if (m_keysPressed.count() > 0)
	{
        QVector3D moveForward = QVector3D(0, 0, 0);
        QVector3D moveUp = QVector3D(0, 0, 0);
		float roulis = 0, tangage = 0, lacet = 0;

		if (m_keysPressed.contains(Qt::Key_Z))
            moveForward += m_camera.getDir();
		else if (m_keysPressed.contains(Qt::Key_S))
            moveForward -= m_camera.getDir();

		if (m_keysPressed.contains(Qt::Key_Shift))
            moveUp += m_camera.getUp();
		else if (m_keysPressed.contains(Qt::Key_Control))
            moveUp -= m_camera.getUp();

        if (m_keysPressed.contains(Qt::Key_P))
            m_runAnim = !m_runAnim;

		if (m_keysPressed.contains(Qt::Key_Up))
            tangage -= 30;
		else if (m_keysPressed.contains(Qt::Key_Down))
            tangage += 30;

		if (m_keysPressed.contains(Qt::Key_Left))
            lacet += 30;
		else if (m_keysPressed.contains(Qt::Key_Right))
            lacet -= 30;

		if (m_keysPressed.contains(Qt::Key_A))
            roulis -= 30;
		else if (m_keysPressed.contains(Qt::Key_E))
            roulis += 30;

        if (!moveForward.isNull())
		{
            moveForward.normalize();
            m_camera.moveForward(moveForward * temp * m_camera.getSpeed());
		}
        if (!moveUp.isNull())
        {
            moveUp.normalize();
            m_camera.moveUp(moveUp * temp * m_camera.getSpeed());
        }

		if (tangage)
			m_camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(m_camera.getUp(), m_camera.getDir()), temp * tangage * m_camera.getSpeed()));
		if(roulis)
			m_camera.rotate(QQuaternion::fromAxisAndAngle(m_camera.getDir(), temp * roulis * m_camera.getSpeed()));
		if(lacet)
			m_camera.rotate(QQuaternion::fromAxisAndAngle(m_camera.getUp(), temp * lacet * m_camera.getSpeed()));
	}

    if(m_runAnim)
        computeAnimation(temp);

	update();
	m_frameCounter++;

	float checkSecond = m_fps.elapsed() - m_lastFrameTime;

	if (checkSecond > 1000)
	{
		qDebug() << checkSecond / float(m_frameCounter) << "ms/frame or " << float(m_frameCounter) * 1000 / checkSecond << "fps";
		m_frameCounter = 0;
		m_lastFrameTime = m_fps.elapsed();
	}
}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();

	glClearColor(0, 0, 0, 1);

	initShaders();

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// Enable back face culling
//	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);
//cout<<"import"<<endl;
//    QFile xml_doc("testPiramide.dae");

//	QFile xml_doc("model.dae");
//	QFile xml_doc("persoTest.dae");
//	QFile xml_doc("Walk_doneMoi.dae");

	QFile xml_doc("Bras.dae");
//	QFile xml_doc("CubeMoi.dae");

//    QFile xml_doc(m_fileName);
	cout << "\nmodel start\n"<<endl;
	AnimatedModelData modelData = ColladaLoader::loadColladaModel(&xml_doc,3);
	cout << "\nmodel end\n"<<endl;
	m_obj = ModelDataParser::loadModel(modelData);
	AnimationData tempAnim = ColladaLoader::loadColladaAnimation(&xml_doc);
//	cout << "anim"<<endl;
	Animation anim= AnimationDataParser::loadAnimation(tempAnim);
	m_obj->setAnimationList(anim);
//		cout << "end"<<endl;
//cout<<"import end"<<endl
	m_camera.moveTo(0,0,7);

	m_lastUpdate = 0;
	m_lastFrameTime = 0;
	m_frameCounter = 0;

	// Use QBasicTimer because its faster than QTimer
	m_timer.start(1000.0/60.0, this);
	m_fps.start();
    std::cout << "success init" <<std::endl;
}

void GLWidget::initShaders()
{
//	// Compile vertex shader
//	if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "vshader.vsh"))
//		close();

//	// Compile fragment shader
//	if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "fshader.fsh"))
//		close();

//	// Link shader pipeline
//	if (!program.link())
//		close();

//	// Compile vertex shader
//	if (!billboard.addShaderFromSourceFile(QOpenGLShader::Vertex, "vbillboard.vsh"))
//		close();

//	// Compile fragment shader
//	if (!billboard.addShaderFromSourceFile(QOpenGLShader::Fragment, "fshader.fsh"))
//		close();

//	// Link shader pipeline
//	if (!billboard.link())
//		close();

//	if (!computeProgramme.addShaderFromSourceFile(QOpenGLShader::Fragment, "fshader.fsh"))
//		close();
	// Compile vertex shader
	if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "ressources/vshader.glsl"))
		close();
	else
        std::cout << "success initShaders" <<std::endl;

	// Compile fragment shader
	if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "ressources/fshader.glsl"))
		close();

	// Link shader pipeline
	if (!m_program.link())
		close();

	// Bind shader pipeline for use
	if (!m_program.bind())
		close();

	m_program.setUniformValue("diffuseMap", 0);
}

void GLWidget::resizeGL(int w, int h)
{
	m_camera.calculateProjection(w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!m_program.bind())
		close();

	m_obj->drawGeometry(&m_program,m_camera.cameraMatrix());
}

void GLWidget::computeAnimation(float time){
	this->m_obj->computeAnimation(time);
}
