#ifndef TJPSITAGSELECTOR_CXX_
#define TJPSITAGSELECTOR_CXX_ 1

#include <TnPSelector/TJPsiTagSelector.h>
#include <TnPSelector/KinematicUtils.h>

#include <limits>
#include <math.h>

#ifdef __CINT__
ClassImp(TJPsiTagSelector);
#endif

TJPsiTagSelector::TJPsiTagSelector(const std::string& name)
 : name(name),
   etaCut(std::numeric_limits<float>::max()),
   combinedMuonCut(-1),
   ptCut(std::numeric_limits<float>::min()),
   d0Cut(std::numeric_limits<float>::max()),
   z0Cut(std::numeric_limits<float>::max()),
   d0SigCut(std::numeric_limits<float>::max()),
   z0SigCut(std::numeric_limits<float>::max()) {
 }

TJPsiTagSelector::~TJPsiTagSelector() {
}

int TJPsiTagSelector::initialize() {
  if(etaCut == std::numeric_limits<float>::max()) return 0;
  if(combinedMuonCut == -1) return 0;
  if(ptCut == std::numeric_limits<float>::min()) return 0;
  if(d0Cut == std::numeric_limits<float>::max()) return 0;
  if(z0Cut == std::numeric_limits<float>::max()) return 0;
  if(d0SigCut == std::numeric_limits<float>::max()) return 0;
  if(z0SigCut == std::numeric_limits<float>::max()) return 0;
  
  return (1);
}

int TJPsiTagSelector::accept(const IMuon& muon) {
  float d0 = muon.id_d0_exPV();
  float z0 = muon.id_z0_exPV();
  float d0Sig = TNP::CalculateSignificance(d0, muon.id_cov_d0_exPV());
  float z0Sig = TNP::CalculateSignificance(z0, muon.id_cov_z0_exPV());
  
  float theta = muon.id_theta();
  float eta = TNP::GetEta(theta);
  float pt = TNP::GetPt(muon.id_qoverp(), theta);

  return (accept(eta, muon.isCombinedMuon(), pt, d0, z0, d0Sig, z0Sig));
}

const int TJPsiTagSelector::accept(float eta, int combinedMuon, float pt,
                                   float d0, float z0,
                                   float d0Sig, float z0Sig) const {
  if(!passReconstructionCuts(pt, eta)) return 0;
  if(!passCombinedCut(combinedMuon)) return 0;
  if(!passIPCuts(d0, z0, d0Sig, z0Sig)) return 0;

  return (1);
}

int TJPsiTagSelector::finalize() {
  return (1);
}

#endif
