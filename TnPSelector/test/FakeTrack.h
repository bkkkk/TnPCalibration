#ifndef TNPSELECTOR_FAKETRACK_H_
#define TNPSELECTOR_FAKETRACK_H_ 1

#include <D3PDReaderAdapter/ITrack.h>
#include <cmath>

class FakeTrack : public ITrack {
public:
  FakeTrack() = default;

  static FakeTrack ConstructGoodProbe() {
    FakeTrack result;
    result.mPt = 3050;
    result.mEta = 0.5;
    result.mPhi_wrtPV = 0.4;
    result.mExpectBLayerHit = 1;
    result.mNBLHits = 1;
    result.mNPixHits = 1;
    result.mNPixelDeadSensors = 1;
    result.mNSCTHits = 3;
    result.mNSCTDeadSensors = 3;
    result.mNPixHoles = 1;
    result.mNSCTHoles = 2;
    result.mNTRTHits = 12;
    result.mNTRTOutliers = 1;
    result.mQoverp_wrtPV = -1;
    result.mZ0_wrtPV = 0.43;
    return result;
  }

  static FakeTrack ConstructBadProbe() {
    FakeTrack result;
    result.mPt = 2000;
    result.mEta = 2.7;
    result.mExpectBLayerHit = 0;
    return result;
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
  double x() const { return (fabs(mPt) * cos(mPhi_wrtPV)); }
  double y() const { return (fabs(mPt) * sin(mPhi_wrtPV)); }
  double z() const { return (fabs(mPt) / tan(2.0 * atan(exp(-mEta)))); }
  int charge() const { return (fabs(mQoverp_wrtPV) / mQoverp_wrtPV); }

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
