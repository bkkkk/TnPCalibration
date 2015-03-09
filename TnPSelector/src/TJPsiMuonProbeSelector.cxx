#include <TnPSelector/TJPsiMuonProbeSelector.h>

#include <limits>
#include <iostream>
#include <string>

#include <TnPSelector/KinematicUtils.h>


TJPsiMuonProbeSelector::TJPsiMuonProbeSelector(const std::string& name)
    : deltaRCut(std::numeric_limits<float>::max()), name(name) {}

TJPsiMuonProbeSelector::~TJPsiMuonProbeSelector() {}

int TJPsiMuonProbeSelector::initialize() {
  if (deltaRCut == std::numeric_limits<float>::max())
    return (0);

  return (1);
}

int TJPsiMuonProbeSelector::accept(const ITrack& probe, const IMuons& muons,
                                   int& muonProbeIdx) {
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

  return (accept(deltaR));
}

int TJPsiMuonProbeSelector::accept(float deltaR) {
  if (deltaR > deltaRCut)
    return (0);
  return (1);
}

int TJPsiMuonProbeSelector::finalize() { return (1); }
