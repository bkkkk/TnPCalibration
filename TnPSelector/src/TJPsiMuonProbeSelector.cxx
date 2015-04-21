#include <TnPSelector/TJPsiMuonProbeSelector.h>

#include <limits>
#include <iostream>
#include <string>

#include <TnPSelector/KinematicUtils.h>
#include "PhysicsTools/MatchResult.h"

TJPsiMuonProbeSelector::TJPsiMuonProbeSelector()
    : deltaRCut{std::numeric_limits<float>::max()} {}

int TJPsiMuonProbeSelector::initialize() {
  if (deltaRCut == std::numeric_limits<float>::max())
    return (0);

  return (1);
}

MatchResult<std::size_t> TJPsiMuonProbeSelector::accept(const ITrack& probe,
                                                        const IMuons& muons) {
  auto muonProbeIndex = findNearestMuonToProbe(probe, muons);

  auto result = MatchResult<std::size_t>{};
  if (!muonInRange(muonProbeIndex, muons.n())) {
    return (result);
  }

  auto deltaR = TNP::GetDeltaR(muons[muonProbeIndex], probe);
  if(!passesDeltaRCut(deltaR)) {
    return (result);
  }

  result.setFound(deltaR, muonProbeIndex);
  return (result);
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

bool TJPsiMuonProbeSelector::muonInRange(std::size_t index,
                                         std::size_t numberOfMuons) {
  return (index == numberOfMuons + 1);
}

bool TJPsiMuonProbeSelector::passesDeltaRCut(double deltaR) {
  return (deltaR < deltaRCut);
}

int TJPsiMuonProbeSelector::finalize() { return (1); }
