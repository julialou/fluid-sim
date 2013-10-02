#ifndef PARTICLE_H
#define PARTICLE_H

#include <boost/lexical_cast.hpp>
#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <ngl/Camera.h>
#include <ngl/TransformStack.h>
#include "Common.h"


/// \file Particle.h
/// \brief Class defining individual particles
/// \author Julia Lou
/// \date 26/03/2013 drawing colours added
/// \todo optimization and cleanup, cleanup setting colours



class Particle
{
public:


  /// @brief unique Particle ID
  int m_id;

  /// @brief particle position
  ngl::Vec3 m_pos;

  /// @brief old position for grid
  ngl::Vec3 m_oldpos;

  /// @brief list of neighbours to smooth over
  std::vector <Particle*> m_neighbors;

  /// @brief simulation scale
  float m_simScale;

  /// @brief particle's pressure in kg/(m*s^2)
  float m_pressure;

  /// @brief particle's mass in kg
  float m_mass;

  /// @brief particle density in kg/m^3
  float m_density;

  /// @brief rest density
  float m_restDensity;

  /// @brief 2x rest density for drawing
  float m_restDensity2;

  /// @brief particle size
  float m_size;

  /// @brief particle acceleration
  ngl::Vec3 m_acceleration;

  /// @brief internal force on the particle
  ngl::Vec3 m_internalForce;

  /// @brief external force on the particle
  ngl::Vec3 m_externalForce;

  /// @brief particle velocity in m/s
  ngl::Vec3 m_velocity;

  /// @brief particle velocity at time t-1/2(delta_t)
  ngl::Vec3 m_prevVelocity;

  /// @brief particle velocity at time t+1/2(delta_t)
  ngl::Vec3 m_nextVelocity;

  /// @brief particle colour
  ngl::Colour m_colour;

  /// @brief indicate if is a surface particle for marching cubes
  bool m_isSurface;

  /// @brief store the surface normal if this particcle is at the surface
  ngl::Vec3 m_surfaceNormal;





  /// @brief default constructor
  /// @param _idx index
  /// @param _pos position
  /// @param _simScale simulation scale
  /// @param _params fluid parameters
  /// @param _shadername shader to render fluid with
  Particle(
          int _idx,
          ngl::Vec3 _pos,
          float _simScale,
          const FluidParams &_params
          );

  /// @brief get the position
  ngl::Vec3 getPos() const;

  /// @brief get the previousposition
  ngl::Vec3 getOldPos() const;

  /// @brief get the velocity at time t
  ngl::Vec3 getVelocity() const;


  /// @brief see if the particle is on the surface
  bool onSurface() const;


  /// @brief set the current position
  /// @param _pos new position to set
  void setPos(
              const ngl::Vec3 &_pos
              );

  /// @brief allows the bounding box to update velocities at time t and t+0.5dt
  /// @param _velocity new velocity
  void setCollisionVelocity(
                            const ngl::Vec3 &_velocity
                            );

  /// @brief sets the colour of the particle
  /// @param _mode drawing mode of particle
  void updateColour(
      const DrawMode _mode
      );

  /// @brief save the list of new neighbors
  /// @param _neighbors new neighbour list
  void updateNeighbors(
                      const std::vector <Particle*> &_neighbors
                      );


private:
};

#endif // PARTICLE_H
