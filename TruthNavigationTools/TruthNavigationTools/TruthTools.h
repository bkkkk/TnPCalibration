#ifndef TRUTH_TOOLS_H_
#define TRUTH_TOOLS_H_ 1

#include <string>
#include <vector>
#include "TruthNavigationTools/TruthEnums.h"
#include "D3PDReaderAdapter/ITruths.h"

namespace TT {
  std::string GetParticleName(const int& pdgid);
  std::string GetParticleName(const ITruth& truthParticle);
  
  bool HasParents(const ITruth& particle);
  bool HasChildren(const ITruth& particle);

  void PrintParticleKinematics(const ITruth& particle);
  
  void PrintParticleInformation(const ITruth& truth, bool doWithSiblings = false);

  void PrintParticleAllSiblings(const ITruth& truth);

  void PrintParticleSiblings(const siblingType type, const std::vector<int>& siblings);

  std::string GetNameOfSibling(const siblingType type);
  
  std::string IntToString(const int num);
};

#endif