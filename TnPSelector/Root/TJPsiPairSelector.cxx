// Class def
#include <TnPSelector/TJPsiPairSelector.h>

/// Convinience and logging
#include <TnPSelector/KinematicUtils.h>
#include <JacobUtils/LoggingUtility.h>

/// Root
#include <TLorentzVector.h>

/// For numeric limits
#include <limits>

// ============================================================================

TJPsiPairSelector ::
TJPsiPairSelector(const std::string& val_name)
 : name(val_name),
   deltaRCutMax(std::numeric_limits<float>::max()),
   deltaRCutMin(std::numeric_limits<float>::min()),
   signCut(std::numeric_limits<float>::max()),
   minMassCut(std::numeric_limits<float>::min()),
   maxMassCut(std::numeric_limits<float>::max()),
   deltaZ0Cut(std::numeric_limits<float>::max())

{

};

// =============================================================================

TJPsiPairSelector ::
~TJPsiPairSelector()
{

};

// =============================================================================

int TJPsiPairSelector ::
initialize()
{
    return (1);
};

// =============================================================================

int TJPsiPairSelector ::
accept(const D3PDReader::MuonD3PDObjectElement& tag,
       const D3PDReader::MuonD3PDObjectElement& muonProbe)
{
    TLorentzVector tagVec = TNP::GetMuonVector(tag.pt(), tag.eta(),
                                               tag.phi(), tag.E());

    TLorentzVector muonProbeVec = TNP::GetMuonVector(muonProbe.pt(),
                                                     muonProbe.eta(), 
                                                     muonProbe.phi(),
                                                     muonProbe.E());
    
    float deltaR = tagVec.DeltaR(muonProbeVec);
    LOG_DEBUG2() << "Delta R: " << deltaR;
    
    float sign = tag.charge() * muonProbe.charge();
    LOG_DEBUG2() << "Sign: " << sign;
    
    float invMass = (tagVec + muonProbeVec).M();
    LOG_DEBUG2() << "Invariant mass: " << invMass;

    float deltaZ0 = GetDeltaZ0(muonProbe.id_z0_exPV(), tag.id_z0_exPV());
    LOG_DEBUG2() << "DeltaZ0: " << deltaZ0;

    return (accept(deltaR, sign, invMass, deltaZ0));
};

// =============================================================================

int TJPsiPairSelector ::
accept(const D3PDReader::MuonD3PDObjectElement& tag,
       const D3PDReader::TrackParticleD3PDObjectElement& probe)
{
  // Build the LorentzVector of objects to get invariant mass and DeltaR
  TLorentzVector tagVec = TNP::GetMuonVector(tag.pt(), tag.eta(), tag.phi(), tag.E());
  TLorentzVector probeVec = TNP::GetTrackVector(probe.pt(), probe.eta(), probe.phi_wrtPV());

  float deltaR = tagVec.DeltaR(probeVec);
  LOG_DEBUG2() << "Pairing Delta R: " << deltaR;
      
  float sign = tag.charge() * (fabs(probe.qoverp_wrtPV()) / probe.qoverp_wrtPV());
  LOG_DEBUG2() << "Pairing Sign: " << sign;
  
  float invMass = (tagVec + probeVec).M();
  LOG_DEBUG2() << "Pairing Invariant mass: " << invMass;

  float deltaZ0 = GetDeltaZ0(probe.z0_wrtPV(), tag.id_z0_exPV());
  LOG_DEBUG2() << "Pairing DeltaZ0: " << deltaZ0;

  return (accept(deltaR, sign, invMass, deltaZ0));
};

// ============================================================================

int TJPsiPairSelector ::
accept(const float& deltaR, const float& sign,
       const float& invMass, const float& deltaZ0)
{
  if ( minMassCut > invMass ) return 0;
  if ( maxMassCut < invMass ) return 0;
  if ( deltaRCutMax < deltaR ) return 0;
  if ( deltaRCutMin > deltaR ) return 0;
  if ( sign != signCut ) return 0;
  if ( deltaZ0 > deltaZ0Cut ) return 0;
  return (1);
};

// ============================================================================

int TJPsiPairSelector ::
finalize()
{
    return (1);
};

// =============================================================================

float TJPsiPairSelector ::
GetDeltaZ0(const float& first, const float& second)
{
    if(first < second)
    {
        return(fabs(second - first));
    } else if(first > second)
    {
        return(fabs(first - second));
    } else
    {
        return(0);
    };
};
