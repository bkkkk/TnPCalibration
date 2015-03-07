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

  float GetInvariantMass(const IMuon& tag, const ITrack& probe);
  float GetInvariantMass(const IMuon& tag, const IMuon& mp);
  float GetInvariantMass(float x1, float y1, float z1, float t1,
                         float x2, float y2, float z2, float t2);

  float GetEta(const float theta);

  float GetPt(const float qoverp, const float theta);

  float GetDeltaZ0(const float first, const float second);

  float GetDeltaR(const IMuon& first, const IMuon& second);
  float GetDeltaR(const IMuon& muon, const ITrack& track);
  float GetDeltaR(const float firstEta, const float firstPhi,
                  const float secondEta, const float secondPhi );

  int GetChargeSign(int aCharge, int anotherCharge);

  float GetWrappedDeltaPhi(const float first, const float second);

  float CalculateSignificance(const float ip, const float cov);
};

#endif
