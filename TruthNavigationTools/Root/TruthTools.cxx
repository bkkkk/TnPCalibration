#include <TruthNavigationTools/TruthTools.h>
#include <map>
#include <iostream>
#include <sstream>
#include <math.h>
#include <JacobUtils/LoggingUtility.h>

namespace TT {
std::string GetParticleName(const ITruth& truthParticle) {
  return(GetParticleName(truthParticle.pdgId()));
}

std::string GetParticleName(const int& pdgid) {

  static std::map<int, std::string> particleName;

  particleName[DQUARK] = "d";
  particleName[UQUARK] = "u";
  particleName[SQUARK] = "s";
  particleName[CQUARK] = "c";
  particleName[BQUARK] = "b";
  particleName[TQUARK] = "t";
  particleName[ELECTRON] = "e";
  particleName[NUELECTRON] = "enu";
  particleName[MUON] = "mu";
  particleName[NUMUON] = "munu";
  particleName[TAU] = "tau";
  particleName[NUTAU] = "taunu";
  particleName[GLUON] = "g";
  particleName[PHOTON] = "pho";
  particleName[ZBOSON] = "Z";
  particleName[WPLUSBOSON] = "W";

  int absPdgId = fabs(pdgid);

  if (particleName.find(absPdgId) == particleName.end()) {
    return(IntToString(absPdgId));
  }
  
  return(particleName[absPdgId]);
}

std::string IntToString(const int& num) {
  std::stringstream ss;
  ss << num;
  return(ss.str());
}

void PrintParticleInformation(const ITruth& truth,
                              bool doWithSiblings) {
  if(doWithSiblings != 0) {
    PrintParticleInformation( truth.GetIndex(), truth.pdgId(), truth.status(),
                              truth.pt(), truth.eta(),
                              truth.parents(), truth.children() );
  } else {
    PrintParticleInformation( truth.GetIndex(), truth.pdgId(), truth.status(),
                              truth.pt(), truth.eta() );
  }

}

void PrintParticleInformation (const size_t& index,
                               const int& pdgid,
                               const int& status,
                               const double& pt,
                               const double& eta,
                               const std::vector<int>& parents,
                               const std::vector<int>& children) {
  // Print particle information
  LOG_INFO() << "-> " << index << ": " << GetParticleName(pdgid)
             << " status: " << status
             << " pt: " << pt
             << " eta: " << eta;

  // Print siblings information if given
  if(!parents.empty()) PrintParticleSiblings(TT::PARENT, parents);
  if(!children.empty()) PrintParticleSiblings(TT::CHILD, children);
}

void PrintParticleSiblings(const siblingType& type, const std::vector<int>& siblings) {
  std::stringstream ss;

  for(size_t sibling = 0; sibling != siblings.size(); sibling++) {
    ss << siblings[sibling] << ", ";
  }

  LOG_INFO() << GetNameOfSibling(type) << ": " << ss.str();
}

std::string GetNameOfSibling(const siblingType& type) {
  static std::string siblingTypeName[] = {"Parent", "Current", "Children" };
  return(siblingTypeName[type]);
}

}; // namespace
