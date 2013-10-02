#include <cstdlib>
#include <ngl/Random.h>
#include "GLWindow.h"
#include "Particle.h"

/// \file Particle.cpp
/// \brief Class defining individual particles
/// \author Julia Lou
/// \date 26/03/2013 drawing colours added
/// \todo optimization and cleanup, cleanup setting colours



//----------------------------------------------------------------------------------------------------------------------

Particle::Particle(int _idx, ngl::Vec3 _pos, float _simScale, const struct FluidParams &_params)
{
  m_id = _idx;
  m_oldpos = _pos;
  m_pos = _pos;
  m_simScale = _simScale;
  m_velocity = ngl::Vec3(0,0,0);
  m_acceleration = ngl::Vec3(4,0,0);
  m_pressure = 0.0;
  m_density = 0.0;
  m_restDensity = _params.restDensity;
  m_restDensity2 = 2 * m_restDensity;
  m_mass = _params.mass;
  m_size = _params.size;
  m_isSurface = false;
  m_surfaceNormal = ngl::Vec3(0,0,0);
  ngl::Random *rand = ngl::Random::instance();
  rand->setSeed(_idx);
  m_colour.set(rand->getRandomColour());


  // previous velocity calculated by Euler step as in Kelager
  m_prevVelocity = ngl::Vec3(0,0,0);
  m_nextVelocity = ngl::Vec3(0,0,0);

}

//----------------------------------------------------------------------------------------------------------------------
void Particle::updateColour(const DrawMode _mode)
{
    switch(_mode)
    {
        case DENSITY:
        {
            m_colour.set(0,0,1-fabs(m_density/m_restDensity2));
            break;
        }
        case SURFACE:
        {
            ngl::Random *rand = ngl::Random::instance();
            rand->setSeed(m_id);
            m_colour.set(rand->getRandomColour());

            if(m_isSurface)
            {
                m_colour.set(ngl::Colour(1,0,0));
            }
            else {
                m_colour.set (ngl::Colour(0.2, 0.2, 0.2));
            }
            break;
        }
        case VELOCITY:
        {
            float vel = m_velocity.length();
            m_colour.set(vel, vel, vel);
            break;
        }
        default:
        {
            ngl::Random *rand = ngl::Random::instance();
            rand->setSeed(m_id);
            m_colour.set(rand->getRandomColour());

            // no DEBUGASSERT here since _mode comes from user input and already has a default set in the GUI
        }
    }
}



//----------------------------------------------------------------------------------------------------------------------
ngl::Vec3 Particle::getPos() const
{
  return m_pos;
}


//----------------------------------------------------------------------------------------------------------------------
ngl::Vec3 Particle::getOldPos() const
{
  return m_oldpos;
}



//----------------------------------------------------------------------------------------------------------------------
ngl::Vec3 Particle::getVelocity() const
{
  //return m_nextVelocity;
  return m_velocity;
}




//----------------------------------------------------------------------------------------------------------------------
void Particle::setPos(const ngl::Vec3 &_pos)
{
  m_pos = _pos;
}


//----------------------------------------------------------------------------------------------------------------------
void Particle::setCollisionVelocity(
                                    const ngl::Vec3 &_velocity
                                    )
{
  m_nextVelocity = _velocity;
  m_velocity = (m_prevVelocity + m_nextVelocity)/2.0;
  //m_velocity = _velocity;
}



//----------------------------------------------------------------------------------------------------------------------
bool Particle::onSurface() const
{
    return m_isSurface;
}

//----------------------------------------------------------------------------------------------------------------------
void Particle::updateNeighbors(const std::vector <Particle*> &_neighbors)
{
  m_neighbors = _neighbors;
}



