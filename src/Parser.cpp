/// \file Parser.cpp
/// \brief Class to read in a config file and store parameters
/// \author Julia Lou
/// \date 26/03/2013

#include "Parser.h"






//----------------------------------------------------------------------------------------------------------------------
Parser::Parser()
{
}



//----------------------------------------------------------------------------------------------------------------------
Parser::Parser( const Parser &_parser)
{
    m_fluidSettings = _parser.m_fluidSettings;
    m_simSettings = _parser.m_simSettings;
}



//----------------------------------------------------------------------------------------------------------------------
Parser::Parser(const std::string _filename)
{
  m_simSettings.numParticles = c_defaultNumParticles;
  m_simSettings.containerDimensions = c_defaultContainerDimensions;
  m_simSettings.simScale = c_defaultSimScale;
  m_simSettings.timeStep = c_defaultTimeStep;
  m_simSettings.smoothRadius = c_defaultSmoothRadius;
  m_simSettings.elasticity = c_defaultElasticity;

  m_fluidSettings.restDensity = c_defaultRestDensity;
  m_fluidSettings.mass = c_defaultMass;
  m_fluidSettings.viscosity = c_defaultViscosity;
  m_fluidSettings.gasK = c_defaultGasK;
  m_fluidSettings.threshold = c_defaultThreshold;
  m_fluidSettings.tension = c_defaultTension;
  m_fluidSettings.size = c_defaultSize;
  m_fluidSettings.gravity = c_defaultGravity;

  m_mcSettings.isovalue = c_defaultIsovalue;
  m_mcSettings.voxelSize = c_defaultVoxelSize;
  m_mcSettings.blobRadius = c_defaultBlobRadius;
  m_mcSettings.isosurface = AVERAGED;

  std::fstream fileIn;
  const char * filename = _filename.c_str();
  fileIn.open(filename,std::ios::in);


  if( !fileIn.is_open() )
  {
    std::cout << "File: " << filename << "not found, exiting" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string lineBuffer;
  boost::char_separator<char> sep(" \t\r\n" );

  while( !fileIn.eof() )
  {
    getline(fileIn, lineBuffer, '\n');

    if( lineBuffer.size() != 0 )
    {
      tokenizer tokens(lineBuffer, sep);
      tokenizer::iterator first = tokens.begin();
      std::string firstToken = *first;
      ++first;

      if( firstToken == "NumParticles" )
      {
        m_simSettings.numParticles = boost::lexical_cast<int>(*first++);
        std::cout << "Parsed numParticles: " << m_simSettings.numParticles << std::endl;
      }
      else if( firstToken == "ContainerDimensions" )
      {
        m_simSettings.containerDimensions.m_x = boost::lexical_cast<float>(*first++);
        m_simSettings.containerDimensions.m_y = boost::lexical_cast<float>(*first++);
        m_simSettings.containerDimensions.m_z = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed ContainerDimensions" << m_simSettings.containerDimensions << std::endl;
      }
      else if( firstToken == "SimScale" )
      {
        m_simSettings.simScale = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed SimScale: "<< m_simSettings.simScale << std::endl;
      }
      else if( firstToken == "TimeStep" )
      {
        m_simSettings.timeStep = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed TimeStep: "<< m_simSettings.timeStep << std::endl;
      }
      else if( firstToken == "SmoothRadius" )
      {
        m_simSettings.smoothRadius = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed SmoothRadius: "<< m_simSettings.smoothRadius << std::endl;
      }
      else if( firstToken == "Elasticity" )
      {
        m_simSettings.elasticity = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Elasticity: "<< m_simSettings.elasticity << std::endl;
      }

      else if( firstToken == "RestDensity" )
      {
        m_fluidSettings.restDensity = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed RestDensity: "<< m_fluidSettings.restDensity << std::endl;
      }
      else if( firstToken == "Mass" )
      {
        m_fluidSettings.mass = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Mass: "<< m_fluidSettings.mass << std::endl;
      }
      else if( firstToken == "Viscosity" )
      {
        m_fluidSettings.viscosity = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Viscosity: "<< m_fluidSettings.viscosity << std::endl;
      }
      else if( firstToken == "GasK" )
      {
        m_fluidSettings.gasK = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed GasK: "<< m_fluidSettings.gasK << std::endl;
      }
      else if( firstToken == "Threshold" )
      {
        m_fluidSettings.threshold = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Threshold: "<< m_fluidSettings.threshold << std::endl;
      }
      else if( firstToken == "Tension" )
      {
        m_fluidSettings.tension = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Tension: "<< m_fluidSettings.tension << std::endl;
      }
      else if( firstToken == "ParticleSize" )
      {
        m_fluidSettings.size = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed ParticleSize: "<< m_fluidSettings.size << std::endl;
      }
      else if( firstToken == "Gravity" )
      {
        m_fluidSettings.gravity.m_x = boost::lexical_cast<float>(*first++);
        m_fluidSettings.gravity.m_y = boost::lexical_cast<float>(*first++);
        m_fluidSettings.gravity.m_z = boost::lexical_cast<float>(*first++);

        std::cout << "Parsed Gravity: "<< m_fluidSettings.gravity << std::endl;
      }
      else if( firstToken == "Isovalue" )
      {
        m_mcSettings.isovalue = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Isovalue: "<< m_mcSettings.isovalue << std::endl;
      }
      else if( firstToken == "VoxelSize" )
      {
        m_mcSettings.voxelSize = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Voxel Size: "<< m_mcSettings.voxelSize << std::endl;
      }
      else if( firstToken == "BlobRadius" )
      {
        m_mcSettings.blobRadius = boost::lexical_cast<float>(*first++);
        std::cout << "Parsed Blob Radius: "<< m_mcSettings.blobRadius << std::endl;
      }
      else
      {
        std::cout << "Invalid Token" << std::endl;
      }
    }
  }

  // don't need to check if all parameters were defined in text file since we already set defaults

  fileIn.close();

}


