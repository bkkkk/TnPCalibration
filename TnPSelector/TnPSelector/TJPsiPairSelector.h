#ifndef TJPSIPAIRSELECTOR_H_
#define TJPSIPAIRSELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuon.h>
#include <D3PDReaderAdapter/ITrack.h>
#include <string>

class TJPsiPairSelector {
public:
  TJPsiPairSelector();
  virtual ~TJPsiPairSelector() = default;

  int initialize(void);

  int accept(const IMuon& tag, const IMuon& muonProbe);
  int accept(const IMuon& tag, const ITrack& probe);
  int accept(float deltaR, float sign, float invMass, float deltaZ0);
  int finalize();

  bool isInInvariantMassRange(float invariantMass) const;
  bool isInDeltaRRange(float deltaR) const;

public:
  float deltaRCutMax;
  float deltaRCutMin;
  float signCut;
  float minMassCut;
  float maxMassCut;
  float deltaZ0Cut;

#ifdef __CINT__
  ClassDef(TJPsiPairSelector, 1);
#endif
};

#endif
