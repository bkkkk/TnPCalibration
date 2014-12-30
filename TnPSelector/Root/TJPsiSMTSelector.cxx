#include <TnPSelector/TJPsiSMTSelector.h>
#include <TnPSelector/KinematicUtils.h>
#include <TLorentzVector.h>
#include <JacobUtils/LoggingUtility.h>

TJPsiSMTSelector ::
TJPsiSMTSelector(const std::string& val_name)
 : name(val_name),
   d0Cut(std::numeric_limits<float>::max()),
   z0SinCut(std::numeric_limits<float>::max()),
   chi2Cut(std::numeric_limits<float>::max()) {

};

TJPsiSMTSelector::~TJPsiSMTSelector() {

};

int TJPsiSMTSelector::initialize() {
  return (1);
}

int TJPsiSMTSelector::accept(const IMuon& muon) {
  float d0 = muon.id_d0_exPV();
  
  float z0 = muon.id_z0_exPV();
  float theta = muon.id_theta();
  float z0sintheta = z0 * sin(theta);

  float chi2 = muon.matchchi2() / muon.matchndof();

  return (accept(d0, z0sintheta, chi2));
};

int TJPsiSMTSelector::accept(const float d0, const float z0sintheta, const float chi2) {
  if (fabs(d0) > d0Cut) return 0;
  if (fabs(z0sintheta) > z0SinCut) return 0;
  if (chi2 > chi2Cut) return 0;
  return (1);
};

int TJPsiSMTSelector::finalize() {
  return (1);
};

