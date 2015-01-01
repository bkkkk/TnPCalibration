#ifndef D3PDREADERADAPTER_ITRACK_HPP
#define D3PDREADERADAPTER_ITRACK_HPP 1

class ITrack {
public:  
  virtual ~ITrack() { }
  
public:
  virtual const double pt() const = 0;
  virtual const double eta() const = 0;
  virtual const double phi_wrtPV() const = 0;
  virtual const double z0_wrtPV() const = 0;
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
  virtual const double qoverp_wrtPV() const = 0;
};

#endif
