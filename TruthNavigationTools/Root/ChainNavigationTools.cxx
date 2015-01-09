#include <string>
#include <vector>
#include <iostream>

#include "TruthNavigationTools/ChainNavigationTools.h"

TT::ChainNavigationTools::ChainNavigationTools(const ITruths& mc)
 : truthRecords(mc) {
}

TT::ChainNavigationTools::~ChainNavigationTools() {
}

void TT::ChainNavigationTools::PrintParentChain(const size_t index) {
  TT::PrintParticleInformation(truthRecords[index], true);

  for(size_t parentIdx = 0; parentIdx != truthRecords[index].parent_index().size(); parentIdx++) {
    PrintParentChain(truthRecords[index].parent_index()[parentIdx]);
  }
}

void TT::ChainNavigationTools::PrintChildChain(const size_t index){
  TT::PrintParticleInformation(truthRecords[index], true);

  std::size_t nChildren = truthRecords[index].child_index().size();

  for(size_t childIdx = 0; childIdx != nChildren; childIdx++) {
    PrintChildChain(truthRecords[index].child_index()[childIdx]);
  }
}

void TT::ChainNavigationTools::PrintSiblingChain(const size_t index, const siblingType type) {    
  if(type == PARENT) {
    PrintParentChain(index);
  } else {
    PrintChildChain(index);
  }
}

void TT::ChainNavigationTools::PrintAllOfType(const int pdgId) {
  for(int mcIdx = 0; mcIdx != truthRecords.n(); mcIdx++) {
    if(IsParticleOfType(truthRecords[mcIdx], pdgId)) {
      TT::PrintParticleInformation(truthRecords[mcIdx]);
    }
  }
}

bool TT::ChainNavigationTools::IsParticleOfType(const ITruth& particle, const int pdgid) {
  int id  = particle.pdgId();
  return (id == pdgid || id == -pdgid);
}

std::vector<int> TT::ChainNavigationTools::FindAllOfType(const int pdgId) {
  std::vector<int> found;

  for(int mcIdx = 0; mcIdx != truthRecords.n(); mcIdx++) {
    if(truthRecords[mcIdx].pdgId() == pdgId || truthRecords[mcIdx].pdgId() == -pdgId ) {
      found.push_back(mcIdx);
    }
  }
  
  return (found);
}

void TT::ChainNavigationTools::PrintAll() {
  for(int mcIdx = 0; mcIdx!=truthRecords.n(); mcIdx++) {
    TT::PrintParticleInformation(truthRecords[mcIdx]);
  }
}
