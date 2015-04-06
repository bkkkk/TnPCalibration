#include <TruthNavigationTools/TruthTools.h>
#include <map>
#include <iostream>
#include <sstream>
#include <math.h>
#include <JacobUtils/LoggingUtility.h>

namespace TT {
std::string GetParticleName(const ITruth& truthParticle) {
  return (GetParticleName(truthParticle.pdgId()));
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
    return (IntToString(absPdgId));
  }
  
  return (particleName[absPdgId]);
}

std::string GetNameOfSibling(const siblingType type) {
  static std::string siblingTypeName[] = { "Parent", "Current", "Children" };
  return (siblingTypeName[type]);
}

std::string IntToString(const int num) {
  std::stringstream ss;
  ss << num;
  return (ss.str());
}

void PrintParticleInformation(const ITruth& truth, bool doWithSiblings) {
  PrintParticleKinematics(truth);
  if(doWithSiblings) PrintParticleAllSiblings(truth);
}

void PrintParticleKinematics(const ITruth& particle) {
  std::stringstream str;
  str << "-> " << particle.GetIndex();
  str << ": " << GetParticleName(particle.pdgId());
  str << " status: " << particle.status();
  str << " pt: " << particle.pt();
  str << " eta: " << particle.eta();

  // LOG_INFO() << str.str();
}

void PrintParticleAllSiblings(const ITruth& truth) {
  if(!HasParents(truth)) PrintParticleSiblings(TT::PARENT, truth.parents());
  if(!HasChildren(truth)) PrintParticleSiblings(TT::CHILD, truth.children());
}

bool HasParents(const ITruth& particle) {
  return (particle.parents().empty());
}

bool HasChildren(const ITruth& particle) {
  return (particle.children().empty());
}

void PrintParticleSiblings(const siblingType type, const std::vector<int>& siblings) {
  std::stringstream ss;

  for(size_t sibling = 0; sibling != siblings.size(); sibling++) {
    ss << siblings[sibling] << ", ";
  }
  (void) type;
  // LOG_INFO() << GetNameOfSibling(type) << ": " << ss.str();
}

}; // namespace
