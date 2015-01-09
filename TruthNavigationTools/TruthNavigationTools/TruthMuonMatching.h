#ifndef TRUTH_MUON_MATCHING_H_
#define TRUTH_MUON_MATCHING_H_ 1

#include "D3PDReaderAdapter/ITracks.h"
#include "D3PDReaderAdapter/IMuons.h"
#include "D3PDReaderAdapter/ITruths.h"

#include <vector>

namespace TT {

class TruthMuonMatching {

private:
  const ITruths& mcRecords;
  std::vector<int> truthMuons;

public:
  float deltaRCut;

public:
  TruthMuonMatching(const ITruths& mc);  
  virtual ~TruthMuonMatching();

  int MatchMuonPair(const IMuon& tag, const IMuon& probe);

  int MatchMuon(const IMuon& muon, int& truthIndex);
  int MatchTrack(const ITrack& track, int& truthIndex);

  void SetAllTruthMuons();
};

}

#endif
