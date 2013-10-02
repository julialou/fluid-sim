#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include "Cube.h"
#include "FluidSystem.h"

/// \file Cube.cpp
/// \brief Cube obstacle for fluids, concrete definition of abstract Obstacle
/// \author Julia Lou
/// \date 27/03/2013 tried to correct particles disappearing when projected to contact point
/// \class Cube

const ObstacleType Cube::m_type = CUBE;

Cube::Cube(
            const ngl::Vec3 &_pos,
            const ngl::Colour &_colour,
            const ngl::Vec3 _size,
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
  m_scalePos = m_pos * m_simScale;

  m_width = m_size.m_x;
  m_height = m_size.m_y;
  m_depth = m_size.m_z;


  m_scaleWidth = m_width * m_simScale;
  m_scaleHeight = m_height * m_simScale;
  m_scaleDepth = m_depth * m_simScale;

  m_scaleExtentWidth = (m_scaleWidth / 2.0);
  m_scaleExtentHeight = (m_scaleHeight / 2.0);
  m_scaleExtentDepth = (m_scaleDepth / 2.0);

}




//----------------------------------------------------------------------------------------------------------------------
Cube::~Cube()
{
}




//----------------------------------------------------------------------------------------------------------------------
void Cube::draw() const
{

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[m_shaderName]->use();
  shader->setShaderParam4f("Colour",m_colour.m_r,m_colour.m_g,m_colour.m_b,m_colour.m_a);

  m_parent->getTransformStack()->pushTransform();
  {
    m_parent->getTransformStack()->setPosition(m_pos);
    m_parent->getTransformStack()->setScale(m_size.m_x,m_size.m_y,m_size.m_z);
    ngl::Mat4 MVP=m_parent->getTransformStack()->getCurrAndGlobal().getMatrix()*m_parent->getCamera()->getVPMatrix();
    shader->setShaderParamFromMat4("MVP",MVP);
    // get an instance of the VBO primitives for drawing
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    // draw the cube
    prim->draw("cube");

  }
  m_parent->getTransformStack()->popTransform();
}






//----------------------------------------------------------------------------------------------------------------------
void Cube ::checkCollision(Particle &_particle)
{
  ngl::Vec3 testPos = _particle.getPos();
  // gets local position in simulation scale
  ngl::Vec3 localPos = testPos - m_scalePos;

  // implicit cube definition
  float x = fabs(localPos.m_x)-(m_scaleExtentWidth+EPSILON);
  float y = fabs(localPos.m_y)-(m_scaleExtentHeight+EPSILON);
  float z = fabs(localPos.m_z)-(m_scaleExtentDepth+EPSILON);

  float cubeFunc = std::max(x,y);
  cubeFunc = std::max(cubeFunc, z);

  // Collision = true
  if ( cubeFunc <= 0 )
  {
    //std::cout << "Cube collision " << std::endl;
    ngl::Vec3 contactLocal;

    contactLocal.m_x = std::min(m_scaleExtentWidth, std::max(-m_scaleExtentWidth, localPos.m_x));
    contactLocal.m_y = std::min(m_scaleExtentHeight, std::max(-m_scaleExtentHeight, localPos.m_y));
    contactLocal.m_z = std::min(m_scaleExtentDepth, std::max(-m_scaleExtentDepth, localPos.m_z));


    // contact point in world coordinates
    ngl::Vec3 contactPoint = contactLocal + m_scalePos;
    // penetration depth
    //float depth = temp.length();

    // calculate unit surface norma;
    ngl::Vec3 signum (Sign(contactLocal.m_x - localPos.m_x), Sign(contactLocal.m_y - localPos.m_y), Sign(contactLocal.m_z - localPos.m_z));
    //if (signum.len)
    ngl::Vec3 normal = signum/signum.length();

    //contactPoint = testPos + (depth * normal);

    // calculate projected position, velocity, and acceleration
    _particle.setPos(contactPoint);
    ngl::Vec3 velocity = _particle.getVelocity();
    velocity -= (1.0 + (m_elasticity))* (velocity.dot(normal)*normal);
    _particle.setCollisionVelocity(velocity);
  }


}
