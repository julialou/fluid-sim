#ifndef __GL_WINDOW_H__
#define __GL_WINDOW_H__

#include <QEvent>
#include <QtOpenGL>
#include <QTime>
#include <ngl/Camera.h>
#include <ngl/Text.h>
#include <ngl/TransformStack.h>
#include <ngl/VAOPrimitives.h>
#include "FluidBBox.h"
#include "FluidSystem.h"
#include "Parser.h"

/// \file GLWindow.h
/// \brief QT GL Window class, based on the NGL Demos by Jon Macey
/// \author Julia Lou
/// \date 26/03/2013 added slots for draw mode
/// \class GLWindow
/// Revision History :
/// Initial Version 10/10/10 (Binary day ;-0 )


class GLWindow : public QGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor for GLWindow
    /// @param [in] _parent the parent window to create the GL context in
    //----------------------------------------------------------------------------------------------------------------------

    GLWindow(
              Parser *_parser,
              QWidget *_parent
            );

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor
    //----------------------------------------------------------------------------------------------------------------------
    ~GLWindow();


    inline void setObstacleDrawMode(const GLenum _mode) { m_obstacleDrawMode = _mode; }

public slots:

    /// @brief start the simulation
    inline void startSimulation() { m_simulate = true; }

    /// @brief stop the simulation
    inline void stopSimulation() { m_simulate = false; }

    /// @brief reset the simulation
    void resetSimulation();

    /// @brief set the number of particles
    inline void setNumParticles(int _n) { m_parser->m_simSettings.numParticles = _n; }

    /// @brief set the drawing mode for particles
    inline void setDrawMode(int _n) { m_fluidDrawMode = _n; }

    /// @brief set the x dimensions of the container
    inline void setContainerX(double _n) { m_parser->m_simSettings.containerDimensions.m_x = (float)_n; }

    /// @brief set the y dimensions of the container
    inline void setContainerY(double _n) { m_parser->m_simSettings.containerDimensions.m_y = (float)_n; }

    /// @brief set the z dimensions of the container
    inline void setContainerZ(double _n) { m_parser->m_simSettings.containerDimensions.m_z = (float)_n; }

    /// @brief set the simulation scale
    inline void setSimScale(double _n) { m_parser->m_simSettings.simScale = _n; }

    /// @brief set the timestep
    inline void setTimeStep(double _n) { m_parser->m_simSettings.timeStep = _n; }

    /// @brief set the smoothing radius
    inline void setSmoothRadius(double _n) { m_parser->m_simSettings.smoothRadius = _n; }

    /// @brief set the collision elasticity (coefficient of restitution)
    inline void setElasticity(double _n) { m_parser->m_simSettings.elasticity = _n; }



    /// @brief set particle mass
    inline void setParticleMass(double _n) { m_parser->m_fluidSettings.mass = _n; }

    /// @brief set the particle radius
    inline void setParticleRadius(double _n) { m_parser->m_fluidSettings.size = _n; }

    /// @brief set the rest density
    inline void setRestDensity(double _n) { m_parser->m_fluidSettings.restDensity = _n; }

    /// @brief set the viscosity
    inline void setViscosity(double _n) { m_parser->m_fluidSettings.viscosity = _n; }

    /// @brief set the surface tension
    inline void setSurfaceTension(double _n) { m_parser->m_fluidSettings.tension = _n; }

    /// @brief set the stiffness/gas constant
    inline void setStiffness(double _n) { m_parser->m_fluidSettings.gasK = _n; }

    /// @brief set the threshold
    inline void setThreshold(double _n) { m_parser->m_fluidSettings.threshold = _n; }

    /// @brief set the x component of the gravity acceleration
    inline void setGravityX(double _n) { m_parser->m_fluidSettings.gravity.m_x = _n; }

    /// @brief set the y component of the gravity acceleration
    inline void setGravityY(double _n) { m_parser->m_fluidSettings.gravity.m_y = _n; }

    /// @brief set the z component of the gravity acceleration
    inline void setGravityZ(double _n) { m_parser->m_fluidSettings.gravity.m_z = _n; }

    /// @brief set the isovalue
    inline void setIsovalue(double _n) { m_parser->m_mcSettings.isovalue = _n; }

    /// @brief set the voxel size
    inline void setVoxelSize(double _n) { m_parser->m_mcSettings.voxelSize = _n; }

    /// @brief set the isosurface method
    inline void setIsosurface(int _n) { m_parser->m_mcSettings.isosurface = _n; }

    /// @brief set the blob radius
    inline void setBlobRadius(double _n) { m_parser->m_mcSettings.blobRadius = _n; }

    /// @brief set x of obstacle to create
    inline void setObstacleX(double _n) { m_obstaclePosX = _n; }

    /// @brief set y of obstacle to create
    inline void setObstacleY(double _n) { m_obstaclePosY = _n; }

    /// @brief set z of obstacle to create
    inline void setObstacleZ(double _n) { m_obstaclePosZ = _n; }

    /// @brief set radius of obstacle to create
    inline void setObstacleRadius(double _n) { m_obstacleRadius = _n; }

    /// @brief create an obstacle
    void createObstacle();

    /// @brief delete an obstacle
    void deleteObstacles();


private :
    /// @brief camera
    ngl::Camera *m_cam;

    /// @brief transformations
    ngl::TransformStack m_transformStack;

    /// @brief aspect ratio of the camera
    float m_aspect;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the x rotation mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_spinXFace;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the y rotation mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_spinYFace;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the mouse button is pressed when dragging
    //----------------------------------------------------------------------------------------------------------------------
    bool m_rotate;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the Right mouse button is pressed when dragging
    //----------------------------------------------------------------------------------------------------------------------
    bool m_translate;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous x mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_origX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous y mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_origY;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous x mouse value for Position changes
    //----------------------------------------------------------------------------------------------------------------------
    int m_origXPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous y mouse value for Position changes
    //----------------------------------------------------------------------------------------------------------------------
    int m_origYPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;

    /// @brief bounding box;
    FluidBBox *m_boundingBox;

    /// @brief parser for parameters
    Parser *m_parser;

    /// @brief text for fps
    ngl::Text *m_text;


    /// @brief Timer for time steps
    QTime m_timer;

    /// @brief Timer for fps
    int m_fpsTimer;

    /// @brief frame counter
    int m_frames;

    /// @brief frame counter
    int m_fps;

    /// @brief flag indicating whether the simulation is running
    bool m_simulate;

    /// @brief Fluid system
    FluidSystem *fluid1;

    /// @brief draw mode (points, random colour, velocity, density)
    int m_fluidDrawMode;

    /// @brief create obstacle position x;
    float m_obstaclePosX;

    /// @brief create obstacle position x;
    float m_obstaclePosY;

    /// @brief create obstacle position x;
    float m_obstaclePosZ;

    /// @brief create obstacle radius
    float m_obstacleRadius;

    /// @brief draw mode for obstacles
    GLenum m_obstacleDrawMode;

    /// @brief isovalue for marching cubes
    float m_isovalue;


protected:
    /// @brief from NGL demos
    void loadMatricesToShader(
                               ngl::TransformStack &_tx
                              );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief  The following methods must be implimented in the sub class
    /// this is called when the window is created
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called whenever the window is re-sized
    /// @param[in] _w the width of the resized window
    /// @param[in] _h the height of the resized window
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(
                    const int _w,
                    const int _h
                  );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is the main gl drawing routine which is called whenever the window needs to
    /// be re-drawn
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL();



private :

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (
                          QMouseEvent * _event
                        );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent (
                            QMouseEvent *_event
                         );

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent (
                            QMouseEvent *_event
                            );

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void wheelEvent(
                      QWheelEvent *_event
                   );

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime a timer is triggered
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void timerEvent(
                  QTimerEvent *_event
                  );

};

#endif
