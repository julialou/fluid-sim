#ifndef COMMON_H
#define COMMON_H

#include <cstdlib>
#include <ngl/Vec3.h>

/// \file Common.h
/// \brief Header file for common definitions used throughout the system
/// \author Julia Lou
/// \date 26/03/2013



/// @brief debug flag
/// definition from Gianni at Stack Overflow
/// http://stackoverflow.com/questions/3371540/c-enable-disable-debug-messages-of-stdcouts-on-the-fly

#define DEBUG 0

#if DEBUG==1
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif


/// @brief error margin for collision tests
#define EPSILON 0.00001


/// @brief store parsed parameters for the system
struct SimulationParams {
  int numParticles;
  ngl::Vec3 containerDimensions;
  float simScale;
  float timeStep;
  float smoothRadius;
  float elasticity;
};

/// @brief store parsed parameters for fluid
struct FluidParams {
  float restDensity;
  float mass;
  float viscosity;
  float gasK;
  float threshold;
  float tension;
  float size;
  ngl::Vec3 gravity;
};


/// @brief store marching cubes parameters
struct MCubesParams {
    float voxelSize;
    float isovalue;
    float blobRadius;
    unsigned int isosurface;
};

enum DrawMode
{
    POINTS,
    DENSITY,
    SURFACE,
    VELOCITY,
    SPHEREMC
};

enum ObstacleType
{
    SPHERE,
    CUBE
};

enum Isosurface
{
    AVERAGED,
    METABALLS
};

template <class T > T Sign(T _a)
{
    if(_a < 0)
    {
        return -1;
    }
    else if (_a == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

#endif // COMMON_H
