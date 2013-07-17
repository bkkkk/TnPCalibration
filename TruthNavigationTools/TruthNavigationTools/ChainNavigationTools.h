#ifndef CHAIN_NAVIGATION_TOOLS_H_
#define CHAIN_NAVIGATION_TOOLS_H_ 1

// RC Packages
#include "TruthNavigationTools/TruthTools.h"
#include "D3PDReader/TruthParticleD3PDObject.h"

// C++
#include <string>
#include <vector>

namespace TT 
{

class ChainNavigationTools
{

private:
  // Collection of truth objects
  const D3PDReader::TruthParticleD3PDObject& sink;

public:
  // Ctor
  ChainNavigationTools(const D3PDReader::TruthParticleD3PDObject& mc);
  
public:
  // Dtor
  ~ChainNavigationTools() {
    
  }

public:
  // Print sibling chain
  void PrintSiblingChain(const size_t index, const siblingType type);

public:
  // Print parent chain
  void PrintParentChain(const size_t index);

public:
  // Print Child Chain
  void PrintChildChain(const size_t index);

public:
  // Prints all particles of type pdgId
  void PrintAllOfType(const int& pdgId);

public:
  // Returns the indecies of all mc particles with type
  std::vector<int> FindAllOfType(const int& pdgId);

public:
  // Prints all information about all MC particles
  void PrintAll();
};

}
#endif