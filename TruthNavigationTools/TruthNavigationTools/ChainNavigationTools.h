#ifndef CHAIN_NAVIGATION_TOOLS_H_
#define CHAIN_NAVIGATION_TOOLS_H_ 1

#include "TruthNavigationTools/TruthTools.h"
#include "D3PDReaderAdapter/TruthParticleD3PDObject.h"

#include <string>
#include <vector>

namespace TT {
class ChainNavigationTools {

private:
  const ITruths& truthRecords;

public:
  ChainNavigationTools(const ITruths& mc);
  virtual ~ChainNavigationTools() { }

  void PrintSiblingChain(const size_t index, const siblingType type);
  void PrintParentChain(const size_t index);
  void PrintChildChain(const size_t index);
  void PrintAllOfType(const int& pdgId);
  std::vector<int> FindAllOfType(const int& pdgId);
  void PrintAll();
};
}

#endif
