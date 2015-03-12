#ifndef TJPSITAGSELECTOR_H_
#define TJPSITAGSELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuon.h>

class TJPsiTagSelector {
 public:
  TJPsiTagSelector();
  virtual ~TJPsiTagSelector();

 public:
  bool initialize() const;
  int accept(const IMuon& muon);
  int accept(float eta,
             int combinedMuon,
             float pt,
             float d0,
             float z0,
             float d0Sig,
             float z0Sig) const;

  bool passReconstructionCuts(float pt, float eta) const;

  bool passCombinedCut(bool isCombined) const;

  bool passIPCuts(float d0, float z0, float d0Sig, float z0Sig) const;
  int finalize() const;

 public:
  float etaCut;
  int combinedMuonCut;
  float trackMatchDrCut;
  float ptCut;
  float d0Cut;
  float z0Cut;
  float d0SigCut;
  float z0SigCut;

#ifdef __CINT__
  ClassDef(TJPsiTagSelector, 1);
#endif
};

#endif
