#include "FluidSystem.h"
#include "Sphere.h"
#include "Cube.h"

/// \file FluidSystem.cpp
/// \brief Class containing the fluid solver, including all particles
/// \author Julia Lou
/// \date 26/03/2013 Pressure corrected
/// \todo optimization and cleanup, velocity clamping?




//----------------------------------------------------------------------------------------------------------------------
FluidSystem::FluidSystem()
{

}



//----------------------------------------------------------------------------------------------------------------------
FluidSystem::FluidSystem(
                        const struct SimulationParams &_simParams,
                        const struct FluidParams &_fluidParams,
                        const struct MCubesParams &_mcubesParams,
                        const std::string &_shadername,
                        ngl::TransformStack *_transformStack
                        )
{
  // simulation properties
  m_numParticles = _simParams.numParticles;
  m_gridSize = _simParams.containerDimensions;
  m_timestep = _simParams.timeStep;
  m_h = _simParams.smoothRadius;
  m_h2 = m_h * m_h;
  m_fParams = _fluidParams;
  m_psize = _fluidParams.size;
  m_simScale = _simParams.simScale;
  m_transformStack = _transformStack;


  // fluid properties
  m_restdensity = _fluidParams.restDensity;
  m_threshold = _fluidParams.threshold;
  m_tension = _fluidParams.tension;
  m_gravity = _fluidParams.gravity;
  m_viscosity = _fluidParams.viscosity;
  m_gasK = _fluidParams.gasK;

  // marching cubes
  m_isovalue = _mcubesParams.isovalue;
  m_voxelSize = _mcubesParams.voxelSize;
  m_blobRadius = _mcubesParams.blobRadius;

  m_shaderName = _shadername;

  // precalculate kernel values for efficiency
  computeCoefficients();

  int count = 0;
  float space = _fluidParams.size;
  for (float py = -(m_gridSize.m_y*m_simScale)/2; py < (m_gridSize.m_y*m_simScale)/2; py += space)
  {
    for(float px = -(m_gridSize.m_x*m_simScale)/2; px<=0; px += space)
    {
      for(float pz = -(m_gridSize.m_z*m_simScale)/2 + 0.001; pz < (m_gridSize.m_z*m_simScale)/2 && count <m_numParticles; pz += space)
      {
        m_particleContainer.push_back(Particle(count, ngl::Vec3(px,py,pz), m_simScale, _fluidParams));
        ++count;
      }
    }
  }


  m_particleGrid = new Grid(m_gridSize.m_x, m_gridSize.m_y, m_gridSize.m_z, m_particleContainer, m_h, m_simScale);
  m_cubes = new MarchingCubes(m_voxelSize, m_blobRadius, m_isovalue, m_gridSize.m_x, m_gridSize.m_y, m_gridSize.m_z, m_simScale, m_particleContainer, _mcubesParams.isosurface);

  //m_cubes->computeMarchingCubes(m_isovalue, m_particleContainer);
}



//----------------------------------------------------------------------------------------------------------------------
FluidSystem::~FluidSystem()
{
  std::cout << "Fluid destroyed " << std::endl;
}



//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::reset(
                        const struct SimulationParams &_simParams,
                        const struct FluidParams &_fluidParams,
                        const struct MCubesParams &_mcubesParams
                        )
{
  m_particleContainer.clear();
  delete m_particleGrid;
  delete m_cubes;
  //m_obstacleContainer.clear();

  // simulation properties
  m_numParticles = _simParams.numParticles;
  m_gridSize = _simParams.containerDimensions;
  m_timestep = _simParams.timeStep;
  m_h = _simParams.smoothRadius;
  m_h2 = m_h * m_h;
  m_fParams = _fluidParams;
  m_psize = _fluidParams.size;
  m_simScale = _simParams.simScale;

  // fluid properties
  m_restdensity = _fluidParams.restDensity;
  m_threshold = _fluidParams.threshold;
  m_tension = _fluidParams.tension;
  m_gravity = _fluidParams.gravity;
  m_viscosity = _fluidParams.viscosity;
  m_gasK = _fluidParams.gasK;

  // marching cubes
  m_isovalue = _mcubesParams.isovalue;
  m_voxelSize = _mcubesParams.voxelSize;
  m_blobRadius = _mcubesParams.blobRadius;


  // precalculate coefficients for efficiency
  computeCoefficients();


  // x
  int count = 0;

  // this value was found through trial and error
  float space = _fluidParams.size;
  for (float py = -(m_gridSize.m_y*m_simScale)/2; py < (m_gridSize.m_y*m_simScale)/2 && count <m_numParticles; py += space)
  {
    for(float px = -(m_gridSize.m_x*m_simScale)/2; px<=0 && count <m_numParticles; px += space)
    {
      for(float pz = -(m_gridSize.m_z*m_simScale)/2 + 0.001; pz < (m_gridSize.m_z*m_simScale)/2 && count <m_numParticles; pz += space)
      {
        m_particleContainer.push_back(Particle(count, ngl::Vec3(px,py,pz), m_simScale, _fluidParams));
        ++count;
      }
    }
  }

  // prevent extra particles from existing if they can't fit
  if(count < m_numParticles)
  {
    m_numParticles = count;
  }

  m_particleGrid = new Grid(m_gridSize.m_x, m_gridSize.m_y, m_gridSize.m_z, m_particleContainer, m_h, m_simScale);
  m_cubes = new MarchingCubes(m_voxelSize, m_blobRadius, m_isovalue, m_gridSize.m_x, m_gridSize.m_y, m_gridSize.m_z, m_simScale, m_particleContainer, _mcubesParams.isosurface);
//m_cubes->computeMarchingCubes(m_isovalue, m_particleContainer);
}





//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::draw(DrawMode _mode, unsigned int _obstacleMode)
{
  glPolygonMode(GL_FRONT_AND_BACK,_obstacleMode);
  if(_mode == POINTS)
  {
    glBegin(GL_POINTS);
    //glColor3f(0.0f,1.0f,1.0f,1.0f);
    for(int i=0;i<m_numParticles;++i)
    {
      glColor3f(m_particleContainer[i].m_colour.m_r, m_particleContainer[i].m_colour.m_g, m_particleContainer[i].m_colour.m_b);
      ngl::Vec3 temp = m_particleContainer[i].getPos() / m_simScale;
      glVertex3f(temp.m_x, temp.m_y, temp.m_z);
    }
    glEnd();
  }
  else if(_mode == SPHEREMC)
  {

    m_cubes->computeMarchingCubes(m_isovalue, m_particleContainer);
    m_cubes->draw();

  }

  else {
    drawSpheres(_mode);
  }

  //glPolygonMode(GL_FRONT_AND_BACK,_obstacleMode);
  // draw obstacles
  std::vector<Obstacle*>::iterator it = m_obstacleContainer.begin();
  std::vector<Obstacle*>::iterator end = m_obstacleContainer.end();
  while(it != end)
  {
    (*it)->draw();
    ++it;
  }

}




//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::drawSpheres(DrawMode _mode)
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();
  (*shader)[m_shaderName]->use();

  for(int i=0; i<m_numParticles; ++i)
  {
    m_particleContainer[i].updateColour(_mode);
    shader->setShaderParam4f("Colour", m_particleContainer[i].m_colour.m_r, m_particleContainer[i].m_colour.m_g, m_particleContainer[i].m_colour.m_b, m_particleContainer[i].m_colour.m_a);

    m_transformStack->pushTransform();
    {
      m_transformStack->setPosition(m_particleContainer[i].m_pos/m_simScale);
      m_transformStack->setScale(0.5, 0.5, 0.5);
      ngl::Mat4 MVP = m_transformStack->getCurrAndGlobal().getMatrix() * m_cam->getVPMatrix();
      shader->setShaderParamFromMat4("MVP", MVP);


      prim->draw("sphere");
    }
    m_transformStack->popTransform();
  }

}




//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::createObstacle(
    ObstacleType _type,
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_size,
    const std::string &_shaderName,
    const SimulationParams &_params
    )
{
  // make sure we don't have too many obstacles
  if(m_obstacleContainer.size() + 1 < c_maxObstacles)
  {
    ngl::Colour obstacleColour = ngl::Colour(0,0.7,0.7);
    if( _type == SPHERE )
    {
      m_obstacleContainer.push_back(new Sphere(_pos, obstacleColour, _size, _shaderName, _params, this));
    }
    else if ( _type == CUBE )
    {
      m_obstacleContainer.push_back(new Cube(_pos, obstacleColour, _size, _shaderName, _params, this));
    }

  }
  else
  {
    std::cout << "Add Obstacle: Reached maximum number of obstacles" << std::endl;
  }

}



//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::removeObstacles()
{
  m_obstacleContainer.clear();
}


//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::updateFluid()
{

  // get neighbors and update density, pressure values
  for(int i=0;i<m_numParticles;++i)
  {
    std::vector<Particle*> neighbors;
    m_particleGrid->getNeighbors(m_particleContainer[i].getPos(), neighbors);
    m_particleContainer[i].updateNeighbors(neighbors);
    updateDensityPressure(m_particleContainer[i]);
  }

  // update forces
  for(int i=0;i<m_numParticles;++i)
  {
    updateInternalForces(m_particleContainer[i]);
    updateExternalForces(m_particleContainer[i]);
  }

  // advance particle with leapfrog integration, Grid
  for(int i=0; i<m_numParticles; ++i)
  {
    advanceParticle(m_particleContainer[i], m_timestep);


    // check for collisions
    std::vector<Obstacle*>::iterator it = m_obstacleContainer.begin();
    std::vector<Obstacle*>::iterator end = m_obstacleContainer.end();
    while(it != end)
    {
      (*it)->checkCollision(m_particleContainer[i]);
      ++it;
    }

    m_fbbox->BBoxCollide(m_particleContainer[i]);

    m_particleGrid->updatePCell(&(m_particleContainer[i]));
  }

}





//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::updateDensityPressure(Particle &io_particle)
{
  float ret_density = 0.0;
  std::vector<Particle*>::iterator it = io_particle.m_neighbors.begin();
  std::vector<Particle*>::iterator end = io_particle.m_neighbors.end();

  // compute new density
  while(it != end)
  {

    if( io_particle.m_id != (*it)->m_id )
    {
      ret_density += (*it)->m_mass * computeKernel(io_particle,*(*it));
    }

    ++it;
  }

  // prevent divide by zero errors
  if ( ret_density != 0.0 )
  {
    io_particle.m_density = ret_density;
  }
  else
  {
      io_particle.m_density = m_restdensity;
  }

  // ideal gas law (Muller)
  io_particle.m_pressure = m_gasK*(io_particle.m_density - m_restdensity);

  // Tait equation
  //m_pressure = (m_gasK * m_restdensity/7)*(pow(m_density/m_restdensity,7)-1);

  DEBUG_MSG(" Updating density/pressure for particle at  " +  boost::lexical_cast<std::string>(io_particle.m_pos) + " : return density is " + boost::lexical_cast<std::string>(io_particle.m_density) + " rest density is " + boost::lexical_cast<std::string>(m_restdensity) + " pressure is " + boost::lexical_cast<std::string>(io_particle.m_pressure));

}



//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::updateInternalForces(Particle &io_particle)
{
  // compute pressure force
  ngl::Vec3 viscosityForce(0,0,0);
  ngl::Vec3 pressureForce(0,0,0);
  std::vector<Particle*>::iterator it = io_particle.m_neighbors.begin();
  std::vector<Particle*>::iterator end = io_particle.m_neighbors.end();

  //if( !io_particle.m_neighbors.empty() )
  //{
    while(it != end)
    {
      // check the current particle is excluded
      if(io_particle.m_id != (*it)->m_id)
      {
        // Kelager 4.10
        pressureForce += ((io_particle.m_pressure/(io_particle.m_density * io_particle.m_density)) + ((*it)->m_pressure/((*it)->m_density * (*it)->m_density))) * (*it)->m_mass * computePressureGradient(io_particle, *(*it));

        viscosityForce += ((*it)->m_velocity - io_particle.m_velocity) * ((*it)->m_mass/(*it)->m_density) * computeViscosityLaplacian(io_particle, *(*it));

      }
      ++it;
    }
    pressureForce *= -io_particle.m_density;
    viscosityForce *= m_viscosity;
    DEBUG_MSG(" PRESSUREFORCE " +  boost::lexical_cast<std::string>(pressureForce));
  //}

  DEBUG_MSG(" VISCOSITY FORCE " +  boost::lexical_cast<std::string>(viscosityForce));


  io_particle.m_internalForce = pressureForce + viscosityForce;
}





//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::updateExternalForces(Particle &io_particle)
{
  ngl::Vec3 surfaceNormal(0,0,0);
  ngl::Vec3 surfForce(0,0,0);
  float colorLaplacian = 0.0;

  std::vector<Particle*>::iterator it = io_particle.m_neighbors.begin();
  std::vector<Particle*>::iterator end = io_particle.m_neighbors.end();

  io_particle.m_isSurface = false;

  // compute the surface normal to determine whether we need surface tension
  while( it != end )
  {
    float md = (*it)->m_mass/(*it)->m_density;
    surfaceNormal += md * computeDefaultGradient(io_particle, *(*it));
    colorLaplacian += md * computeDefaultLaplacian(io_particle, *(*it));

    ++it;
  }


  // compute surface tension force if is a surface particle
  if( surfaceNormal.length() >= m_threshold )
  {
    // save surface info & normal for marching cubes
    io_particle.m_isSurface = true;
    io_particle.m_surfaceNormal = -surfaceNormal;

    // set surface tension force
    surfForce = - m_tension * colorLaplacian * surfaceNormal/surfaceNormal.length();

  }

  ngl::Vec3 gravityForce = io_particle.m_density * m_gravity;

  // return gravity + surface tension force
  io_particle.m_externalForce = gravityForce + surfForce;
}



//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::advanceParticle(Particle &io_particle, float _dtime)
{
  // store the old position for the grid
  io_particle.m_oldpos = io_particle.m_pos;

  io_particle.m_acceleration = (io_particle.m_internalForce + io_particle.m_externalForce)/io_particle.m_density;

  // velocity at t = t - 0.5(timestep)
  io_particle.m_prevVelocity = io_particle.m_nextVelocity;

  // velocity at t = t + 0.5 (timestep)
  io_particle.m_nextVelocity = io_particle.m_prevVelocity + (_dtime * io_particle.m_acceleration);

  // clamp velocities
  float vtemp = io_particle.m_nextVelocity.length();
  if(vtemp > 24)
  {
    io_particle.m_nextVelocity /= vtemp;
  }

  // approximate velocity at t
  io_particle.m_velocity = (io_particle.m_prevVelocity + io_particle.m_nextVelocity)/2.0;

  // project position
  io_particle.m_pos = io_particle.m_pos + (_dtime * io_particle.m_nextVelocity);


  DEBUG_MSG(" UPDATE particle velocity:  " +  boost::lexical_cast<std::string>(io_particle.m_nextVelocity));
}


//----------------------------------------------------------------------------------------------------------------------
float FluidSystem::computeKernel(const Particle &_i, const Particle &_j)
{
  ngl::Vec3 vdist = _i.m_pos - _j.m_pos;
  float dist = vdist.length();

  if (( 0 <= dist ) &&
      ( dist <= m_h )
      )
  {
    return m_defaultKernelCoefficient * pow((m_h2)- (dist *dist),3);
  }
  else {
    return 0;
  }

}




//----------------------------------------------------------------------------------------------------------------------
// gradientW(r,h) = - 945/(32 * PI * h^9) * r * (h^2 - |r|^2)^2
ngl::Vec3 FluidSystem::computeDefaultGradient(const Particle &_i, const Particle &_j)
{
  ngl::Vec3 vdist = _i.m_pos - _j.m_pos;
  float dist = vdist.length();
  if(dist <= m_h) {
    return m_defaultGradientCoefficient * pow((m_h2) - (dist *dist),2) *  vdist;
  }
  else
  {
      return 0;
  }

}




//----------------------------------------------------------------------------------------------------------------------
// laplacianW(r,h) = -945/(32 * PI * h^9) * (h^2 - |r|^2) * (3 * h^2 - 7 * |r|^2)
float FluidSystem::computeDefaultLaplacian(const Particle &_i, const Particle &_j)
{
  ngl::Vec3 vdist = _i.m_pos - _j.m_pos;
  float dist = vdist.length();
  if(dist <= m_h) {
    float d2 = dist * dist;
    return m_defaultLaplacianCoefficient * (m_h2 - d2) * ((3 * m_h2) - (7 * d2));
  }
  else
  {
      return 0;
  }

}




//----------------------------------------------------------------------------------------------------------------------
// gradientWspiky(r,h) = -45/(PI * h^6) * (r/|r|) * (h - |r|)^2
ngl::Vec3 FluidSystem::computePressureGradient(const Particle &_i, const Particle &_j)
{
  ngl::Vec3 vdist = _i.m_pos - _j.m_pos;
  float dist = vdist.length();
  if( dist != 0 && ( dist <= m_h ) )
  {
    ngl::Vec3 result =  m_pressureGradientCoefficient * (vdist/dist) * (m_h - dist) * (m_h - dist);
    return result;
  }
  else
  {
    return ngl::Vec3(0,0,0);
  }
}




//----------------------------------------------------------------------------------------------------------------------
// (laplacian op)W(r,h) = (45/(PI * h^6)) * (h-r)
float FluidSystem::computeViscosityLaplacian(const Particle &_i, const Particle &_j)
{
  ngl::Vec3 vdist = _i.m_pos - _j.m_pos;
  float dist = vdist.length();
  if(dist <= m_h) {
    return m_viscosityLaplacianCoefficient * (m_h - dist);
  }
  else
  {
      return 0;
  }
}



//----------------------------------------------------------------------------------------------------------------------
void FluidSystem::computeCoefficients()
{
  m_defaultKernelCoefficient = 315.0/(64.0 * ngl::PI * pow(m_h, 9));
  m_defaultGradientCoefficient = - 945.0/(32.0 * ngl::PI * pow(m_h, 9));
  m_defaultLaplacianCoefficient = - 945.0/(32.0 * ngl::PI * pow(m_h, 9));
  m_pressureGradientCoefficient = - 45.0/(ngl::PI * pow(m_h,6));
  m_viscosityLaplacianCoefficient = 45/(ngl::PI * pow(m_h,6));
}
