#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <ngl/Vec3.h>
#include "Common.h"

/// \file Parser.h
/// \brief Class to read in a config file and store parameters
/// \author Julia Lou
/// \date 26/03/2013


// typecast to tokenizer
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

/* Default fluid parameter settings in case they are not set in the config file */
/// @brief Default number of particles
const int c_defaultNumParticles = 200;

/// @brief Default container size
const ngl::Vec3 c_defaultContainerDimensions = ngl::Vec3(1,1,1);

/// @brief Default simulation scale
const float c_defaultSimScale = 0.1;

/// @brief Default time step
const float c_defaultTimeStep = 0.01;

/// @brief Default smoothing radius
const float c_defaultSmoothRadius = 0.08;


/// @brief Default elasticity
const float c_defaultElasticity = 0.2;

/** default fluid parameters **/

/// @brief Default rest density
const float c_defaultRestDensity = 60;

/// @brief Default particle mass
const float c_defaultMass = 0.02;

/// @brief Default viscosity
const float c_defaultViscosity = 3.5;

/// @brief Default stiffness
const float c_defaultGasK = 3.0;

/// @brief Default threshold for surface tension
const float c_defaultThreshold = 2.065;

/// @brief Default surface tension
const float c_defaultTension = 0.0728;

/// @brief Default particle size
const float c_defaultSize = 0.01;

/// @brief Default gravity acceleration
const ngl::Vec3 c_defaultGravity= ngl::Vec3(0,-9.8,0);

/** default marching cubes parameters **/
/// @brief default isovalue
const float c_defaultIsovalue = 0.05;

/// @brief default voxel size
const float c_defaultVoxelSize = 0.05;

/// @brief default metaball radius size
const float c_defaultBlobRadius = 0.1;


class Parser
{
public:
  /// @brief store parsed parameters for the fluid system
  struct FluidParams m_fluidSettings;

  /// @brief store parsed parameters for the simulation
  struct SimulationParams m_simSettings;


  /// @brief store parsed marching cubes parameters
  struct MCubesParams m_mcSettings;

public:
  /// @brief default constructor shouldn't do anything
  Parser();

  /// @brief copy constructor
  Parser(
        const Parser &_parser
        );

  /// @brief constructor takes a file and parses it, storing the read parameters in the structs
  Parser(
        const std::string filename
        );


private:


};

#endif // PARSER_H
