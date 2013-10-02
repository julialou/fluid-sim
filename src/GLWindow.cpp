#include <iostream>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include "GLWindow.h"


/// \file GLWindow.cpp
/// \brief QT GL Window class, based on the NGL Demos by Jon Macey
/// \author Julia Lou
/// \date 26/03/2013 added slots for draw mode
/// \class GLWindow
/// Revision History :
/// based on ngl demos
/// Initial Version 10/10/10 (Binary day ;-0 )


// this file is based on the NGL Demos

/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=0.01;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.1;


//----------------------------------------------------------------------------------------------------------------------
// in this ctor we need to call the CreateCoreGLContext class, this is mainly for the MacOS Lion version as
// we need to init the OpenGL 3.2 sub-system which is different than other platforms
//----------------------------------------------------------------------------------------------------------------------
GLWindow::GLWindow(
                   Parser *_parser,
                   QWidget *_parent
                  )
                    : QGLWidget( new CreateCoreGLContext(QGLFormat::defaultFormat()), _parent )
{

  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  // Now set the initial GLWindow attributes to default values
  // Rotate is false
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0;
  m_spinYFace=0;

  // start with simulation running
  m_simulate = true;

  m_fps = 0;
  m_frames = 0;
  m_fpsTimer = startTimer(0);
  m_timer.start();

  // create Fluid System
  m_parser =  _parser;
  fluid1 = new FluidSystem(m_parser->m_simSettings,m_parser->m_fluidSettings, m_parser->m_mcSettings, "Colour", &m_transformStack);
  m_fluidDrawMode = 4;
  m_obstacleDrawMode = GL_LINE;
  m_obstaclePosX = 0.0;
  m_obstaclePosY = 0.0;
  m_obstaclePosZ = 0.0;
  m_obstacleRadius = 0.4;
}

//----------------------------------------------------------------------------------------------------------------------
GLWindow::~GLWindow()
{
  ngl::NGLInit *Init = ngl::NGLInit::instance();
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  Init->NGLQuit();
}

//----------------------------------------------------------------------------------------------------------------------
// This virtual function is called once before the first call to paintGL() or resizeGL(),
//and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining VBOs etc.
//----------------------------------------------------------------------------------------------------------------------
void GLWindow::initializeGL()
{
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // we need to initialise the NGL lib, under windows and linux we also need to
  // initialise GLEW, under windows this needs to be done in the app as well
  // as the lib hence the WIN32 define
  ngl::NGLInit *Init = ngl::NGLInit::instance();
  // init GLEW for the lib
  Init->initGlew();
  #ifdef WIN32
    glewInit(); // need a local glew init as well as lib one for windows
  #endif

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  shader->createShaderProgram("Phong");

  shader->attachShader("PhongVertex",ngl::VERTEX);
  shader->attachShader("PhongFragment",ngl::FRAGMENT);
  shader->loadShaderSource("PhongVertex","shaders/Phong.vs");
  shader->loadShaderSource("PhongFragment","shaders/Phong.fs");

  shader->compileShader("PhongVertex");
  shader->compileShader("PhongFragment");
  shader->attachShaderToProgram("Phong","PhongVertex");
  shader->attachShaderToProgram("Phong","PhongFragment");

  shader->bindAttribute("Phong",0,"inVert");

  shader->bindAttribute("Phong",1,"inUV");

  shader->bindAttribute("Phong",2,"inNormal");


  shader->linkProgramObject("Phong");
  (*shader)["Phong"]->use();
  //shader->setShaderParam1i("Normalize",1);
  //ngl::Material m(ngl::GOLD);
 // m.loadToShader("material");

  shader->createShaderProgram("Colour");

  shader->attachShader("ColourVertex",ngl::VERTEX);
  shader->attachShader("ColourFragment",ngl::FRAGMENT);
  shader->loadShaderSource("ColourVertex","shaders/Colour.vs");
  shader->loadShaderSource("ColourFragment","shaders/Colour.fs");

  shader->compileShader("ColourVertex");
  shader->compileShader("ColourFragment");
  shader->attachShaderToProgram("Colour","ColourVertex");
  shader->attachShaderToProgram("Colour","ColourFragment");

  shader->bindAttribute("Colour",0,"inVert");
  shader->linkProgramObject("Colour");
  (*shader)["Colour"]->use();
  shader->setShaderParam4f("Colour",1,1,1,1);


  // create camera
  ngl::Vec3 from(0,0.5,4);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);
  m_cam = new ngl::Camera(from, to, up,ngl::PERSPECTIVE);
  m_cam->setShape(45,(float)720.0/576.0,0.05,350,ngl::PERSPECTIVE);
  shader->setShaderParam3f("viewerPos",m_cam->getEye().m_x,m_cam->getEye().m_y,m_cam->getEye().m_z);




  ngl::Light light(ngl::Vec3(2,2,5),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::POINTLIGHT);
  // now create our light this is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv=m_cam->getViewMatrix();
  iv=iv.inverse();
  iv.transpose();
  light.setTransform(iv);
  light.setAttenuation(1,0,0);
  light.enable();

  fluid1->setCamera(m_cam);

  (*shader)["Phong"]->use();
  light.loadToShader("light");



  m_text = new ngl::Text(QFont("Arial",14));

  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->createSphere("sphere",0.05,10);
  prim->createSphere("collisionSphere", 1.0, 20);


 m_boundingBox = new FluidBBox(m_parser->m_simSettings);

  fluid1->setBBox(m_boundingBox);
  m_boundingBox->setDrawMode(GL_LINE);



}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
//----------------------------------------------------------------------------------------------------------------------
void GLWindow::resizeGL(
                        int _w,
                        int _h
                       )
{
  // set the viewport for openGL
  glViewport(0,0,_w,_h);
  // calculate the aspect ratio
  m_aspect=(float)_w/_h;
  m_cam->setShape(45, m_aspect, 0.05,350, ngl::PERSPECTIVE);
  m_text->setScreenSize(_w,_h);
}




//----------------------------------------------------------------------------------------------------------------------
void GLWindow::loadMatricesToShader(
                                     ngl::TransformStack &_tx
                                   )
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=_tx.getCurrAndGlobal().getMatrix();
  MV= _tx.getCurrAndGlobal().getMatrix()*m_cam->getViewMatrix();
  MVP= M*m_cam->getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);
}



//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
//----------------------------------------------------------------------------------------------------------------------
void GLWindow::paintGL()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // update the fluid system
  if( m_simulate == true )
  {
    fluid1->updateFluid();
  }

  // draw the bounding box in wireframe mode
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  // load the colour  shader and set the values,
  shader->use("Colour");
  shader->setShaderParam4f("Colour", 1.0, 1.0, 1.0, 1.0);



  // Rotation based on the mouse position for our global transform
  ngl::Transformation trans;
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX(m_spinXFace);
  rotY.rotateY(m_spinYFace);
  // multiply the rotations
  ngl::Mat4 final=rotY*rotX;
  // add the translations
  final.m_m[3][0] = m_modelPos.m_x;
  final.m_m[3][1] = m_modelPos.m_y;
  final.m_m[3][2] = m_modelPos.m_z;
  // set this in the TX stack
  trans.setMatrix(final);
  m_transformStack.setGlobal(trans);

  m_transformStack.pushTransform();
  {
    m_transformStack.setPosition(0,0,0);
    ngl::Mat4 MVP;
    MVP=m_transformStack.getCurrAndGlobal().getMatrix() *
        m_cam->getViewMatrix() *
        m_cam->getProjectionMatrix();

    shader->setShaderParamFromMat4("MVP",MVP);
    m_boundingBox->draw();

    // solid drawing for fluid
    //glPolygonMode(GL_FRONT_AND_BACK,m_obstacleDrawMode);
    fluid1->draw((DrawMode)m_fluidDrawMode, m_obstacleDrawMode);
    //m_simulate=false;
  }
  m_transformStack.popTransform();

  ++m_frames;
  m_text->setColour(1,1,1);
  QString text=QString("FPS: %2 ").arg(m_fps);
  QString textInfo = QString("w/s for wireframe/shaded");
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  m_text->renderText(10,10,text);
  m_text->renderText(10,30,textInfo);

}




//----------------------------------------------------------------------------------------------------------------------
void GLWindow::resetSimulation()
{
  //m_simulate = false;

  // reset using the updated parameters
  fluid1->reset(m_parser->m_simSettings, m_parser->m_fluidSettings, m_parser->m_mcSettings);
  m_boundingBox->resetBBox(m_parser->m_simSettings);
  fluid1->setBBox(m_boundingBox);
  fluid1->setCamera(m_cam);
  m_boundingBox->setDrawMode(GL_LINE);

  std::cout << "reset simulation with max " << m_parser->m_simSettings.numParticles << " particles" << std::endl;

  // call update once so the new reset instance is drawn
  updateGL();
}


//----------------------------------------------------------------------------------------------------------------------
void GLWindow::createObstacle()
{
  fluid1->createObstacle(SPHERE, ngl::Vec3(m_obstaclePosX, m_obstaclePosY, m_obstaclePosZ), ngl::Vec3(m_obstacleRadius,0,0), "Phong", m_parser->m_simSettings);
  updateGL();
}

void GLWindow::deleteObstacles()
{
  fluid1->removeObstacles();
  updateGL();
}



//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mouseMoveEvent (
                               QMouseEvent * _event
                              )
{
  // note the method buttons() is the button state when event was called
  // this is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if(m_rotate && _event->buttons() == Qt::LeftButton)
  {
    int diffx=_event->x()-m_origX;
    int diffy=_event->y()-m_origY;
    m_spinXFace += (float) 0.5f * diffy;
    m_spinYFace += (float) 0.5f * diffx;
    m_origX = _event->x();
    m_origY = _event->y();
    updateGL();

  }
    // right mouse translate code
  else if(m_translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos=_event->x();
    m_origYPos=_event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    updateGL();

  }

}


//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mousePressEvent (
                                QMouseEvent * _event
                               )
{
  // this method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate =true;
  }
    // right mouse translate mode
    else if(_event->button() == Qt::RightButton)
    {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
        m_translate=true;
    }

}

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mouseReleaseEvent (
                                  QMouseEvent * _event
                                 )
{
  // this event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_rotate=false;
  }
    // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_translate=false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::wheelEvent(
                          QWheelEvent *_event
                          )
{

  // check the diff of the wheel position (0 means no change)
  if(_event->delta() > 0)
  {
    m_modelPos.m_z+=ZOOM;
  }
  else if(_event->delta() <0 )
  {
    m_modelPos.m_z-=ZOOM;
  }
  updateGL();
}
//----------------------------------------------------------------------------------------------------------------------

void GLWindow::timerEvent(QTimerEvent *_event)
{

    if(_event->timerId() == m_fpsTimer)
    {
        if(m_timer.elapsed()>1000.0)
        {
            m_fps = m_frames;
            m_frames = 0;
            m_timer.restart();
        }
    }
  if (m_simulate != true)
  {
    return;
  }
  updateGL();
}

//----------------------------------------------------------------------------------------------------------------------
