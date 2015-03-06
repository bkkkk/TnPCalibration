#ifndef TNPSELECTOR_FAKEMUON_H_
#define TNPSELECTOR_FAKEMUON_H_ 1

#include <D3PDReaderAdapter/IMuon.h>

class FakeMuon : public IMuon {
public:
  static FakeMuon ConstructGoodTagMuon() {
    FakeMuon muon;
    muon.mId_d0_exPV = 0.3;
    muon.mId_z0_exPV = 0.5;
    muon.mId_cov_d0_exPV = 1;
    muon.mId_cov_z0_exPV = 1;
    muon.mId_theta = 0.5;
    muon.mId_qoverp = 0.0001;
    muon.mIsCombinedMuon = true;
    muon.mMatchchi2 = 6;
    muon.mMatchndof = 6;
    return (muon);
  }

  static FakeMuon ConstructBadTagMuon() {
    FakeMuon muon;
    muon.mId_d0_exPV = 100;
    muon.mId_z0_exPV = 100;
    muon.mId_cov_d0_exPV = 0.1; 
    muon.mId_cov_z0_exPV = 0.1;
    muon.mId_theta = 6.28;
    muon.mId_qoverp = 1;
    muon.mIsCombinedMuon = false;
    muon.mMatchchi2 = -999;
    muon.mMatchndof = -999;
    return (muon);
  }

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

  inline double id_d0_exPV() const { return mId_d0_exPV; }
  inline double id_z0_exPV() const { return mId_z0_exPV; }
  inline double id_cov_d0_exPV() const { return mId_cov_d0_exPV; }
  inline double id_cov_z0_exPV() const { return mId_cov_z0_exPV; }
  inline double id_theta() const { return mId_theta; }
  inline double id_qoverp() const { return mId_qoverp; }
  inline bool isCombinedMuon() const { return mIsCombinedMuon; }
  inline double phi() const { return mPhi; }
  inline double E() const { return mE; }
  inline double eta() const { return mEta; }
  inline double pt() const { return mPt; }
  inline double charge() const { return mCharge; }
  inline double etcone20() const { return mEtcone20; }
  inline double etcone30() const { return mEtcone30; }
  inline double etcone40() const { return mEtcone40; }
  inline double nucone20() const { return mNucone20; }
  inline double nucone30() const { return mNucone30; }
  inline double nucone40() const { return mNucone40; }
  inline double ptcone20() const { return mPtcone20; }
  inline double ptcone30() const { return mPtcone30; }
  inline double ptcone40() const { return mPtcone40; }
  inline double expectBLayerHit() const { return mExpectBLayerHit; }
  inline double nBLHits() const { return mNBLHits; }
  inline double nPixHits() const { return mNPixHits; }
  inline double nPixelDeadSensors() const { return mNPixelDeadSensors; }
  inline double nSCTHits() const { return mNSCTHits; }
  inline double nSCTDeadSensors() const { return mNSCTDeadSensors; }
  inline double nPixHoles() const { return mNPixHoles; }
  inline double nSCTHoles() const { return mNSCTHoles; }
  inline double nTRTHits() const { return mNTRTHits; }
  inline double nTRTOutliers() const { return mNTRTOutliers; }
  inline double matchchi2() const { return mMatchchi2; }
  inline double matchndof() const { return mMatchndof; }
  
public:
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
