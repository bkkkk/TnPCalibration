#include <limits>

#include "TruthNavigationTools/TruthMuonMatching.h"
#include "TruthNavigationTools/ChainNavigationTools.h"
#include "TnPSelector/KinematicUtils.h"

TT::TruthMuonMatching::TruthMuonMatching(const ITruths& mc)
 : mcRecords(mc)
 , deltaRCut(std::numeric_limits<float>::max()) {
}

TT::TruthMuonMatching::~TruthMuonMatching() {
}

void TT::TruthMuonMatching::SetAllTruthMuons() {
  TT::ChainNavigationTools navTools(mcRecords);
  truthMuons = navTools.FindAllOfType(TT::MUON);
}

int TT::TruthMuonMatching::MatchMuonPair(const IMuon& tag, const IMuon& probe) {
  int truthTagIndex = 0;
  int truthProbeIndex = 0;

  if(!MatchMuon(probe, truthProbeIndex) || !MatchMuon(tag, truthTagIndex))  {
    return (0);
  }

  if(truthTagIndex == truthProbeIndex) {
    return (0);
  }

  return (1);
}

int TT::TruthMuonMatching::MatchMuon(const IMuon& muon, int& truthIndex) {
  std::vector<int>::iterator goodMuon = truthMuons.begin();
  std::vector<int>::iterator lastItr = truthMuons.end();

  float minDeltaR = std::numeric_limits<float>::max();

  for(; goodMuon != lastItr; goodMuon++) {
    float trEta = mcRecords[*goodMuon].eta();
    float trPhi = mcRecords[*goodMuon].phi();

    float recoEta = muon.eta();
    float recoPhi = muon.phi();

    float deltaR = TNP::GetDeltaR(trEta, trPhi, recoEta, recoPhi);

    if(deltaR < minDeltaR) {
      minDeltaR = deltaR;
      truthIndex = *goodMuon;
    }
  }

  if(minDeltaR < deltaRCut) return (1);
  else return (0);
}

int TT::TruthMuonMatching::MatchTrack(const ITrack& track, int& truthIndex) {
  std::vector<int>::iterator goodMuon = truthMuons.begin();
  std::vector<int>::iterator lastItr = truthMuons.end();

  float minDeltaR = std::numeric_limits<float>::max();

  for(; goodMuon!=lastItr; goodMuon++) {
    float trEta = mcRecords[*goodMuon].eta();
    float trPhi = mcRecords[*goodMuon].phi();

    float recoEta = track.eta();
    float recoPhi = track.phi_wrtPV();

    float deltaR = TNP::GetDeltaR(trEta, trPhi, recoEta, recoPhi);

    if(deltaR < minDeltaR) {
      minDeltaR = deltaR;
      truthIndex = *goodMuon;
    }
  }

  if(minDeltaR < deltaRCut) return (1);
  else return (0);
}
