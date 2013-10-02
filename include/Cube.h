#ifndef CUBE_H
#define CUBE_H

#include "Obstacle.h"

/// \file Cube.h
/// \brief Cube obstacle for fluids, concrete definition of abstract Obstacle
/// \author Julia Lou
/// \date 26/03/2013 created
/// \class Cube


class Cube : public Obstacle
{
public:
    /// @brief constructor
    /// @param[in] _pos center position of the cube in world coordinates
    /// @param[in] _colour color of the cube
    /// @param[in] _size dimension fo the cube
    /// @param[in] _shaderName shader to use
    /// @param[in] _params simulation parameters
    /// @param[in] _parent fluid system to which this obstacle belongs
    Cube(
        const ngl::Vec3 &_pos,
        const ngl::Colour &_colour,
        ngl::Vec3 _size,
        const std::string &_shaderName,
        const struct SimulationParams &_params,
        FluidSystem *_parent
        );

    /// @brief destructor
    virtual ~Cube();

    /// @brief draw the sphere
    virtual void draw() const;

    /// @brief collide with a particle
    /// @param[in] _particle the particle to check with
    virtual void checkCollision(
        Particle &_particle
        );

private:

    /// @brief sim scaled position
    ngl::Vec3 m_scalePos;

    /// @brief height
    float m_height;

    /// @brief width
    float m_width;

    /// @brief depth
    float m_depth;

    /// @brief scaled height
    float m_scaleHeight;

    /// @brief scaled width
    float m_scaleWidth;

    /// @brief scaled depth
    float m_scaleDepth;

    /// @brief scaled extent x
    float m_scaleExtentWidth;

    /// @brief scaled extent y
    float m_scaleExtentHeight;

    /// @brief scaled extent z
    float m_scaleExtentDepth;



    /// @brief type of obstacle
    const static ObstacleType m_type;

};

#endif // CUBE_H
