#ifndef TJPSITAGSELECTOR_CXX_
#define TJPSITAGSELECTOR_CXX_ 1

#include <TnPSelector/TJPsiTagSelector.h>
#include <TnPSelector/KinematicUtils.h>

#include <limits>
#include <math.h>

#ifdef __CINT__
ClassImp(TJPsiTagSelector);
#endif

TJPsiTagSelector::TJPsiTagSelector(const std::string& val_name)
 : name(val_name),
   etaCut(std::numeric_limits<float>::max()),
   combinedMuonCut(0),
   ptCut(std::numeric_limits<float>::min()),
   d0Cut(std::numeric_limits<float>::max()),
   z0Cut(std::numeric_limits<float>::max()),
   d0SigCut(std::numeric_limits<float>::max()),
   z0SigCut(std::numeric_limits<float>::max()) {

 }

TJPsiTagSelector::~TJPsiTagSelector() {
}

int TJPsiTagSelector::initialize() {
	return 1;
}

int TJPsiTagSelector::accept(const IMuon& muon) {
	float d0 = muon.id_d0_exPV();
	float z0 = muon.id_z0_exPV();

	float d0Sig = (d0 / muon.id_cov_d0_exPV());
	float z0Sig = (z0 / muon.id_cov_z0_exPV());

	float idTrackTheta = muon.id_theta();
	float idTrackEta = TNP::GetEta(idTrackTheta);

	float idTrackPt = TNP::GetPt(muon.id_qoverp(), idTrackTheta);

	return (accept(idTrackEta, muon.isCombinedMuon(), idTrackPt,
                   d0, z0, d0Sig, z0Sig));
}

int TJPsiTagSelector::accept(float eta, int combinedMuon, float pt, float d0,
	   float z0, float d0Sig, float z0Sig) {
	if(fabs(eta) > etaCut) return 0;
	if(combinedMuon != combinedMuonCut) return 0;
	if(pt < ptCut) return 0;
	if(fabs(d0) > d0Cut) return 0;
	if(fabs(z0) > z0Cut) return 0;
	if(fabs(d0Sig) > d0SigCut) return 0;
	if(fabs(z0Sig) > z0SigCut) return 0;

	return (1);
}

int TJPsiTagSelector ::
finalize() {
	return (1);
}

#endif
