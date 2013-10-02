#include "GLWindow.h"
#include "MainWindow.h"
#include "Parser.h"
#include "ui_MainWindow.h"

/// \file MainWindow.cpp
/// \brief main qt window
/// \author Julia Lou
/// \class MainWindow

//----------------------------------------------------------------------------------------------------------------------
MainWindow::MainWindow(
                       std::string _name,
                       QWidget *parent) :
                       QMainWindow(parent),
                       m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  // create our GLWindow
  m_parser =  new Parser(_name);
  m_gl = new GLWindow(m_parser,this);
  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);

  connect(m_ui->m_numParticlesBox,SIGNAL(valueChanged(int)),m_gl,SLOT(setNumParticles(int)));
  connect(m_ui->m_drawBox,SIGNAL(currentIndexChanged(int)),m_gl,SLOT(setDrawMode(int)));
  connect(m_ui->m_containerSizeXBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setContainerX(double)));
  connect(m_ui->m_containerSizeYBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setContainerY(double)));
  connect(m_ui->m_containerSizeZBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setContainerZ(double)));
  connect(m_ui->m_smoothRadiusBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setSmoothRadius(double)));
  connect(m_ui->m_elasticityBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setElasticity(double)));
  connect(m_ui->m_restDensityBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setRestDensity(double)));
  connect(m_ui->m_viscosityBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setViscosity(double)));
  connect(m_ui->m_tensionBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setSurfaceTension(double)));
  connect(m_ui->m_gasKBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setStiffness(double)));
  connect(m_ui->m_gravityXBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setGravityX(double)));
  connect(m_ui->m_gravityYBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setGravityY(double)));
  connect(m_ui->m_gravityZBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setGravityZ(double)));


  connect(m_ui->m_isovalue, SIGNAL(valueChanged(double)),m_gl,SLOT(setIsovalue(double)));
  connect(m_ui->m_voxelSize, SIGNAL(valueChanged(double)),m_gl,SLOT(setVoxelSize(double)));
  connect(m_ui->m_blobRadius, SIGNAL(valueChanged(double)),m_gl,SLOT(setBlobRadius(double)));
  connect(m_ui->m_isosurface, SIGNAL(currentIndexChanged(int)),m_gl,SLOT(setIsosurface(int)));

  connect(m_ui->m_obstacleXBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setObstacleX(double)));
  connect(m_ui->m_obstacleYBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setObstacleY(double)));
  connect(m_ui->m_obstacleZBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setObstacleZ(double)));
  connect(m_ui->m_obstacleRadiusBox, SIGNAL(valueChanged(double)),m_gl,SLOT(setObstacleRadius(double)));
  connect(m_ui->m_addObstacleButton, SIGNAL(clicked()),m_gl,SLOT(createObstacle()));
  connect(m_ui->m_deleteObstaclesButton, SIGNAL(clicked()),m_gl,SLOT(deleteObstacles()));

  connect(m_ui->m_runButton, SIGNAL(clicked()),m_gl,SLOT(startSimulation()));
  connect(m_ui->m_stopButton, SIGNAL(clicked()),m_gl,SLOT(stopSimulation()));
  connect(m_ui->m_resetButton, SIGNAL(clicked()),m_gl,SLOT(resetSimulation()));


  m_ui->m_numParticlesBox->setValue(m_parser->m_simSettings.numParticles);
  m_ui->m_drawBox->setCurrentIndex(4);
  m_ui->m_containerSizeXBox->setValue(m_parser->m_simSettings.containerDimensions.m_x);
  m_ui->m_containerSizeYBox->setValue(m_parser->m_simSettings.containerDimensions.m_y);
  m_ui->m_containerSizeZBox->setValue(m_parser->m_simSettings.containerDimensions.m_z);
  m_ui->m_smoothRadiusBox->setValue(m_parser->m_simSettings.smoothRadius);
  m_ui->m_elasticityBox->setValue(m_parser->m_simSettings.elasticity);
  m_ui->m_restDensityBox->setValue(m_parser->m_fluidSettings.restDensity);
  m_ui->m_viscosityBox->setValue(m_parser->m_fluidSettings.viscosity);
  m_ui->m_tensionBox->setValue(m_parser->m_fluidSettings.tension);
  m_ui->m_gasKBox->setValue(m_parser->m_fluidSettings.gasK);
  m_ui->m_gravityXBox->setValue(m_parser->m_fluidSettings.gravity.m_x);
  m_ui->m_gravityYBox->setValue(m_parser->m_fluidSettings.gravity.m_y);
  m_ui->m_gravityZBox->setValue(m_parser->m_fluidSettings.gravity.m_z);
  m_ui->m_isovalue->setValue(m_parser->m_mcSettings.isovalue);
  m_ui->m_blobRadius->setValue(m_parser->m_mcSettings.blobRadius);
  m_ui->m_voxelSize->setValue(m_parser->m_mcSettings.voxelSize);
}

//----------------------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete m_ui;
}


//----------------------------------------------------------------------------------------------------------------------
void MainWindow::keyPressEvent(
                               QKeyEvent *_event
                              )
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
  // turn on wirframe rendering
  case Qt::Key_W : m_gl->setObstacleDrawMode(GL_LINE); break;
  // turn off wire frame
  case Qt::Key_S : m_gl->setObstacleDrawMode(GL_FILL); break;
  // show full screen
  case Qt::Key_F : showFullScreen(); break;
  // show windowed
  case Qt::Key_N : showNormal(); break;
  default : break;
  }
  // finally update the GLWindow and re-draw
  m_gl->updateGL();
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::resizeEvent ( QResizeEvent * _event )
{
  //m_gl->resize(_event->size());
}

