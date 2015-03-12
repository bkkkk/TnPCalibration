#ifndef TJPSIMUONPROBESELECTOR_H_
#define TJPSIMUONPROBESELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuons.h>
#include <D3PDReaderAdapter/ITracks.h>

class TJPsiMuonProbeSelector {
public:
  TJPsiMuonProbeSelector();

  virtual ~TJPsiMuonProbeSelector();

  int initialize();

  int accept(const ITrack& probe, const IMuons& muons,
             std::size_t& muonProbeIdx);

  int accept(float deltaR);

  int finalize();

private:
  unsigned findNearestMuonToProbe(const ITrack& probe, const IMuons& muons);

public:
  float deltaRCut;

#ifdef __CINT__
  ClassDef(TJPsiMuonProbeSelector, 1);
#endif
};

#endif
