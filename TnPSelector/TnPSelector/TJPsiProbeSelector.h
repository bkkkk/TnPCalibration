#ifndef TJPSIPROBESELECTOR_H_
#define TJPSIPROBESELECTOR_H_ 1

#include "D3PDReaderAdapter/ITrack.h"

class TJPsiProbeSelector {
 public:
  TJPsiProbeSelector();
  virtual ~TJPsiProbeSelector();

 public:
  int initialize();

  int accept(const ITrack& track);
  int accept(const float& eta, const float& p);

  int finalize();

 public:
  float etaCut;
  float pCut;

#ifdef __CINT__
  ClassDef(TJPsiProbeSelector, 1);
#endif
};

#endif
