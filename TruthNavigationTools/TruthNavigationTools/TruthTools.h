#ifndef TRUTH_TOOLS_H_
#define TRUTH_TOOLS_H_ 1

#include <string>
#include <vector>
#include "TruthNavigationTools/TruthEnums.h"
#include "D3PDReaderAdapter/ITruths.h"

namespace TT {
  std::string GetParticleName(const int& pdgid);

  std::string GetParticleName(const ITruth& truthParticle);
  
  void PrintParticleInformation(const size_t& index,
                                const int& pdgid,
                                const int& status,
                                const double& pt,
                                const double& eta,
                                const std::vector<int>& parents=std::vector<int>(),
                                const std::vector<int>& children=std::vector<int>() );

  void PrintParticleInformation(const ITruth& truth, bool doWithSiblings=false);

  void PrintParticleSiblings(const siblingType& type, const std::vector<int>& siblings);

  std::string GetNameOfSibling(const siblingType& type);
  
  std::string IntToString(const int& num);
};

#endif