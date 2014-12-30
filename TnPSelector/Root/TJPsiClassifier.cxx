#include <TnPSelector/TJPsiClassifier.h>
#include <TnPSelector/KinematicUtils.h>

TJPsiClassifier::TJPsiClassifier(const std::string& val_name)
 : name(val_name),
   pair(std::make_pair(-9999, -9999)),
   isMuonProbe(0),
   isSMT(0),
   muonProbeIdx(10000),
   smallestDZ0(1000),
   mcpSelector(NULL),
   tagSelector(NULL),
   pairSelector(NULL),
   probeSelector(NULL),
   muonProbeSelector(NULL),
   smtSelector(NULL) { }

TJPsiClassifier::~TJPsiClassifier() {
}

int TJPsiClassifier::initialize(void) {
  if(mcpSelector == NULL) {
    return (0);
  }
  if(tagSelector == NULL) {
    return (0);
  }
  if(pairSelector == NULL) {
    return (0);
  }
  if(probeSelector == NULL) {
    return (0);
  }
  if(muonProbeSelector == NULL) {
    return (0);
  }
  if(smtSelector == NULL) {
    return (0);
  }

  return (1);
}

int TJPsiClassifier::classify(const IMuons& muons, const ITracks& tracks) {
  clear();

  int nMuons = muons.n();
  int nTracks = tracks.n();

  for (int muon = 0; muon != nMuons; muon++) {
    if(tagSelector->accept(muons[muon]) == 1 &&
       mcpSelector->accept(muons[muon]) == 1 ) {
      tagsIndexes.push_back(muon);
    }
  }

  for(int track = 0; track != nTracks; track++) {
    if( probeSelector->accept(tracks[track]) == 1 &&
        mcpSelector->accept(tracks[track]) == 1 ) {
      probesIndexes.push_back(track);
    }
  }

  smallestDZ0 = 1000.;
  int chosenTag = -9999;
  int chosenProbe = -9999;

  // Loop over probes
  std::vector<int>::iterator probeIdx = probesIndexes.begin();
  std::vector<int>::iterator probeLast = probesIndexes.end();
  for(; probeIdx != probeLast; probeIdx++) {
    // Loop over tag
    std::vector<int>::iterator tagIdx = tagsIndexes.begin();
    std::vector<int>::iterator tagLast = tagsIndexes.end();
    for(;tagIdx != tagLast; tagIdx++) {

      if( pairSelector->accept( muons[*tagIdx], tracks[*probeIdx] ) != 1) continue;

      float trk_z0_wrtPV = tracks[*probeIdx].z0_wrtPV();
      float tag_id_z0_wrtPV = muons[*tagIdx].id_z0_exPV();

      float dz0 = TNP::GetDeltaZ0(trk_z0_wrtPV, tag_id_z0_wrtPV);

      if(smallestDZ0 > dz0) {
        smallestDZ0 = dz0;
        chosenTag = *tagIdx;
        chosenProbe = *probeIdx;
      }
    }
  }

  if(smallestDZ0 == 1000.) {
    return 0;
  }

  pair = std::make_pair(chosenTag, chosenProbe);

  isMuonProbe = muonProbeSelector->accept(tracks[chosenProbe], muons, muonProbeIdx);
  
  if(isMuonProbe != 1) {
    return (1);
  }
  
  isSMT = smtSelector->accept(muons[muonProbeIdx]);

  return (1);
}

int TJPsiClassifier::clear(void) {
  isMuonProbe = 0;
  isSMT = 0;
  muonProbeIdx = -9999;
  tagsIndexes.clear();
  probesIndexes.clear();
  pair = std::make_pair(-9999,-9999);
  return (1);
}

const std::pair<int, int>& TJPsiClassifier::GetSelectedPair() {
  return(pair);
}

int TJPsiClassifier::GetSelectedProbe () {
  return (pair.second);
}

int TJPsiClassifier::GetMatchedMuonProbe () {
  return (muonProbeIdx);
}

int TJPsiClassifier::GetSelectedTag () {
  return (pair.first);
}

int TJPsiClassifier::IsPairMuonProbe (void) {
  return (isMuonProbe);
}

int TJPsiClassifier::IsPairSMT (void) {
  return (isSMT);
}

#ifdef __CINT__
ClassImp(TJPsiClassifier)
#endif
