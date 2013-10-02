#include "FluidBBox.h"

/// \file FluidBBox.cpp
/// \brief Bounding box for the fluid to collide with
/// \author Julia Lou
/// \date 08/05/2013 extra calculations removed




//----------------------------------------------------------------------------------------------------------------------

FluidBBox::FluidBBox()
{
  m_center = ngl::Vec3(0,0,0);
  m_width = 2.0;
  m_height = 2.0;
  m_depth = 2.0;
  m_drawMode = GL_LINE;
  m_vao = 0;
  setVAO();

  recalculate();
  recalcScaled();

}




//----------------------------------------------------------------------------------------------------------------------
FluidBBox::FluidBBox(
                    const struct SimulationParams &_params
                    )
{
    m_simScale = _params.simScale;
    m_center.set(0,0,0);
    m_width = _params.containerDimensions.m_x;
    m_height = _params.containerDimensions.m_y;
    m_depth = _params.containerDimensions.m_z;
    m_elasticity = _params.elasticity;
    m_timeStep = _params.timeStep;

    m_vao=0;
    setVAO();

    recalculate();
    recalcMinMax();
    recalcScaled();
    // from NGL::BBox

    // Setup the Plane Normals for Collision Detection
    m_norm[0].set(0.0f,1.0f,0.0f);
    m_norm[1].set(0.0f,-1.0f,0.0f);
    m_norm[2].set(1.0f,0.0f,0.0f);
    m_norm[3].set(-1.0f,0.0f,0.0f);
    m_norm[4].set(0.0f,0.0f,1.0f);
    m_norm[5].set(0.0f,0.0f,-1.0f);
    m_drawMode=GL_LINE;
}




//----------------------------------------------------------------------------------------------------------------------
// check for collision
void FluidBBox::BBoxCollide(
                            Particle &_particle
                            )
{
  bool collide = false;
  ngl::Vec3 pos = _particle.getPos();


  // contact point in world space
  ngl::Vec3 contactPt = pos;
  // normal to project along
  ngl::Vec3 sNormal(0,0,0);


  // collision with implicit bounding box
  // F(X) < 0 inside, F(X) = 0 on surface, F(X) > 0 outside
  if( pos.m_x < m_simScaleMinX+EPSILON)
  {
    contactPt.m_x = m_simScaleMinX+EPSILON;
    sNormal += m_norm[2];
    collide = true;
  }
  else if( pos.m_x > m_simScaleMaxX-EPSILON)
  {
    contactPt.m_x = m_simScaleMaxX-EPSILON;
    sNormal += m_norm[3];
    collide = true;
  }

  if( pos.m_y < m_simScaleMinY+EPSILON)
  {
    contactPt.m_y = m_simScaleMinY+EPSILON;
    sNormal += m_norm[0];
    collide = true;
  }
  else if( pos.m_y > m_simScaleMaxY-EPSILON)
  {
    contactPt.m_y = m_simScaleMaxY-EPSILON;
    sNormal += m_norm[1];
    collide = true;
  }

  if( pos.m_z < m_simScaleMinZ+EPSILON)
  {
    contactPt.m_z = m_simScaleMinZ+EPSILON;
    sNormal += m_norm[4];
    collide = true;
  }
  else if ( pos.m_z > m_simScaleMaxZ-EPSILON)
  {
    contactPt.m_z = m_simScaleMaxZ-EPSILON;
    sNormal += m_norm[5];
    collide = true;
  }

  // if we had a collision, calculate the new velocity and update it, and project the particle to the contact point. otherwise do nothing
  if( collide ) {
    DEBUG_MSG("COLLISION at " + contactPt + " particle pos at " + pos + " with surface normal " + sNormal);
    ngl::Vec3 tempDist = contactPt - pos;
    ngl::Vec3 velocity = _particle.getVelocity();

    velocity -= (1.0 + (m_elasticity * (tempDist.length()/(m_timeStep * velocity.length()))))* velocity.dot(sNormal)*sNormal;


    _particle.setPos(contactPt);
    _particle.setCollisionVelocity(velocity);

  }

}



//----------------------------------------------------------------------------------------------------------------------
void FluidBBox::resetBBox(
                          const SimulationParams &_params
                          )
{
    m_simScale = _params.simScale;
    m_center.set(0,0,0);
    m_width = _params.containerDimensions.m_x;
    m_height = _params.containerDimensions.m_y;
    m_depth = _params.containerDimensions.m_z;
    m_elasticity = _params.elasticity;

    m_vao=0;
    setVAO();

    recalculate();
    recalcMinMax();
    recalcScaled();
}



//----------------------------------------------------------------------------------------------------------------------
void FluidBBox::recalcMinMax()
{
  m_minX = m_center.m_x - m_width/2.0;
  m_maxX = m_center.m_x + m_width/2.0;
  m_minY = m_center.m_y - m_height/2.0;
  m_maxY = m_center.m_y + m_height/2.0;
  m_minZ = m_center.m_z - m_depth/2.0;
  m_maxZ = m_center.m_z + m_depth/2.0;
}



//----------------------------------------------------------------------------------------------------------------------
void FluidBBox::recalcScaled()
{
  m_simScaleMinX = m_minX * m_simScale;
  m_simScaleMinY = m_minY * m_simScale;
  m_simScaleMinZ = m_minZ * m_simScale;
  m_simScaleMaxX = m_maxX * m_simScale;
  m_simScaleMaxY = m_maxY * m_simScale;
  m_simScaleMaxZ = m_maxZ * m_simScale;
}
