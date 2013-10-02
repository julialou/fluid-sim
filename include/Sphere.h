#ifndef SPHERE_H
#define SPHERE_H


#include "Obstacle.h"

/// \file Sphere.h
/// \brief sphere obstacle for fluids, definition of abstract Obstacle
/// \author Julia Lou
/// \date 26/03/2013 created
/// \class Sphere

class Sphere : public Obstacle
{
public:
    /// @brief constructor
    /// @param[in] _pos center position of the sphere in world coordinates
    /// @param[in] _colour color of the sphere
    /// @param[in] _size dimension fo the sphere
    /// @param[in] _shaderName shader to use
    /// @param[in] _params simulation parameters
    /// @param[in] _parent fluid system to which this obstacle belongs
    Sphere(
          const ngl::Vec3 &_pos,
          const ngl::Colour &_colour,
          const ngl::Vec3 &_size,
          const std::string &_shaderName,
          const struct SimulationParams &_params,
          FluidSystem *_parent
          );

    /// @brief destructor
    virtual ~Sphere();

    /// @brief draw the sphere
    virtual void draw() const;

    /// @brief collide with a particle
    /// @param[in] _particle particle to collide with
    virtual void checkCollision(
                                Particle &_particle
                                );

private:
    /// @brief radius
    float m_radius;

    /// @brief radius squared for collision test
    float m_scaleRadius2;

    /// @brief simulation scale radius
    float m_scaleRadius;

    /// @brief sim scaled position
    ngl::Vec3 m_scalePos;

    /// @brief type of obstacle
    const static ObstacleType m_type;
};

#endif // SPHERE_H
