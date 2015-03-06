#ifndef TNPSELECTOR_FAKETRACK_H_
#define TNPSELECTOR_FAKETRACK_H_ 1

#include <D3PDReaderAdapter/ITrack.h>

class FakeTrack : public ITrack {
public:
  FakeTrack() { }

  void constructGoodProbe() {
    mPt = 4000;
    mEta = 1.2;
    mExpectBLayerHit = 1;
    mNBLHits = 1;
    mNPixHits = 1;
    mNPixelDeadSensors = 1;
    mNSCTHits = 3;
    mNSCTDeadSensors = 3;
    mNPixHoles = 1;
    mNSCTHoles = 2;
    mNTRTHits = 12;
    mNTRTOutliers = 1;
  }

  void constructBadProbe() {
    mPt = 2000;
    mEta = 2.7;
    mExpectBLayerHit = 0;
  }

public:
  double pt() const { return (mPt); }
  double eta() const { return (mEta); }
  double phi_wrtPV() const { return (mPhi_wrtPV); }
  double z0_wrtPV() const { return (mZ0_wrtPV); }
  double expectBLayerHit() const { return (mExpectBLayerHit); }
  double nBLHits() const { return (mNBLHits); }
  double nPixHits() const { return (mNPixHits); }
  double nPixelDeadSensors() const { return (mNPixelDeadSensors); }
  double nSCTHits() const { return (mNSCTHits); }
  double nSCTDeadSensors() const { return (mNSCTDeadSensors); }
  double nPixHoles() const { return (mNPixHoles); }
  double nSCTHoles() const { return (mNSCTHoles); }
  double nTRTHits() const { return (mNTRTHits); }
  double nTRTOutliers() const { return (mNTRTOutliers); }
  double qoverp_wrtPV() const { return (mQoverp_wrtPV); }

public:
  float mPt;
  float mEta;
  float mPhi_wrtPV;
  float mZ0_wrtPV;
  float mExpectBLayerHit;
  float mNBLHits;
  float mNPixHits;
  float mNPixelDeadSensors;
  float mNSCTHits;
  float mNSCTDeadSensors;
  float mNPixHoles;
  float mNSCTHoles;
  float mNTRTHits;
  float mNTRTOutliers;
  float mQoverp_wrtPV;
};

#endif
