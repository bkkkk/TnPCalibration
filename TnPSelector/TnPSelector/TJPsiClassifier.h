#ifndef TJPSI_CLASSIFIER_H_
#define TJPSI_CLASSIFIER_H_ 1

#include <vector>
#include <utility>

#include "TnPSelector/TMCPSelector.h"
#include "TnPSelector/TJPsiPairSelector.h"
#include "TnPSelector/TJPsiProbeSelector.h"
#include "TnPSelector/TJPsiTagSelector.h"
#include "TnPSelector/TJPsiMuonProbeSelector.h"
#include "TnPSelector/TJPsiSMTSelector.h"

class TJPsiClassifier {
public:
  TJPsiClassifier();
  virtual ~TJPsiClassifier();

public:
  int initialize();

  int classify(const IMuons& muons, const ITracks& tracks);
  std::pair<int, int> classifyPairs(const IMuons& muons,
                                    const ITracks& tracks);

  void classifyTags(const IMuons& muons);
  bool isGoodMcpTag(const IMuon& muon);

  void classifyProbes(const ITracks& tracks);
  bool isGoodMcpProbe(const ITrack& track);

  void choosePair(const IMuons& muons, const ITracks& tracks);
  void setProbePassedLevel();

  int clear();

  inline int GetSelectedMuonProbe() { return (muonProbeIdx); }

  inline float GetDZ0 () { return (smallestDZ0); }

  inline const std::pair<int, int>& GetSelectedPair() {
    return(pair);
  }

  inline int GetSelectedProbe() {
    return (pair.second);
  }

  inline int GetMatchedMuonProbe() {
    return (muonProbeIdx);
  }

  inline int GetSelectedTag() {
    return (pair.first);
  }

  inline int IsPairMuonProbe() {
    return (isMuonProbe);
  }

  inline int IsPairSMT() {
    return (isSMT);
  }

  inline std::vector<int> getProbeIndexes() const {
    return (probesIndexes);
  }

  inline std::vector<int> getTagIndexes() const {
    return (tagsIndexes);
  }

public:  
  std::pair<int, int> pair;

  int isMuonProbe;
  int isSMT;

  int muonProbeIdx;

private:
  float smallestDZ0;

private:
  std::vector<int> probesIndexes;
  std::vector<int> tagsIndexes;

public:
  TMCPSelector* mcpSelector;
  TJPsiTagSelector* tagSelector;
  TJPsiPairSelector* pairSelector;
  TJPsiProbeSelector* probeSelector;
  TJPsiMuonProbeSelector* muonProbeSelector;
  TJPsiSMTSelector* smtSelector;

#ifdef __CINT__
  ClassDef(TJPsiClassifier,1)
#endif
};

#endif
