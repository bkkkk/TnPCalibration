#include <TnPSelector/TJPsiProbeSelector.h>
#include <TnPSelector/KinematicUtils.h>
#include <TLorentzVector.h>
#include <JacobUtils/LoggingUtility.h>
#include <limits>

// ========================================================================

TJPsiProbeSelector::TJPsiProbeSelector(const std::string& val_name)
: name(val_name),
  etaCut(std::numeric_limits<float>::max()),
  pCut(std::numeric_limits<float>::min())
{

};

// ========================================================================

/// Standard dtor
TJPsiProbeSelector::~TJPsiProbeSelector(void)
{

};

// ========================================================================

/// Initialize
int TJPsiProbeSelector::initialize(void)
{
	return (1);
};

// ========================================================================

/// Accept
int TJPsiProbeSelector::accept(const D3PDReader::TrackParticleD3PDObjectElement& track)
{
	// This is needed when I am running with momentum rather then pt
/**
	TLorentzVector trackVec = TNP::GetTrackVector(track.pt(), track.eta(), track.phi_wrtPV());
	float p = trackVec.P();
	float eta = track.eta();
	return (accept(eta, p));
*/
	float eta = track.eta();
	float pt = track.pt();
	return (accept(eta, pt));
};

// ========================================================================

int TJPsiProbeSelector::accept (const float& eta, const float& p)
{
	if ( fabs(eta) > etaCut ) return (0);
	if ( p < pCut ) return (0);
	return (1);
};

// ========================================================================

/// Finalize
int TJPsiProbeSelector::finalize(void)
{
	return (1);
};

// ========================================================================
