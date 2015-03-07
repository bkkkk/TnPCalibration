#include <TnPSelector/TJPsiPairSelector.h>

#include <TnPSelector/KinematicUtils.h>
#include <JacobUtils/LoggingUtility.h>

#include <TLorentzVector.h>

#include <limits>
#include <string>


TJPsiPairSelector::TJPsiPairSelector(const std::string& name)
 : name(name),
   deltaRCutMax(std::numeric_limits<float>::max()),
   deltaRCutMin(std::numeric_limits<float>::min()),
   signCut(std::numeric_limits<float>::max()),
   minMassCut(std::numeric_limits<float>::min()),
   maxMassCut(std::numeric_limits<float>::max()),
   deltaZ0Cut(std::numeric_limits<float>::max()) {
}

TJPsiPairSelector::~TJPsiPairSelector() { }

int TJPsiPairSelector::initialize() {
  if (deltaRCutMax == std::numeric_limits<float>::max()) return (0);
  if (deltaRCutMin == std::numeric_limits<float>::min()) return (0);
  if (deltaRCutMax <= deltaRCutMin) return (0);
  if (signCut == std::numeric_limits<float>::max()) return (0);
  if (minMassCut == std::numeric_limits<float>::min()) return (0);
  if (maxMassCut == std::numeric_limits<float>::max()) return (0);
  if (maxMassCut <= minMassCut) return (0);
  if (deltaZ0Cut == std::numeric_limits<float>::max()) return (0);
  if (deltaZ0Cut == 0.0) return (0);
  return (1);
}

int TJPsiPairSelector::accept(const IMuon& tag, const IMuon& muonProbe) {
  auto deltaR = TNP::GetDeltaR(tag, muonProbe);
  auto sign = TNP::GetChargeSign(tag.charge(), muonProbe.charge());
  auto invMass = TNP::GetInvariantMass(tag, muonProbe);
  auto deltaZ0 = TNP::GetDeltaZ0(muonProbe.id_z0_exPV(), tag.id_z0_exPV());

  return (accept(deltaR, sign, invMass, deltaZ0));
}

int TJPsiPairSelector::accept(const IMuon& tag, const ITrack& probe) {
  auto deltaR = TNP::GetDeltaR(tag, probe);
  auto sign = TNP::GetChargeSign(tag.charge(), probe.charge());
  auto invMass = TNP::GetInvariantMass(tag, probe);
  auto deltaZ0 = TNP::GetDeltaZ0(tag.id_z0_exPV(), probe.z0_wrtPV());

  return (accept(deltaR, sign, invMass, deltaZ0));
}

int TJPsiPairSelector::accept(float deltaR, float sign, float invMass,
                              float deltaZ0) {
  if (!isInInvariantMassRange(invMass)) return (0);
  if (!isInDeltaRRange(deltaR)) return (0);
  if (sign != signCut) return (0);
  if (deltaZ0 > deltaZ0Cut) return (0);

  return (1);
}

bool TJPsiPairSelector::isInInvariantMassRange(float invariantMass) const {
  return (minMassCut < invariantMass && invariantMass < maxMassCut);
}

bool TJPsiPairSelector::isInDeltaRRange(float deltaR) const {
  return (deltaRCutMin < deltaR && deltaR < deltaRCutMax);
}

int TJPsiPairSelector::finalize() {
  return (1);
}


