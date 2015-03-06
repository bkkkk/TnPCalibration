#ifndef TMCPSELECTOR_H_
#define TMCPSELECTOR_H_ 1

#include <string>

#include <TString.h>

#include "D3PDReaderAdapter/IMuon.h"
#include "D3PDReaderAdapter/ITrack.h"

class TMCPSelector {
public:
  explicit TMCPSelector(const std::string& val_name="TMCPSelector");

public:
  virtual ~TMCPSelector (void);

  int initialize (void);
  int finalize (void);

  int accept(const IMuon& muon);
  int accept(const ITrack& track);
  int accept(int expectBLayerHit,
         int nBLHits,
         int nPixHits,
         int nPixelDeadSensors,
         int nSCTHits,
         int nSCTDeadSensors,
         int nPixHoles,
         int nSCTHoles,
         int nTRTHits,
         int nTRTOutliers,
         float eta);
public:
  std::string name;
  int expectBLayerHitCut;
  int nBLHitCut;
  int sumPixCut;
  int sumSctCut;
  int sumHolesCut;
  int sumTrtCut;

#ifdef __CINT__
  ClassDef(TMCPSelector,1);
#endif
};

#endif
