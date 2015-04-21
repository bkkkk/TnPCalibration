#ifndef TJPSIMUONPROBESELECTOR_H_
#define TJPSIMUONPROBESELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuons.h>
#include <D3PDReaderAdapter/ITracks.h>
#include "PhysicsTools/MatchResult.h"

class TJPsiMuonProbeSelector {
public:
  TJPsiMuonProbeSelector();

  ~TJPsiMuonProbeSelector() = default;

  int initialize();

  MatchResult<std::size_t> accept(const ITrack& probe, const IMuons& muons);

  int finalize();

private:
  unsigned findNearestMuonToProbe(const ITrack& probe, const IMuons& muons);
  bool muonInRange(std::size_t index, std::size_t numberOfMuons);
  bool passesDeltaRCut(double deltaR);

public:
  float deltaRCut;

#ifdef __CINT__
  ClassDef(TJPsiMuonProbeSelector, 1);
#endif
};

#endif
