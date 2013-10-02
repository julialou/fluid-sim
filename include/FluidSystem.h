#ifndef FLUIDSYSTEM_H
#define FLUIDSYSTEM_H

#include <cstdlib>
#include <ngl/BBox.h>
#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/ShaderLib.h>
#include <ngl/TransformStack.h>
#include <ngl/Util.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Vec3.h>
#include "FluidBBox.h"
#include "Common.h"
#include "Grid.h"
#include "MarchingCubes.h"
#include "Obstacle.h"
#include "Particle.h"

/// \file FluidSystem.h
/// \brief Class containing the fluid solver, including all particles
/// \author Julia Lou
/// \date 26/03/2013 Pressure corrected
/// \todo optimization and cleanup, velocity clamping?


const unsigned int c_maxObstacles = 5;

class FluidSystem
{
public:
  /// @brief default constructor
  FluidSystem();

  /// @brief constructor
  /// @param _simParams simulation parameters
  /// @param _fluidParams fluid parameters
  /// @param _shadername shader to render fluid with
  /// @param _transformStack pointer to the Transform stack for rendering
  FluidSystem(
              const struct SimulationParams &_simParams,
              const struct FluidParams &_fluidParams,
              const struct MCubesParams &_mcubesParams,
              const std::string &_shadername,
              ngl::TransformStack *_transformStack

              );

  /// @brief destructor
  ~FluidSystem();


  /// @brief resets the fluid when button pressed by user
  /// @param[in] _simParams simulation settings
  /// @param[in] _fluidParams fluid settings
  void reset(
            const struct SimulationParams &_simParams,
            const struct FluidParams &_fluidParams,
            const struct MCubesParams &_mcubesParams
            );

  /// @brief update the fluid system for the next time step
  void updateFluid();

  /// @brief set camera
  /// @param _cam pointer to the camera
  inline void setCamera(ngl::Camera *_cam) { m_cam = _cam; }

  /// @brief get camera
  inline ngl::Camera* getCamera() const { return m_cam; }

  /// @brief get transform stack
  inline ngl::TransformStack* getTransformStack() const { return m_transformStack; }


  /// @brief set bounding box
  /// @param _fbbox pointer to the bounding box
  inline void setBBox(FluidBBox *_fbbox) {m_fbbox = _fbbox; }

  /// @brief draw the new fluid
  /// @param _mode drawing mode for particles
  /// @param _obstacleMode wireframe or solid shading for obstacles
  void draw(
            DrawMode _mode,
            unsigned int _obstacleMode
            );

  /// @brief draws coloured spheres for particles
  /// @param _mode drawing mode for particles
  void drawSpheres(
                    DrawMode _mode
                    );


  /// @brief creates an obstacle
  /// @param _type enum type of the obstacle to create
  /// @param _pos center of the obstacle
  /// @param _size size of the obstacle
  /// @param _shaderName shader to draw with
  /// @param _params simulation parameters
  void createObstacle(
                      ObstacleType _type,
                      const ngl::Vec3 &_pos,
                      const ngl::Vec3 &_size,
                      const std::string &_shaderName,
                      const SimulationParams &_params
                      );


  /// @brief erases the last obstacle
  void removeObstacles();


private:
  /// @brief camera
  ngl::Camera *m_cam;

  /// @brief shader for sphere
  std::string m_shaderName;

  /// @brief transform stack
  ngl::TransformStack *m_transformStack;

  /// @brief bounding box
  FluidBBox *m_fbbox;

  /// @brief store particle parameters
  struct FluidParams m_fParams;


  /// @brief marching cubes
  MarchingCubes *m_cubes;


  /** SPH **/

  /// @brief Particle size
  float m_psize;

  /// @brief simulation
  float m_simScale;

  /// @brief smoothing radius
  float m_h;

  /// @brief premultipled h^2
  float m_h2;

  /// @brief timestep for simulation
  float m_timestep;

  /// @brief dimensions of the uniform grid
  ngl::Vec3 m_gridSize;

  /// @brief number of particles in the simulation
  int m_numParticles;

  /// @brief container for all particles
  std::vector <Particle> m_particleContainer;

  /// @brief grid to make it easy to find neighbors
  Grid *m_particleGrid;


  /// @brief vao for mesh
  ngl::VertexArrayObject *m_vao;

  /// @brief vector storing collision objects
  std::vector <Obstacle *> m_obstacleContainer;



  /** Fluid Properties **/
  /// @brief rest density in kg/m^3
  float m_restdensity;

  /// @brief surface threshold
  float m_threshold;

  /// @brief tension coefficient
  float m_tension;

  /// @brief gravity on the particle
  ngl::Vec3 m_gravity;

  /// @brief viscosity
  float m_viscosity;

  /// @brief gas constant
  float m_gasK;



  /** precalculated kernel values for optimization **/
  /// @brief default kernel coefficient: 315/(64 * PI * h^9)
  float m_defaultKernelCoefficient;

  /// @brief default gradient coefficient: - 945/(32 * PI * h^9)
  float m_defaultGradientCoefficient;

  /// @brief default Laplacian coefficient: - 945/(32 * PI * h^9)
  float m_defaultLaplacianCoefficient;

  /// @brief spiky gradient coefficient for pressure: -45/(PI * h^6)
  float m_pressureGradientCoefficient;

  /// @brief viscosity Laplacian coefficient: 45/(PI * h^6)
  float m_viscosityLaplacianCoefficient;


  /** Marching Cubes **/
  /// @brief isovalue
  float m_isovalue;

  /// @brief voxel size
  float m_voxelSize;

  /// @brief blob radius
  float m_blobRadius;


  /// @brief general kernel function using kernel from Muller
  /// Wpoly6(r,h) = 315 / ( 64 * PI * h ^9) : { ( h^2 - |r|^2)^3 for 0<=r<= h; 0 otherwise }
  /// @param _i current particle
  /// @param _j neighbour particle
  float computeKernel(
                    const Particle &_i,
                    const Particle &_j
                    );

  /// @brief gradient function for default kernel
  /// gradientW(r,h) = - 945/(32 * PI * h^9) * r * (h^2 - |r|^2)^2
  /// @param _i current particle
  /// @param _j neighbour particle
  ngl::Vec3 computeDefaultGradient(
                                  const Particle &_i,
                                  const Particle &_j
                                  );

  /// @brief Laplacian function for default kernel
  /// laplacianW(r,h) = -945/(32 * PI * h^9) * (h^2 - |r|^2) * (3 * h^2 - 7 * |r|^2)
  /// @param _i current particle
  /// @param _j neighbour particle
  float computeDefaultLaplacian(
                                const Particle &_i,
                                const Particle &_j
                                );

  /// @brief gradient function for pressure using Debrun's spiky kernel
  /// gradientWspiky(r,h) = -45/(PI * h^6) * (r/|r|) * (h - |r|)^2
  /// @param _i current particle
  /// @param _j neighbour particle
  ngl::Vec3 computePressureGradient(
                                    const Particle &_i,
                                    const Particle &_j
                                    );

  /// @brief Laplacian function for viscosity kernel as in Kelager
  /// (laplacian op)W(r,h) = (45/(PI * h^6)) * (h-r)
  /// @param _i current particle
  /// @param _j neighbour particle
  float computeViscosityLaplacian(
                                  const Particle &_i,
                                  const Particle &_j
                                  );

  /// @brief compute kernel coefficients
  void computeCoefficients();


  /** SPH calculations **/
  /// @brief compute new density and pressure values
  /// @param _particle particle to calculate densities
  void updateDensityPressure(
                          Particle &io_particle
                          );

  /// @brief compute new internal forces (pressure + viscosity)
  /// @param _particle to calculate forces for
  void updateInternalForces(
                          Particle &io_particle
                          );

  /// @brief compute new external forces (gravity + surface tension)
  /// @param _particle to calculate forces for
  void updateExternalForces(
                          Particle &io_particle
                          );

  /// @brief calculate new acceleration and advance particle's velocity and position with leapfrog method
  /// @param _particle particle to advance3
  /// @param _dtime timestep
  void advanceParticle(
                      Particle &io_particle,
                      float _dtime
                      );

};

#endif // FLUIDSYSTEM_H
