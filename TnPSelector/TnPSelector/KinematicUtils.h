#ifndef KINEMATICUTILS_H_
#define KINEMATICUTILS_H_ 1

#include <TLorentzVector.h>
#include <D3PDReaderAdapter/ITracks.h>
#include <D3PDReaderAdapter/IMuons.h>

namespace TNP {
  TVector3 GetTrack3Vector(const ITrack& track);
  TVector3 GetTrack3Vector(const float pt, const float eta, const float phi);
  
  TLorentzVector GetTrackVector(const ITrack& track);
  TLorentzVector GetTrackVector(const float pt, const float eta, const float phi);

  TLorentzVector GetMuonVector(const IMuon& muon);
  TLorentzVector GetMuonVector(const float pt, const float eta, const float phi, const float E);

  TVector3 GetMuon3Vector(const IMuon& muon);
  TVector3 GetMuon3Vector(const float pt, const float eta, const float phi);

  float GetInvariantMass(const ITrack& probe, const IMuon& tag);
  float GetInvariantMass(const float trackpt, const float tracketa, const float trackphi,
                         const float tagpt, const float tageta, const float tagphi, const float tagE);
  float GetInvariantMass(const TLorentzVector& first, const TLorentzVector& second);

  float GetEta(const float theta);

  float GetPt(const float qoverp, const float theta);

  float GetDeltaZ0(const float first, const float second);

  float GetDeltaR(const IMuon& first, const IMuon& second);
  float GetDeltaR(const float firstEta, const float firstPhi,
                  const float secondEta, const float secondPhi );

  float GetWrappedDeltaPhi(const float first, const float second);

  float CalculateSignificance(const float ip, const float cov);
};

#endif
