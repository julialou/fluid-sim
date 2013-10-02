#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include "FluidSystem.h"
#include "Sphere.h"

/// \file Sphere.cpp
/// \brief sphere obstacle for fluids, definition of abstract Obstacle
/// \author Julia Lou
/// \date 26/03/2013 created
/// \class Sphere

const ObstacleType Sphere::m_type = SPHERE;


//----------------------------------------------------------------------------------------------------------------------
Sphere::Sphere(
                const ngl::Vec3 &_pos,
                const ngl::Colour &_colour,
                const ngl::Vec3 &_size,
                const std::string &_shaderName,
                const SimulationParams &_params,
                FluidSystem *_parent
                ) :
                Obstacle(
                        _pos,
                        _colour,
                        _size,
                        _shaderName,
                        _params,
                        _parent
                        )
{
  m_radius = _size.m_x;

  m_scaleRadius = m_radius * m_simScale;
  m_scaleRadius2 = m_scaleRadius * m_scaleRadius;
  m_scalePos = m_pos * m_simScale;
}


//----------------------------------------------------------------------------------------------------------------------
Sphere::~Sphere()
{

}



//----------------------------------------------------------------------------------------------------------------------
void Sphere::draw() const
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[m_shaderName]->use();
  shader->setShaderParam4f("Colour",m_colour.m_r,m_colour.m_g,m_colour.m_b,m_colour.m_a);

  m_parent->getTransformStack()->pushTransform();
  {
    m_parent->getTransformStack()->setPosition(m_pos);
    m_parent->getTransformStack()->setScale(m_radius,m_radius,m_radius);
    ngl::Mat4 MVP=m_parent->getTransformStack()->getCurrAndGlobal().getMatrix()*m_parent->getCamera()->getVPMatrix();
    shader->setShaderParamFromMat4("MVP",MVP);
    // get an instance of the VBO primitives for drawing
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    // draw the sphere
    prim->draw("collisionSphere");

  }
  m_parent->getTransformStack()->popTransform();
}


//----------------------------------------------------------------------------------------------------------------------
void Sphere::checkCollision(
    Particle &_particle
    )
{

  ngl::Vec3 vdist = _particle.getPos() - m_scalePos;
  float dist = vdist.length();
  float sphereFunc = dist * dist - m_scaleRadius2;

  if(sphereFunc <= (0.00001) )
  {
    ngl::Vec3 contactPoint = m_scalePos + ((m_scaleRadius+4*EPSILON) * (vdist/dist));
    float depth = fabs(dist - m_scaleRadius);
    if (depth > 0.01)
    {
        depth = 0.01;
    }
    ngl::Vec3 normal = Sign(sphereFunc) * (vdist/dist);

    _particle.setPos(contactPoint);
    ngl::Vec3 velocity = _particle.getVelocity();
    velocity -= (1.0 + (m_elasticity*(depth/(m_timestep * velocity.length()))))* (velocity.dot(normal)*normal);
    // _particle.m_acceleration -= (1.0 + m_elasticity)* (_particle.m_acceleration.dot(normal)*normal);
    _particle.setCollisionVelocity(velocity);
  }
}
