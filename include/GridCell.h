#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <cstdlib>
#include "Particle.h"

class GridCell
{
public:
    GridCell();

    inline void remove( Particle *_p) { m_cellParticles.remove(_p); }
    inline void add(Particle *_p ) { m_cellParticles.push_back(_p); }

    inline void getCell( std::list<Particle *> &o_cell ) const { o_cell = m_cellParticles; }

    inline void clear() { m_cellParticles.clear(); }

    inline int size() const { return m_cellParticles.size(); }

private:
    std::list<Particle *> m_cellParticles;
};

#endif // GRIDCELL_H
