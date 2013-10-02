#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H

#include <ngl/Util.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Vec3.h>
#include "MCGrid.h"
#include "Particle.h"

/// \file MarchingCubes.h
/// \brief Header file for common definitions used throughout the system
/// \author Julia Lou
/// \date 10/05/2013 clean up
/// \todo work on getting rid of repeated vertices, optimizations, clean up

class MarchingCubes
{
struct vertData
{
  GLfloat u;
  GLfloat v;
  GLfloat nx;
  GLfloat ny;
  GLfloat nz;
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

typedef struct {
    ngl::Vec3 p[3];
} MC_Triangle;

    /// @brief p[8] is an array of the vertices of the voxels
    /// val[8] is the value of the scalar field at the vertices
    /// m_pos is the position of the furthest left, bottom vertex (0)
typedef struct {
    ngl::Vec3 p[8];
    double val[8];
    ngl::Vec3 m_pos;
} Voxel;

public:

    /// @brief default ctor
    MarchingCubes();

    /// @brief constructor
    MarchingCubes(
            float _voxelSize,
            float _blobRadius,
            float _isovalue,
            float _width,
            float _height,
            float _depth,
            float _simScale,
            std::vector<Particle> &_particles,
            unsigned int _isosurface
            );

    /// @brief destructor
    ~MarchingCubes();

    /// @brief draw the marching cubes surface
    void draw();

    /// @brief compute an isosurface from the particles
    void computeMarchingCubes(double _isolevel,
            std::vector<Particle> &_particles
            );

    /// @brief function from Paul Bourke
    /// Available from http://paulbourke.net/geometry/polygonise/
    int Polygonise(
            Voxel &grid,
            MC_Triangle *triangles
            );



    /// @brief based on Marching cubes definitions by Paul Bourke (1994)
    /// http://paulbourke.net/geometry/polygonise/
    /// Linearly interpolate the position where an isosurface cuts an edge between two vertices
    /// prevents interpolation on boundaries to avoid gaps
    ngl::Vec3 VertexInterp(
            ngl::Vec3 p1,
            ngl::Vec3 p2,
            double valp1,
            double valp2
            );

    /// @brief compute the values of the scalar field at the vertex
    float vertexValue(
            const ngl::Vec3 _pos
            );

    /// @brief update a voxel with the new scalar values
    void updateVoxel(
            Voxel &io_voxel
            );



private:
    /// @brief contain normals
    std::vector<ngl::Vec3> m_normals;

    /// @brief array of Voxels for the volume grid
    Voxel *m_volumeGrid;

    /// @brief container storing all triangles
    std::vector <MC_Triangle> m_triangleContainer;

    /// @brief Grid storing the particles
    MCGrid *m_particleGrid;

    /// @brief number of Voxels in X
    int m_dimX;

    /// @brief number of Voxels in Y
    int m_dimY;

    /// @brief number of Voxels in Z
    int m_dimZ;

    /// @brief x Extents
    float m_xExtent;

    /// @brief y Extents
    float m_yExtent;

    /// @brief z Extents
    float m_zExtent;

    /// @brief size of each voxel
    float m_voxelSize;

    /// @brief blobby radius
    float m_radius;

    /// @brief radius^2 so we don't have to keep calculating it
    float m_rad2;

    /// @brief simulation scale
    float m_simScale;

    /// @brief isolevel
    float m_isolevel;

    /// @brief surfacing method
    unsigned int m_isosurface;


    /// @brief Kernel function from Bridson & Zhu
    float bKernel(float _s);


    ngl::VertexArrayObject *m_vao;


};

#endif // MARCHINGCUBES_H
