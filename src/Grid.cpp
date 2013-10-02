#include <assert.h>
#include <math.h>
#include <boost/multi_array.hpp>
#include <ngl/Vec3.h>
#include "Grid.h"



/// \file Grid.cpp
/// \brief Class for uniform grid, stores neighbours for each cell
/// \author Julia Lou
/// \date 26/03/2013





//----------------------------------------------------------------------------------------------------------------------
Grid::Grid(){

}



//----------------------------------------------------------------------------------------------------------------------
Grid::Grid(
          const float _bbx,
          const float _bby,
          float _bbz,
          std::vector<Particle> &_pvector,
          const float _radius,
          const float _simScale
          )
{
  m_radius = _radius;

  // make sure that the radius is max the size of the smallest dimension
//  float minDim = std::min(_bbx,_bby);
//  minDim = std::min(minDim, _bbz);
//  if ( (minDim * _simScale) < m_radius )
//  {
//    m_radius = minDim*_simScale;
//    std::cout << "New radius is: " << m_radius << std::endl;
//  }

  m_sizeX = _bbx * _simScale;
  m_sizeY = _bby * _simScale;
  m_sizeZ = _bbz * _simScale;


  m_gridSizeX = ceil((_bbx * _simScale) / m_radius);
  m_gridSizeY = ceil((_bby * _simScale) / m_radius);
  m_gridSizeZ = ceil((_bbz * _simScale) / m_radius);



  m_grid = new GridCell[m_gridSizeX * m_gridSizeY * m_gridSizeZ];
  //m_allParticles = std::vector<Particle*>;

  std::cout << "Created Grid of size (" << m_gridSizeX << ", " << m_gridSizeY << ", " << m_gridSizeZ << ")" << std::endl;

  std::vector<Particle>::iterator it = _pvector.begin();
  std::vector<Particle>::iterator end = _pvector.end();

  // add all particles to the grid
  while(it!=end)
  {
    ngl::Vec3 temp = (*it).getPos();
    int idx = posToIndex(temp);
    m_grid[idx].add( &(*it++));
    DEBUG_MSG("Insert Grid IDX: " + idx);
    //m_allParticles.push_back(&(*it));
  }

}




//----------------------------------------------------------------------------------------------------------------------
Grid::~Grid()
{
    delete [] m_grid;
}



//----------------------------------------------------------------------------------------------------------------------
void Grid::getNeighbors(
                        const ngl::Vec3 &_pos,
                        std::vector <Particle*> &o_retVec
                        )
{
  std::vector<Particle*> retVec;



  //get x, y, z indices
  int idxX = (_pos.m_x + (m_sizeX/2.0))/m_radius;
  int idxY = (_pos.m_y + (m_sizeY/2.0))/m_radius;
  int idxZ = (_pos.m_z + (m_sizeZ/2.0))/m_radius;

  for (int cx=-1; cx<=1; ++cx)
  {
    for (int cy=-1; cy<=1; ++cy)
    {
      for (int cz=-1; cz<=1; ++cz)
      {
        // continue if this cell is out of bounds
        if((unsigned int)(idxX+cx) >= m_gridSizeX ||
           (unsigned int)(idxY+cy) >= m_gridSizeY ||
           (unsigned int)(idxZ+cz) >= m_gridSizeZ ||
           (idxX+cx) < 0 ||
           (idxY+cy) < 0 ||
           (idxZ+cz) < 0
           )
        {
          continue;
        }
        // otherwise add the elements of the cell to the vector
        else
        {
          int index = ((idxX+cx)*m_gridSizeY*m_gridSizeZ) + ((idxY+cy) * m_gridSizeZ) + (idxZ+cz);
          std::list<Particle*> cell;
          m_grid[index].getCell(cell);
          //std::vector<Particle*> temp (cell.begin(), (cell.end());
          retVec.insert(retVec.end(),cell.begin(),cell.end());
        }


      }
    }
  }


  o_retVec = retVec;

  DEBUG_MSG("Return: " + o_retVec.size());

}

//----------------------------------------------------------------------------------------------------------------------
void Grid::getCell(
              const ngl::Vec3 &_pos,
              std::vector <Particle*> &o_retVec
              ) const
{



    o_retVec.clear();
    int idx = posToIndex(_pos);
    std::list<Particle*> cell;
    m_grid[idx].getCell(cell);
    //std::vector<Particle*> temp (cell.begin(), (cell.end());
    o_retVec.insert(o_retVec.end(),cell.begin(),cell.end());
}



//----------------------------------------------------------------------------------------------------------------------
// update the cell a particle belongs to by removing its pointer from the old cell and adding it to the new one
void Grid::updatePCell(
                      Particle  *_particle
                      )
{
  ngl::Vec3 oldpos = _particle->getOldPos();
  ngl::Vec3 newpos = _particle->getPos();

  int idx = posToIndex(oldpos);
  m_grid[idx].remove(_particle);

  int nidx = posToIndex(newpos);
  m_grid[nidx].add(_particle);

}




//----------------------------------------------------------------------------------------------------------------------
// we divide by the radius so that the cells are the size of the smoothing radius
// divide gridsize/2 so that we start with the origin at the center of the grid
int Grid::posToIndex(
                      const ngl::Vec3 &_pos
                      )
                      const
{

  unsigned int x = (_pos.m_x + (m_sizeX/2.0))/m_radius;
  unsigned int y = (_pos.m_y + (m_sizeY/2.0))/m_radius;
  unsigned int z = (_pos.m_z + (m_sizeZ/2.0))/m_radius;

  return (x * m_gridSizeY * m_gridSizeZ)+ (y * m_gridSizeZ) + z;
}


