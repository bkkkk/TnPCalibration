#include <TnPSelector/KinematicUtils.h>
#include <JacobUtils/LoggingUtility.h>

#define _USE_MATH_DEFINES
#include <math.h>

TVector3 TNP::GetTrack3Vector (const float pt, const float eta, const float phi) {
	TVector3 trackVector;
	trackVector.SetPtEtaPhi( pt, eta, phi );
	
  return trackVector;
}

TLorentzVector TNP::GetTrackVector(const float pt, const float eta, const float phi) {
	TLorentzVector tempVector;

  const double muonMass = 105.6583715;
	tempVector.SetVectM(GetTrack3Vector(pt, eta, phi), muonMass);

	TLorentzVector trackVector;
	trackVector.SetPtEtaPhiE( pt, eta, phi, tempVector.E() );

	return trackVector;
}


TLorentzVector TNP::GetMuonVector(const float pt, const float eta, const float phi, const float E) {
	TLorentzVector muonVector;
	muonVector.SetPtEtaPhiE(pt, eta, phi, E);

	return muonVector;
}

TVector3 TNP::GetMuon3Vector(const float pt, const float eta, const float phi) {
	TVector3 muonVector;
	muonVector.SetPtEtaPhi(pt, eta, phi);

	return muonVector;
}

float TNP::GetInvariantMass(const float trackpt, const float tracketa, const float trackphi,
						    const float tagpt, const float tageta, const float tagphi, const float tagE) {
  TLorentzVector tagVector = TNP::GetMuonVector(tagpt, tageta, tagphi, tagE);
	TLorentzVector probeVector = TNP::GetTrackVector(trackpt, tracketa, trackphi);

	return ((tagVector + probeVector).M());
}

float TNP::GetEta(const float theta) {
	return (-log(tan(theta/2)));
}

float TNP::GetPt(const float qoverp, const float theta) {
	return (fabs(1 / qoverp) * sin(theta));
}

float TNP::GetDeltaZ0(const float first, const float second) {
  float diff = 0;
  
  if(first < second) {
    diff = fabs(second - first);
  } else if(first > second) {
    diff = fabs(first - second);
  } else {
    diff = 0;
  }

  return (diff);
}


float TNP::GetDeltaR(const float firstEta, const float firstPhi,
                     const float secondEta, const float secondPhi ) {

  float dPhi = fabs(firstPhi - secondPhi);
  float dPhiWrapped = fabs(fabs( dPhi - M_PI ) - M_PI);

  float dEta = fabs(firstEta - secondEta);

  return (sqrt(dPhiWrapped * dPhiWrapped + dEta * dEta));
}
