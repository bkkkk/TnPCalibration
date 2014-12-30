#include <TnPSelector/TJPsiMuonProbeSelector.h>
#include <TnPSelector/KinematicUtils.h>
#include <TVector3.h>
#include <limits>

TJPsiMuonProbeSelector::TJPsiMuonProbeSelector(const std::string& val_name) {
}

TJPsiMuonProbeSelector::~TJPsiMuonProbeSelector() {
}

int TJPsiMuonProbeSelector::initialize(void) {
  return (1);
}

int TJPsiMuonProbeSelector::accept(const ITrack& probe, const IMuons& muons, int& muonProbeIdx) {
  float deltaR = std::numeric_limits<float>::max();

  // loop over all muons and find a candidate that is a combined muon
  // within deltaRCut
  for(int muon = 0; muon != muons.n(); muon++) {
    if(muons[muon].isCombinedMuon() != 1) continue;

    float deltaRCandidate = this->GetDeltaR(probe, muons[muon]);
        
    // Minimize deltaR
    if(deltaRCandidate < deltaR) {
      deltaR = deltaRCandidate;
      muonProbeIdx = muon;
    }
  }

  return (accept(deltaR));
}

float TJPsiMuonProbeSelector::GetDeltaR(const ITrack& probe, const IMuon& muon) {
  TLorentzVector probeVec = TNP::GetTrackVector(probe.pt(), probe.eta(),
                                                probe.phi_wrtPV());
    
  TLorentzVector muonVec = TNP::GetMuonVector(muon.pt(), muon.eta(),
                                              muon.phi(), muon.E());
    
  return (probeVec.DeltaR(muonVec));
}

int TJPsiMuonProbeSelector::accept(const float& deltaR) {
  if( deltaR > deltaRCut ) return (0);
  return (1);
}

int TJPsiMuonProbeSelector::finalize() {
  return (1);
}
