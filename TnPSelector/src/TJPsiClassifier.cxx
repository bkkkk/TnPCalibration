#include <utility>

#include "TnPSelector/TJPsiClassifier.h"
#include "TnPSelector/KinematicUtils.h"

TJPsiClassifier::TJPsiClassifier()
    : pair{9999, -9999}, isMuonProbe{0}, isSMT{0}, muonProbeIdx{10000},
      smallestDZ0{1000}, mcpSelector{nullptr}, tagSelector{nullptr},
      pairSelector{nullptr}, probeSelector{nullptr}, muonProbeSelector{nullptr},
      smtSelector{nullptr} {}

TJPsiClassifier::~TJPsiClassifier() {
  if (mcpSelector)
    delete mcpSelector;
  if (tagSelector)
    delete tagSelector;
  if (pairSelector)
    delete pairSelector;
  if (probeSelector)
    delete probeSelector;
  if (muonProbeSelector)
    delete muonProbeSelector;
  if (smtSelector)
    delete smtSelector;
}

int TJPsiClassifier::initialize() {
  if (mcpSelector == nullptr) {
    return (0);
  }
  if (tagSelector == nullptr) {
    return (0);
  }
  if (pairSelector == nullptr) {
    return (0);
  }
  if (probeSelector == nullptr) {
    return (0);
  }
  if (muonProbeSelector == nullptr) {
    return (0);
  }
  if (smtSelector == nullptr) {
    return (0);
  }

  return (1);
}

int TJPsiClassifier::classify(const IMuons &muons, const ITracks &tracks) {
  clear();

  classifyTags(muons);
  classifyProbes(tracks);

  pair = classifyPairs(muons, tracks);

  if (smallestDZ0 == 1000.) {
    return 0;
  }

  auto matchResult = muonProbeSelector->accept(tracks[pair.second], muons);
  isMuonProbe = matchResult();

  if (isMuonProbe) {
    return (1);
  }

  isSMT = smtSelector->accept(muons[matchResult.getMatched()]);

  return (1);
}

std::pair<int, int> TJPsiClassifier::classifyPairs(const IMuons &muons,
                                                   const ITracks &tracks) {
  auto chosenTag = -99999;
  auto chosenProbe = -99999;

  for (const auto probeIdx : probesIndexes) {
    for (const auto tagIdx : tagsIndexes) {
      if (!isGoodPair(muons[tagIdx], tracks[probeIdx]))
        continue;

      auto trk_z0_wrtPV = tracks[probeIdx].z0_wrtPV();
      auto tag_id_z0_wrtPV = muons[tagIdx].id_z0_exPV();

      auto dz0 = TNP::GetDeltaZ0(trk_z0_wrtPV, tag_id_z0_wrtPV);

      if (smallestDZ0 > dz0) {
        smallestDZ0 = dz0;
        chosenTag = tagIdx;
        chosenProbe = probeIdx;
      }
    }
  }

  return (std::make_pair(chosenTag, chosenProbe));
}

bool TJPsiClassifier::isGoodPair(const IMuon &muon, const ITrack &track) {
  return (pairSelector->accept(muon, track) == 1);
}

void TJPsiClassifier::classifyTags(const IMuons &muons) {
  for (auto muon = 0ul; muon != muons.n(); muon++) {
    if (isGoodMcpTag(muons[muon])) {
      tagsIndexes.push_back(muon);
    }
  }
}

bool TJPsiClassifier::isGoodMcpTag(const IMuon &muon) {
  return (tagSelector->accept(muon) && mcpSelector->accept(muon));
}

void TJPsiClassifier::classifyProbes(const ITracks &tracks) {
  for (auto track = 0ul; track != tracks.n(); track++) {
    if (isGoodMcpProbe(tracks[track])) {
      probesIndexes.push_back(track);
    }
  }
}

bool TJPsiClassifier::isGoodMcpProbe(const ITrack &track) {
  return (probeSelector->accept(track) && mcpSelector->accept(track));
}

int TJPsiClassifier::clear() {
  isMuonProbe = 0;
  isSMT = 0;
  muonProbeIdx = -9999;
  tagsIndexes.clear();
  probesIndexes.clear();
  pair = std::make_pair(-9999, -9999);
  return (1);
}

#ifdef __CINT__
ClassImp(TJPsiClassifier)
#endif
