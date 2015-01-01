#ifndef TNPSELECTOR_FAKEMUON_H_
#define TNPSELECTOR_FAKEMUON_H_ 1

#include <D3PDReaderAdapter/IMuon.h>

class FakeMuon : public IMuon {
public:
  FakeMuon()
   : mId_d0_exPV(-1),
     mId_z0_exPV(-1),
     mId_cov_d0_exPV(-1),
     mId_cov_z0_exPV(-1),
     mId_theta(-1),
     mId_qoverp(-1),
     mIsCombinedMuon(false),
     mPhi(-1),
     mE(-1),
     mEta(-1),
     mPt(-1),
     mCharge(-1),
     mEtcone20(-1),
     mEtcone30(-1),
     mEtcone40(-1),
     mNucone20(-1),
     mNucone30(-1),
     mNucone40(-1),
     mPtcone20(-1),
     mPtcone30(-1),
     mPtcone40(-1),
     mExpectBLayerHit(-1),
     mNBLHits(-1),
     mNPixHits(-1),
     mNPixelDeadSensors(-1),
     mNSCTHits(-1),
     mNSCTDeadSensors(-1),
     mNPixHoles(-1),
     mNSCTHoles(-1),
     mNTRTHits(-1),
     mNTRTOutliers(-1),
     mMatchchi2(-1),
     mMatchndof(-1) { }
  
  virtual ~FakeMuon() { }

  void constructGoodTagMuon() {
    mId_d0_exPV = 0.3;
    mId_z0_exPV = 0.5;
    mId_cov_d0_exPV = 1;
    mId_cov_z0_exPV = 1;
    mId_theta = 0.5;
    mId_qoverp = 0.0001;
    mIsCombinedMuon = true;
  }

  void constructBadTagMuon() {
    mId_d0_exPV = 100;
    mId_z0_exPV = 100;
    mId_cov_d0_exPV = 0.1; 
    mId_cov_z0_exPV = 0.1;
    mId_theta = 6.28;
    mId_qoverp = 1;
    mIsCombinedMuon = false;
  }

  inline const double id_d0_exPV() const { return mId_d0_exPV; }
  inline const double id_z0_exPV() const { return mId_z0_exPV; }
  inline const double id_cov_d0_exPV() const { return mId_cov_d0_exPV; }
  inline const double id_cov_z0_exPV() const { return mId_cov_z0_exPV; }
  inline const double id_theta() const { return mId_theta; }
  inline const double id_qoverp() const { return mId_qoverp; }
  inline const bool isCombinedMuon() const { return mIsCombinedMuon; }
  inline const double phi() const { return mPhi; }
  inline const double E() const { return mE; }
  inline const double eta() const { return mEta; }
  inline const double pt() const { return mPt; }
  inline const double charge() const { return mCharge; }
  inline const double etcone20() const { return mEtcone20; }
  inline const double etcone30() const { return mEtcone30; }
  inline const double etcone40() const { return mEtcone40; }
  inline const double nucone20() const { return mNucone20; }
  inline const double nucone30() const { return mNucone30; }
  inline const double nucone40() const { return mNucone40; }
  inline const double ptcone20() const { return mPtcone20; }
  inline const double ptcone30() const { return mPtcone30; }
  inline const double ptcone40() const { return mPtcone40; }
  inline const double expectBLayerHit() const { return mExpectBLayerHit; }
  inline const double nBLHits() const { return mNBLHits; }
  inline const double nPixHits() const { return mNPixHits; }
  inline const double nPixelDeadSensors() const { return mNPixelDeadSensors; }
  inline const double nSCTHits() const { return mNSCTHits; }
  inline const double nSCTDeadSensors() const { return mNSCTDeadSensors; }
  inline const double nPixHoles() const { return mNPixHoles; }
  inline const double nSCTHoles() const { return mNSCTHoles; }
  inline const double nTRTHits() const { return mNTRTHits; }
  inline const double nTRTOutliers() const { return mNTRTOutliers; }
  inline const double matchchi2() const { return mMatchchi2; }
  inline const double matchndof() const { return mMatchndof; }
  
private:
  double mId_d0_exPV;
  double mId_z0_exPV;
  double mId_cov_d0_exPV;
  double mId_cov_z0_exPV;
  double mId_theta;
  double mId_qoverp;
  bool mIsCombinedMuon;
  double mPhi;
  double mE;
  double mEta;
  double mPt;
  double mCharge;
  double mEtcone20;
  double mEtcone30;
  double mEtcone40;
  double mNucone20;
  double mNucone30;
  double mNucone40;
  double mPtcone20;
  double mPtcone30;
  double mPtcone40;
  double mExpectBLayerHit;
  double mNBLHits;
  double mNPixHits;
  double mNPixelDeadSensors;
  double mNSCTHits;
  double mNSCTDeadSensors;
  double mNPixHoles;
  double mNSCTHoles;
  double mNTRTHits;
  double mNTRTOutliers;
  double mMatchchi2;
  double mMatchndof;
};

#endif