#include <TnPSelector/TJPsiProbeSelector.h>

#include <limits>
#include <cmath>

TJPsiProbeSelector::TJPsiProbeSelector()
    : etaCut(std::numeric_limits<float>::max()),
      pCut(std::numeric_limits<float>::min()) {
}

TJPsiProbeSelector::~TJPsiProbeSelector() {
}

int TJPsiProbeSelector::initialize() {
  if (etaCut == std::numeric_limits<float>::max())
    return (0);
  if (pCut == std::numeric_limits<float>::min())
    return (0);

  return (1);
}

int TJPsiProbeSelector::accept(const ITrack& track) {
  float eta = track.eta();
  float pt = track.pt();
  return (accept(eta, pt));
}

int TJPsiProbeSelector::accept(const float& eta, const float& p) {
  if (std::fabs(eta) > etaCut)
    return (0);
  if (p < pCut)
    return (0);
  return (1);
}

int TJPsiProbeSelector::finalize() {
  return (1);
}
