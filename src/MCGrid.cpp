#include "include/MCGrid.h"
#include <math.h>
#include <ngl/Vec3.h>

MCGrid::MCGrid()
{
}



/// \file MCGrid.cpp
/// \brief Class for marching cubes grid, stores neighbours for each cell
/// \author Julia Lou
/// \date 09/05/2013




//----------------------------------------------------------------------------------------------------------------------
MCGrid::MCGrid(
            const float _width,
            const float _height,
            const float _depth,
            std::vector<Particle> &_pvector,
            const float _voxelSize,
            const float _simScale
          )
{

  m_width = _width;
  m_height = _height;
  m_depth = _depth;

  m_gridSizeX = ceil(_width/_voxelSize);
  m_gridSizeY = ceil(_height/_voxelSize);
  m_gridSizeZ = ceil(_depth/_voxelSize);

  m_totalCells = m_gridSizeX * m_gridSizeY * m_gridSizeZ;

  m_voxelSize = _voxelSize;
  m_simScale = _simScale;



  m_grid = new GridCell[m_gridSizeX * m_gridSizeY * m_gridSizeZ];
  //m_allParticles = std::vector<Particle*>;

  std::cout << "Created MCGrid of size (" << m_gridSizeX << ", " << m_gridSizeY << ", " << m_gridSizeZ << ")" << std::endl;
  update(_pvector);

}




//----------------------------------------------------------------------------------------------------------------------
MCGrid::~MCGrid()
{
    delete [] m_grid;
}



//----------------------------------------------------------------------------------------------------------------------
void MCGrid::getNeighbors(
                        const ngl::Vec3 &_pos,
                        std::vector <Particle*> &o_retVec
                        )
{
  std::vector<Particle*> retVec;

  ngl::Vec3 drawPos = _pos;

  //get x, y, z indices
  int idxX = (drawPos.m_x + (m_width/2.0))/m_voxelSize;
  int idxY = (drawPos.m_y + (m_height/2.0))/m_voxelSize;
  int idxZ = (drawPos.m_z + (m_depth/2.0))/m_voxelSize;

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
void MCGrid::getCell(
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
void MCGrid::update(
              std::vector<Particle> &_pvector
                      )
{
  for(int i=0; i < m_totalCells; ++i)
  {
    m_grid[i].clear();
  }

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
int MCGrid::posToIndex(
                      const ngl::Vec3 &_pos
                      )
                      const
{

  ngl::Vec3 drawPos = _pos / m_simScale;
  unsigned int x = (drawPos.m_x + (m_width/2.0))/m_voxelSize;
  unsigned int y = (drawPos.m_y + (m_height/2.0))/m_voxelSize;
  unsigned int z = (drawPos.m_z + (m_depth/2.0))/m_voxelSize;

  return (x * m_gridSizeY * m_gridSizeZ)+ (y * m_gridSizeZ) + z;
}


