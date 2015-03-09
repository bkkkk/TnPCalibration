#include <TnPSelector/TJPsiMuonProbeSelector.h>

#include <limits>
#include <iostream>
#include <string>

#include <TnPSelector/KinematicUtils.h>

TJPsiMuonProbeSelector::TJPsiMuonProbeSelector()
    : deltaRCut{std::numeric_limits<float>::max()} {}

TJPsiMuonProbeSelector::~TJPsiMuonProbeSelector() {}

int TJPsiMuonProbeSelector::initialize() {
  if (deltaRCut == std::numeric_limits<float>::max())
    return (0);

  return (1);
}

int TJPsiMuonProbeSelector::accept(const ITrack& probe, const IMuons& muons,
                                   std::size_t& muonProbeIdx) {
  muonProbeIdx = findNearestMuonToProbe(probe, muons);
  if (muonProbeIdx == muons.n() + 1) {
    return (0);
  }

  auto deltaR = TNP::GetDeltaR(muons[muonProbeIdx], probe);

  return (accept(deltaR));
}

unsigned TJPsiMuonProbeSelector::findNearestMuonToProbe(const ITrack& probe,
                                                        const IMuons& muons) {
  auto muonProbeIdx = muons.n() + 1;
  auto deltaR = std::numeric_limits<float>::max();

  for (auto muon = 0ul; muon != muons.n(); muon++) {
    if (muons[muon].isCombinedMuon() != 1)
      continue;

    auto pairDeltaR = TNP::GetDeltaR(muons[muon], probe);

    if (pairDeltaR < deltaR) {
      deltaR = pairDeltaR;
      muonProbeIdx = muon;
    }
  }

  return (muonProbeIdx);
}

int TJPsiMuonProbeSelector::accept(float deltaR) {
  if (deltaR > deltaRCut)
    return (0);
  return (1);
}

int TJPsiMuonProbeSelector::finalize() { return (1); }
