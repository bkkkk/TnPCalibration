#ifndef D3PDREADERADAPTER_ITRACK_HPP
#define D3PDREADERADAPTER_ITRACK_HPP 1

class ITrack {
public:  
  virtual ~ITrack() = default;
  
public:
  virtual double pt() const = 0;
  virtual double eta() const = 0;
  virtual double phi_wrtPV() const = 0;
  virtual double z0_wrtPV() const = 0;
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
  virtual double qoverp_wrtPV() const = 0;
};

#endif
