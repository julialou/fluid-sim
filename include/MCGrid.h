#ifndef MCGRID_H
#define MCGRID_H

#include <cstdlib>
#include <ngl/Vec3.h>
#include "GridCell.h"
#include "Particle.h"


/// \file MCGrid.h
/// \brief Class for uniform grid, stores neighbours for each cell
/// \author Julia Lou
/// \date 09/05/2013 removed unneccessary methods

class MCGrid
{
public:
  /// @brief default constructor
  MCGrid();

  /// @brief constructor creates a grid defined by the bounding box dimensions
  /// @param[in] _width bounding box size x
  /// @param[in] _height bounding box size y
  /// @param[in] _depth bounding box size z
  /// @param[in] _pvector particle container
  /// @param[in] _voxelSize size of a voxel
  MCGrid(
      const float _width,
      const float _height,
      const float _depth,
      std::vector<Particle> &_pvector,
      const float _voxelSize,
      const float _simScale
      );


  /// @brief destructor
  ~MCGrid();


  /// @brief return vector of indices of neighbours using the position
  /// @param[in] _pos position to get neighbours around
  /// @param[out] o_retVec vector filled in with neighbours
  void getNeighbors(
                  const ngl::Vec3 &_pos,
                  std::vector <Particle*> &o_retVec
                  );

  /// @brief update the grid
  /// @param[in] _pvector particle container
  void update(
              std::vector<Particle> &_pvector
              );

  /// @brief retrieve a cell's contents using the position. for marching cubes
  /// @param[in] vec3 position around which we want the cell
  void getCell(
                const ngl::Vec3 &_pos,
                std::vector <Particle*> &o_retVec
                ) const;


private:

  /// @brief x dimension of the grid
  unsigned int m_gridSizeX;

  /// @brief y dimension of the grid
  unsigned int m_gridSizeY;

  /// @brief z dimension of the grid
  unsigned int m_gridSizeZ;

  /// @brief total # of cells
  unsigned int m_totalCells;

  /// @brief x dimension of the box
  float m_width;

  /// @brief y dimension of the box
  float m_height;

  /// @brief z dimension of the box
  float m_depth;

  /// @brief simulation scale
  float m_simScale;

  /// @brief voxel size
  float m_voxelSize;

  /// @brief array of cells
  GridCell *m_grid;

  /// @brief helper function turning a position to an index into the uniform grid
  int posToIndex(const ngl::Vec3 &_pos) const;


  // for testing purposes
  //std::vector<Particle*> m_allParticles;
};

#endif // MCGRID_H


