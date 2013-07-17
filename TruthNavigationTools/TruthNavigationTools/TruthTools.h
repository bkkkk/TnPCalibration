#ifndef TRUTH_TOOLS_H_
#define TRUTH_TOOLS_H_ 1

#include <string>
#include <vector>
#include "TruthNavigationTools/TruthEnums.h"
#include "D3PDReader/TruthParticleD3PDObject.h"

// A set of tools to work with Truth data from D3PDs
namespace TT
{
  // Returns the name of a particle given PDG ID
  std::string GetParticleName(const int& pdgid);

  // Returns the name of the particle given a TruthD3PDElement
  std::string GetParticleName(const D3PDReader::TruthParticleD3PDObjectElement& truthParticle);
  
  // Prints information about the truth particle given simple variables
  void PrintParticleInformation( const size_t& index,
                                 const int& pdgid,
                                 const int& status,
                                 const double& pt,
                                 const double& eta,
                                 const std::vector<int>& parents=std::vector<int>(),
                                 const std::vector<int>& children=std::vector<int>() );

  // Prints information about the truth particle
  // given a D3PDReader::TruthParticleD3PDObjectElement
  void PrintParticleInformation( const D3PDReader::TruthParticleD3PDObjectElement& truth,
                                 bool doWithSiblings=false );

  // Prints list of siblings given vector of sibling indecies
  void PrintParticleSiblings( const siblingType& type, 
                              const std::vector<int>& siblings );

  std::string GetNameOfSibling(const siblingType& type);

  
  // Convenience tool to convert int to string
  std::string IntToString( const int& num );
};

#endif