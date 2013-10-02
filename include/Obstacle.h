#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <ngl/Colour.h>
#include <ngl/TransformStack.h>
#include <ngl/Vec3.h>
#include "Parser.h"
#include "Particle.h"


/// \file Obstacle.h
/// \brief abstract obstacle for fluids
/// \author Julia Lou
/// \date 26/03/2013 created
/// \class Obstacle

class FluidSystem;

class Obstacle
{
public:
    Obstacle(
            const ngl::Vec3 &_pos,
            const ngl::Colour &_colour,
            const ngl::Vec3 &_size,
            const std::string &_shaderName,
            const struct SimulationParams &_params,
            FluidSystem *_parent
            );

    /// @brief destructor
    virtual ~Obstacle();

    /// @brief draw the obstacle
    virtual void draw() const =0;

    /// @brief collide with a particle
    virtual void checkCollision(
                                Particle &_particle
                                )=0;

protected:
    /// @brief center position of the obstacle
    ngl::Vec3 m_pos;

    /// @brief colour
    ngl::Colour m_colour;

    /// @brief simulation scale
    float m_simScale;

    /// @brief elasticity
    float m_elasticity;

    /// @brief dimensions of the obstacle
    ngl::Vec3 m_size;

    /// @brief time step
    float m_timestep;

    /// @brief shader name
    std::string m_shaderName;

    /// @brief the parenting fluid system
    FluidSystem *m_parent;
};



#endif // OBSTACLE_H
