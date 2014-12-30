#ifndef D3PDREADERADAPTER_ITRIGMUONS_HPP
#define D3PDREADERADAPTER_ITRIGMUONS_HPP 1

#include <vector>

class ITrigMuon {
public:
  ITrigMuon();
  virtual ~ITrigMuon();

  virtual const bool EF_mu6_Trk_Jpsi_loose() const = 0;        
  virtual const bool EF_mu6() const = 0;
  virtual const bool EF_mu15() const = 0;
  virtual const bool EF_mu8() const = 0;
  virtual const bool EF_mu4T() const = 0;
  virtual std::vector<double> track_CB_eta() const = 0;
  virtual std::vector<double> track_CB_phi() const = 0;
};

class ITrigMuons {
public:
  ITrigMuons();
  virtual ~ITrigMuons();

  virtual const std::size_t n() const = 0;
  virtual std::size_t n() = 0;

  virtual const ITrigMuon& operator[](const std::size_t idx) const = 0;
  virtual ITrigMuon& operator[](const std::size_t idx) = 0;
};

#endif
