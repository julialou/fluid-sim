#ifndef GRID_H
#define GRID_H

#include <cstdlib>
#include <ngl/Vec3.h>
#include "GridCell.h"
#include "Particle.h"


/// \file Grid.h
/// \brief Class for uniform grid, stores neighbours for each cell
/// \author Julia Lou
/// \date 08/05/2013 removed unneccessary methods


class Grid
{
public:
  /// @brief default constructor
  Grid();

  /// @brief constructor creates a grid defined by the bounding box dimensions
  /// @param[in] _bbx bounding box size x
  /// @param[in] _bby bounding box size y
  /// @param[in] _bbz bounding box size z
  /// @param[in] _plist particle container
  /// @param[in] _radius smoothing radius
  /// @param[in] _simScale simulation scale
  Grid(
      const float _bbx,
      const float _bby,
      const float _bbz,
      std::vector<Particle> &_pvector,
      const float _radius,
      const float _simScale
      );


  /// @brief destructor
  ~Grid();


  /// @brief return vector of indices of neighbours using the position
  /// @param[in] _pos position to get neighbours around
  /// @param[out] o_retVec vector filled in with neighbours
  void getNeighbors(
                  const ngl::Vec3 &_pos,
                  std::vector <Particle*> &o_retVec
                  );

  /// @brief update the cell a particle belongs to
  /// @param[in] pointer to particle to update
  void updatePCell(
                  Particle  *_particle
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

  /// @brief x dimension of the box
  float m_sizeX;

  /// @brief y dimension of the box
  float m_sizeY;

  /// @brief z dimension of the box
  float m_sizeZ;



  /// @brief the smoothing radius, which determines the size of each cell, which is 2X the smoothing radius
  float m_radius;

  /// @brief array of cells
  GridCell *m_grid;

  /// @brief helper function turning a position to an index into the uniform grid
  int posToIndex(const ngl::Vec3 &_pos) const;


  // for testing purposes
  //std::vector<Particle*> m_allParticles;
};

#endif // GRID_H
