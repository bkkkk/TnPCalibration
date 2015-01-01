#ifndef D3PDREADERADAPTER_IMUON_HPP
#define D3PDREADERADAPTER_IMUON_HPP 1

class IMuon {
public:
  virtual ~IMuon() {}

public:
  virtual const double id_d0_exPV() const = 0;
  virtual const double id_z0_exPV() const = 0;
  virtual const double id_cov_d0_exPV() const = 0;
  virtual const double id_cov_z0_exPV() const = 0;
  virtual const double phi() const = 0;
  virtual const double E() const = 0;  
  virtual const double id_theta() const = 0;
  virtual const double eta() const = 0;
  virtual const double id_qoverp() const = 0;
  virtual const double pt() const = 0;
  virtual const bool isCombinedMuon() const = 0;
  virtual const double charge() const = 0;
  virtual const double etcone20() const = 0;
  virtual const double etcone30() const = 0;
  virtual const double etcone40() const = 0;
  virtual const double nucone20() const = 0;
  virtual const double nucone30() const = 0;
  virtual const double nucone40() const = 0;
  virtual const double ptcone20() const = 0;
  virtual const double ptcone30() const = 0;
  virtual const double ptcone40() const = 0;
  virtual const double expectBLayerHit() const = 0;
  virtual const double nBLHits() const = 0;
  virtual const double nPixHits() const = 0;
  virtual const double nPixelDeadSensors() const = 0;
  virtual const double nSCTHits() const = 0;
  virtual const double nSCTDeadSensors() const = 0;
  virtual const double nPixHoles() const = 0;
  virtual const double nSCTHoles() const = 0;
  virtual const double nTRTHits() const = 0;
  virtual const double nTRTOutliers() const = 0;
  virtual const double matchchi2() const = 0;
  virtual const double matchndof() const = 0;
};

#endif