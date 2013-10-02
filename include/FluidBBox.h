#ifndef FLUIDBBOX_H
#define FLUIDBBOX_H

#include <ngl/BBox.h>
#include <ngl/Vec3.h>
#include "Common.h"
#include "Particle.h"

/// \file FluidBBox.h
/// \brief Bounding box for the fluid to collide with, extends the NGL BBox
/// \author Julia Lou
/// \date 26/03/2013 Collision normals corrected


class FluidBBox : public ngl::BBox
{
public:
  /// @brief default ctor
  FluidBBox();

  /// @brief constructor
  /// @param _params simulation parameters
  FluidBBox(
            const struct SimulationParams
            &_params
            );


  /// @brief resets bounding box when button is clicked
  /// @param _params simulation parameters
  void resetBBox(
                const struct SimulationParams &_params
                );

  /// @brief detect collision with the box, updates velocity if there is a collision
  /// @param _particle particle to collide with
  void BBoxCollide(
                  Particle &_particle
                  );


private:
  /// @brief minX in simulation scale
  float m_simScaleMinX;
  /// @brief minX in simulation scale
  float m_simScaleMinY;
  /// @brief minX in simulation scale
  float m_simScaleMinZ;
  /// @brief minX in simulation scale
  float m_simScaleMaxX;
  /// @brief minX in simulation scale
  float m_simScaleMaxY;
  /// @brief minX in simulation scale
  float m_simScaleMaxZ;
  /// @brief simulation scale
  float m_simScale;
  /// @brief collision elasticity (restitution)
  float m_elasticity;
  /// @brief timestep
  float m_timeStep;


  /// @brief calculates new min and max values for m_width, m_height, m_depth
  void recalcMinMax();
  /// @brief calculates min and max values in simulation scale
  void recalcScaled();

};

#endif // FLUIDBBOX_H
