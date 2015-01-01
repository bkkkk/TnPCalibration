#ifndef TNPSELECTOR_FAKETRACK_H_
#define TNPSELECTOR_FAKETRACK_H_ 1

#include <D3PDReaderAdapter/ITrack.h>

class FakeTrack : public ITrack {
public:
  FakeTrack() { }

  void constructGoodProbe() {
    mPt = 4000;
    mEta = 1.2;
  }

  void constructBadProbe() {
    mPt = 2000;
    mEta = 2.7;
  }

public:
  const double pt() const { return (mPt); }
  const double eta() const { return (mEta); }
  const double phi_wrtPV() const { return (mPhi_wrtPV); }
  const double z0_wrtPV() const { return (mZ0_wrtPV); }
  const double expectBLayerHit() const { return (mExpectBLayerHit); }
  const double nBLHits() const { return (mNBLHits); }
  const double nPixHits() const { return (mNPixHits); }
  const double nPixelDeadSensors() const { return (mNPixelDeadSensors); }
  const double nSCTHits() const { return (mNSCTHits); }
  const double nSCTDeadSensors() const { return (mNSCTDeadSensors); }
  const double nPixHoles() const { return (mNPixHoles); }
  const double nSCTHoles() const { return (mNSCTHoles); }
  const double nTRTHits() const { return (mNTRTHits); }
  const double nTRTOutliers() const { return (mNTRTOutliers); }
  const double qoverp_wrtPV() const { return (mQoverp_wrtPV); }

private:
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
