#include <TnPSelector/TJPsiPairSelector.h>

#include <TnPSelector/KinematicUtils.h>
#include <JacobUtils/LoggingUtility.h>

#include <TLorentzVector.h>

#include <limits>


TJPsiPairSelector::TJPsiPairSelector(const std::string& val_name)
 : name(val_name),
   deltaRCutMax(std::numeric_limits<float>::max()),
   deltaRCutMin(std::numeric_limits<float>::min()),
   signCut(std::numeric_limits<float>::max()),
   minMassCut(std::numeric_limits<float>::min()),
   maxMassCut(std::numeric_limits<float>::max()),
   deltaZ0Cut(std::numeric_limits<float>::max()) {
}

TJPsiPairSelector::~TJPsiPairSelector() { }

int TJPsiPairSelector::initialize() {
  return (1);
}

int TJPsiPairSelector::accept(const IMuon& tag, const IMuon& muonProbe) {
  TLorentzVector tagVec = TNP::GetMuonVector(tag.pt(), tag.eta(),
                                             tag.phi(), tag.E());

  TLorentzVector muonProbeVec = TNP::GetMuonVector(muonProbe.pt(),
                                                   muonProbe.eta(),
                                                   muonProbe.phi(),
                                                   muonProbe.E());

  float deltaR = tagVec.DeltaR(muonProbeVec);
  float sign = tag.charge() * muonProbe.charge();
  float invMass = (tagVec + muonProbeVec).M();
  float deltaZ0 = GetDeltaZ0(muonProbe.id_z0_exPV(), tag.id_z0_exPV());

  return (accept(deltaR, sign, invMass, deltaZ0));
}

int TJPsiPairSelector::accept(const IMuon& tag, const ITrack& probe) {
  TLorentzVector tagVec = TNP::GetMuonVector(tag.pt(), tag.eta(), tag.phi(), tag.E());
  TLorentzVector probeVec = TNP::GetTrackVector(probe.pt(), probe.eta(), probe.phi_wrtPV());

  float deltaR = tagVec.DeltaR(probeVec);
  float sign = tag.charge() * (fabs(probe.qoverp_wrtPV()) / probe.qoverp_wrtPV());
  // GetChargeSign(charge, qoverp)
  float invMass = (tagVec + probeVec).M();
  float deltaZ0 = GetDeltaZ0(probe.z0_wrtPV(), tag.id_z0_exPV());

  return (accept(deltaR, sign, invMass, deltaZ0));
}

float GetChargeSign(float charge, float qoverp) {
  return (charge * (fabs(qoverp) / qoverp));
}

float TJPsiPairSelector::GetDeltaZ0(float first, float second) {
  return (fabs(second - first));
}

int TJPsiPairSelector::accept(float deltaR, float sign, float invMass, float deltaZ0) {
  if(minMassCut > invMass) return 0;
  if(maxMassCut < invMass) return 0;
  if(deltaRCutMax < deltaR) return 0;
  if(deltaRCutMin > deltaR) return 0;
  if(sign != signCut) return 0;
  if(deltaZ0 > deltaZ0Cut) return 0;

  return (1);
}

int TJPsiPairSelector::finalize() {
  return (1);
}


