#include "Obstacle.h"

/// \file Obstacle.cpp
/// \brief abstract obstacle for fluids
/// \author Julia Lou
/// \date 26/03/2013 created
/// \class Obstacle

//----------------------------------------------------------------------------------------------------------------------
Obstacle::Obstacle(
                    const ngl::Vec3 &_pos,
                    const ngl::Colour &_colour,
                    const ngl::Vec3 &_size,
                    const std::string &_shaderName,
                    const struct SimulationParams &_params,
                    FluidSystem *_parent
                    )
{
    m_pos = _pos;
    m_colour = _colour;
    m_shaderName = _shaderName;
    m_elasticity = _params.elasticity;
    m_simScale = _params.simScale;
    m_timestep = _params.timeStep;
    m_size = _size;
    m_parent = _parent;
}



//----------------------------------------------------------------------------------------------------------------------
Obstacle:: ~Obstacle()
{

}
