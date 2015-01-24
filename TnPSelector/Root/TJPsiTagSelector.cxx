#ifndef TJPSITAGSELECTOR_CXX_
#define TJPSITAGSELECTOR_CXX_ 1

#include <TnPSelector/TJPsiTagSelector.h>
#include <TnPSelector/KinematicUtils.h>

#include <limits>
#include <math.h>

#ifdef __CINT__
ClassImp(TJPsiTagSelector);
#endif

TJPsiTagSelector::TJPsiTagSelector()
 : etaCut(std::numeric_limits<float>::max()),
   combinedMuonCut(-1),
   ptCut(std::numeric_limits<float>::min()),
   d0Cut(std::numeric_limits<float>::max()),
   z0Cut(std::numeric_limits<float>::max()),
   d0SigCut(std::numeric_limits<float>::max()),
   z0SigCut(std::numeric_limits<float>::max()) {
 }

TJPsiTagSelector::TJPsiTagSelector(const TagCuts& cuts)
  : etaCut(cuts.etaCut),
    combinedMuonCut(cuts.combinedMuonCut),
    ptCut(cuts.ptCut),
    d0Cut(cuts.d0Cut),
    z0Cut(cuts.z0Cut),
    d0SigCut(cuts.d0SigCut),
    z0SigCut(cuts.z0SigCut) { }

TJPsiTagSelector::~TJPsiTagSelector() {
}

const bool TJPsiTagSelector::initialize() const {
  if(etaCut == std::numeric_limits<float>::max()) return false;
  if(combinedMuonCut == -1) return false;
  if(ptCut == std::numeric_limits<float>::min()) return false;
  if(d0Cut == std::numeric_limits<float>::max()) return false;
  if(z0Cut == std::numeric_limits<float>::max()) return false;
  if(d0SigCut == std::numeric_limits<float>::max()) return false;
  if(z0SigCut == std::numeric_limits<float>::max()) return false;
  
  return (true);
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

const int TJPsiTagSelector::finalize() const {
  return (1);
}

#endif
