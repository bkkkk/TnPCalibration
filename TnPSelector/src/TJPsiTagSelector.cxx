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

TJPsiTagSelector::~TJPsiTagSelector() {
}

bool TJPsiTagSelector::initialize() const {
  if (etaCut == std::numeric_limits<float>::max())
    return false;
  if (combinedMuonCut == -1)
    return false;
  if (ptCut == std::numeric_limits<float>::min())
    return false;
  if (d0Cut == std::numeric_limits<float>::max())
    return false;
  if (z0Cut == std::numeric_limits<float>::max())
    return false;
  if (d0SigCut == std::numeric_limits<float>::max())
    return false;
  if (z0SigCut == std::numeric_limits<float>::max())
    return false;

  return (true);
}

int TJPsiTagSelector::accept(const IMuon& muon) {
  auto d0 = muon.id_d0_exPV();
  auto z0 = muon.id_z0_exPV();
  auto d0Sig = TNP::CalculateSignificance(d0, muon.id_cov_d0_exPV());
  auto z0Sig = TNP::CalculateSignificance(z0, muon.id_cov_z0_exPV());
  auto theta = muon.id_theta();
  auto eta = TNP::GetEta(theta);
  auto pt = TNP::GetPt(muon.id_qoverp(), theta);

  return (accept(eta, muon.isCombinedMuon(), pt, d0, z0, d0Sig, z0Sig));
}

int TJPsiTagSelector::accept(float eta,
                             int combinedMuon,
                             float pt,
                             float d0,
                             float z0,
                             float d0Sig,
                             float z0Sig) const {
  if (!passReconstructionCuts(pt, eta))
    return 0;
  if (!passCombinedCut(combinedMuon))
    return 0;
  if (!passIPCuts(d0, z0, d0Sig, z0Sig))
    return 0;

  return (1);
}

bool TJPsiTagSelector::passReconstructionCuts(float pt, float eta) const {
  return (pt > ptCut && fabs(eta) < etaCut);
}

bool TJPsiTagSelector::passCombinedCut(bool isCombined) const {
  return (isCombined == combinedMuonCut);
}

bool TJPsiTagSelector::passIPCuts(float d0,
                                  float z0,
                                  float d0Sig,
                                  float z0Sig) const {
  if (fabs(d0) > d0Cut)
    return false;
  if (fabs(z0) > z0Cut)
    return false;
  if (fabs(z0Sig) > z0SigCut)
    return false;
  if (fabs(d0Sig) > d0SigCut)
    return false;

  return true;
}

int TJPsiTagSelector::finalize() const {
  return (1);
}

#endif
