#include <TnPSelector/TJPsiSMTSelector.h>
#include <TnPSelector/KinematicUtils.h>
#include <TLorentzVector.h>
#include <JacobUtils/LoggingUtility.h>

TJPsiSMTSelector::TJPsiSMTSelector()
 : d0Cut(std::numeric_limits<float>::max()),
   z0SinCut(std::numeric_limits<float>::max()),
   chi2Cut(std::numeric_limits<float>::max()) {

};

TJPsiSMTSelector::~TJPsiSMTSelector() { }

int TJPsiSMTSelector::initialize() {
  if (d0Cut == std::numeric_limits<float>::max()) return (0);
  if (z0SinCut == std::numeric_limits<float>::max()) return (0);
  if (chi2Cut == std::numeric_limits<float>::max()) return (0);

  return (1);
}

int TJPsiSMTSelector::accept(const IMuon& muon) {
  auto d0 = muon.id_d0_exPV();
  
  auto z0 = muon.id_z0_exPV();
  auto theta = muon.id_theta();
  auto z0sintheta = z0 * sin(theta);

  auto chi2 = muon.matchchi2() / muon.matchndof();

  return (accept(d0, z0sintheta, chi2));
};

int TJPsiSMTSelector::accept(float d0, float z0sintheta, float chi2) {
  if (fabs(d0) > d0Cut) return 0;
  if (fabs(z0sintheta) > z0SinCut) return 0;
  if (chi2 > chi2Cut) return 0;
  return (1);
};

int TJPsiSMTSelector::finalize() {
  return (1);
};

