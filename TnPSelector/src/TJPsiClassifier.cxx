#include <TnPSelector/TJPsiClassifier.h>
#include <TnPSelector/KinematicUtils.h>

TJPsiClassifier::TJPsiClassifier()
 : pair(std::make_pair(-9999, -9999)),
   isMuonProbe(0),
   isSMT(0),
   muonProbeIdx(10000),
   smallestDZ0(1000),
   mcpSelector(nullptr),
   tagSelector(nullptr),
   pairSelector(nullptr),
   probeSelector(nullptr),
   muonProbeSelector(nullptr),
   smtSelector(nullptr) { }

TJPsiClassifier::~TJPsiClassifier() {
  if (mcpSelector) delete mcpSelector;
  if (tagSelector) delete tagSelector;
  if (pairSelector) delete pairSelector;
  if (probeSelector) delete probeSelector;
  if (muonProbeSelector) delete muonProbeSelector;
  if (smtSelector) delete smtSelector;
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

int TJPsiClassifier::classify(const IMuons& muons, const ITracks& tracks) {
  clear();

  classifyTags(muons);
  classifyProbes(tracks);

  auto chosenTag = -99999;
  auto chosenProbe = -99999;

  for(auto probeIdx = probesIndexes.begin(); probeIdx != probesIndexes.end(); probeIdx++) {
    for(auto tagIdx = tagsIndexes.begin(); tagIdx != tagsIndexes.end(); tagIdx++) {
      if (!pairSelector->accept(muons[*tagIdx], tracks[*probeIdx])) continue;

      auto trk_z0_wrtPV = tracks[*probeIdx].z0_wrtPV();
      auto tag_id_z0_wrtPV = muons[*tagIdx].id_z0_exPV();

      auto dz0 = TNP::GetDeltaZ0(trk_z0_wrtPV, tag_id_z0_wrtPV);

      if (smallestDZ0 > dz0) {
        smallestDZ0 = dz0;
        chosenTag = *tagIdx;
        chosenProbe = *probeIdx;
      }
    }
  }

  if (smallestDZ0 == 1000.) {
    return 0;
  }

  pair = std::make_pair(chosenTag, chosenProbe);

  isMuonProbe = muonProbeSelector->accept(tracks[chosenProbe], muons, muonProbeIdx);

  if (isMuonProbe != 1) {
    return (1);
  }

  isSMT = smtSelector->accept(muons[muonProbeIdx]);

  return (1);
}

void TJPsiClassifier::classifyTags(const IMuons& muons) {
  for (auto muon = 0ul; muon != muons.n(); muon++) {
    if (tagSelector->accept(muons[muon]) &&
        mcpSelector->accept(muons[muon])) {
      tagsIndexes.push_back(muon);
    }
  }
}

void TJPsiClassifier::classifyProbes(const ITracks& tracks) {
  for (auto track = 0ul; track != tracks.n(); track++) {
    if (probeSelector->accept(tracks[track]) == 1 &&
        mcpSelector->accept(tracks[track]) == 1) {
      probesIndexes.push_back(track);
    }
  }
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
