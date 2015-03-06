#include <TnPSelector/KinematicUtils.h>
#include <math.h>

TVector3 TNP::GetTrack3Vector (const ITrack& track) {
  return (GetTrack3Vector(track.pt(), track.eta(), track.phi_wrtPV()));
}

TVector3 TNP::GetTrack3Vector (const float pt, const float eta, const float phi) {
  TVector3 trackVector;
  trackVector.SetPtEtaPhi(pt, eta, phi);
  
  return (trackVector);
}

TLorentzVector TNP::GetTrackVector (const ITrack& track) {
  return (GetTrackVector(track.pt(), track.eta(), track.phi_wrtPV()));
}

TLorentzVector TNP::GetTrackVector(const float pt, const float eta, const float phi) {
  const double MuonMass = 105.6583715;
  
  TLorentzVector trackVector;
  trackVector.SetVectM(GetTrack3Vector(pt, eta, phi), MuonMass);

  return trackVector;
}

TLorentzVector TNP::GetMuonVector(const IMuon& muon) {
  return (TNP::GetMuonVector(muon.pt(), muon.eta(), muon.phi(), muon.E()));
}

TLorentzVector TNP::GetMuonVector(const float pt, const float eta, const float phi, const float E) {
  TLorentzVector muonVector;
  muonVector.SetPtEtaPhiE(pt, eta, phi, E);

  return (muonVector);
}

TVector3 TNP::GetMuon3Vector(const IMuon& muon) {
  return (TNP::GetMuon3Vector(muon.pt(), muon.eta(), muon.phi()));
}

TVector3 TNP::GetMuon3Vector(const float pt, const float eta, const float phi) {
  TVector3 muonVector;
  muonVector.SetPtEtaPhi(pt, eta, phi);

  return muonVector;
}

float TNP::GetInvariantMass(const ITrack& probe, const IMuon& tag) {
  TLorentzVector tagVector = TNP::GetMuonVector(tag);
  TLorentzVector probeVector = TNP::GetTrackVector(probe);

  return (GetInvariantMass(tagVector, probeVector));
}

float TNP::GetInvariantMass(const float trackpt, const float tracketa, const float trackphi,
                const float tagpt, const float tageta, const float tagphi, const float tagE) {

  TLorentzVector tag = TNP::GetMuonVector(tagpt, tageta, tagphi, tagE);
  TLorentzVector probe = TNP::GetTrackVector(trackpt, tracketa, trackphi);

  return (GetInvariantMass(tag, probe));
}

float TNP::GetInvariantMass(const TLorentzVector& first, const TLorentzVector& second) {
  TLorentzVector combined(first + second);

  return (combined.M());
}

float TNP::GetEta(const float theta) {
  if(theta == 0.0) {
    throw std::logic_error("Particle has infinite pseudorapidity");
  }

  return (-log(tan(theta/2)));
}

float TNP::GetPt(const float qoverp, const float theta) {
  if(qoverp == 0.0) {
    throw std::logic_error("This particle has zero momentum");
  }

  return (fabs(1 / qoverp) * sin(theta));
}

float TNP::GetDeltaZ0(const float first, const float second) {
  return (fabs(first - second));
}


float TNP::GetDeltaR(const float firstEta, const float firstPhi,
                     const float secondEta, const float secondPhi ) {
  float dPhi = GetWrappedDeltaPhi(firstPhi, secondPhi);
  float dEta = fabs(firstEta - secondEta);

  return (sqrt(dPhi*dPhi + dEta*dEta));
}


float TNP::GetWrappedDeltaPhi(const float first, const float second) {
  float dPhi = fabs(first - second);
  float dPhiWrapped = fabs(fabs(dPhi - M_PI) - M_PI);

  return dPhiWrapped;
}

float TNP::CalculateSignificance(const float ip, const float cov) {
  return (ip / cov);
}
