#ifndef D3PDREADERADAPTER_IMUON_HPP
#define D3PDREADERADAPTER_IMUON_HPP 1

class IMuon {
public:
  virtual ~IMuon() {}

public:
  virtual double id_d0_exPV() const = 0;
  virtual double id_z0_exPV() const = 0;
  virtual double id_cov_d0_exPV() const = 0;
  virtual double id_cov_z0_exPV() const = 0;
  virtual double phi() const = 0;
  virtual double E() const = 0;  
  virtual double id_theta() const = 0;
  virtual double eta() const = 0;
  virtual double id_qoverp() const = 0;
  virtual double pt() const = 0;
  virtual bool isCombinedMuon() const = 0;
  virtual double charge() const = 0;
  virtual double etcone20() const = 0;
  virtual double etcone30() const = 0;
  virtual double etcone40() const = 0;
  virtual double nucone20() const = 0;
  virtual double nucone30() const = 0;
  virtual double nucone40() const = 0;
  virtual double ptcone20() const = 0;
  virtual double ptcone30() const = 0;
  virtual double ptcone40() const = 0;
  virtual double expectBLayerHit() const = 0;
  virtual double nBLHits() const = 0;
  virtual double nPixHits() const = 0;
  virtual double nPixelDeadSensors() const = 0;
  virtual double nSCTHits() const = 0;
  virtual double nSCTDeadSensors() const = 0;
  virtual double nPixHoles() const = 0;
  virtual double nSCTHoles() const = 0;
  virtual double nTRTHits() const = 0;
  virtual double nTRTOutliers() const = 0;
  virtual double matchchi2() const = 0;
  virtual double matchndof() const = 0;
};

#endif