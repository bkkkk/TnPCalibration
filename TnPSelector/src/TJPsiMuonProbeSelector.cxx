#include <TnPSelector/TJPsiMuonProbeSelector.h>
#include <TnPSelector/KinematicUtils.h>
#include <TVector3.h>
#include <limits>
#include <iostream>

TJPsiMuonProbeSelector::TJPsiMuonProbeSelector(const std::string& name)
 : deltaRCut(std::numeric_limits<float>::max())
 , name(name) {
}

TJPsiMuonProbeSelector::~TJPsiMuonProbeSelector() {
}

int TJPsiMuonProbeSelector::initialize(void) {
  if(deltaRCut == std::numeric_limits<float>::max()) return(0);

  return (1);
}

int TJPsiMuonProbeSelector::accept(const ITrack& probe, const IMuons& muons, int& muonProbeIdx) {
  float deltaR = std::numeric_limits<float>::max();

  for(auto muon = 0ul; muon != muons.n(); muon++) {
    if(muons[muon].isCombinedMuon() != 1) continue;

    float deltaRCandidate = TNP::GetDeltaR(muons[muon], probe);
        
    if(deltaRCandidate < deltaR) {
      deltaR = deltaRCandidate;
      muonProbeIdx = muon;
    }
  }

  return (accept(deltaR));
}
// MARK FOR DEMOLITION
float TJPsiMuonProbeSelector::GetDeltaR(const ITrack& probe, const IMuon& muon) {
  TLorentzVector probeVec = TNP::GetTrackVector(probe.pt(), probe.eta(),
                                                probe.phi_wrtPV());
    
  TLorentzVector muonVec = TNP::GetMuonVector(muon.pt(), muon.eta(),
                                              muon.phi(), muon.E());
    
  return (probeVec.DeltaR(muonVec));
}

int TJPsiMuonProbeSelector::accept(const float& deltaR) {
  if(deltaR > deltaRCut) return (0);
  return (1);
}

int TJPsiMuonProbeSelector::finalize() {
  return (1);
}
