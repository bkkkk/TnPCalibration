#include <TnPSelector/TJPsiMuonProbeSelector.h>

// To get vector objects
#include <TnPSelector/KinematicUtils.h>
#include <TVector3.h>
#include <limits>

// ============================================================================

TJPsiMuonProbeSelector ::
TJPsiMuonProbeSelector( const std::string& val_name )
{

}

// ============================================================================

TJPsiMuonProbeSelector ::
~TJPsiMuonProbeSelector( void )
{

}

// ============================================================================

int TJPsiMuonProbeSelector ::
initialize( void )
{
    return (1);
}

// ============================================================================

int TJPsiMuonProbeSelector ::
accept( const D3PDReader::TrackParticleD3PDObjectElement& probe,
        const D3PDReader::MuonD3PDObject& muons,
        int& muonProbeIdx )
{
  float deltaR = std::numeric_limits<float>::max();

  // loop over all muons and find a candidate that is a combined muon
  // within deltaRCut
  for(int muon = 0; muon != muons.n(); muon++)
  {
    // Check if muon is combined
    if(muons[muon].isCombinedMuon() != 1) continue;

    float deltaRCandidate = this->GetDeltaR(probe, muons[muon]);
        
    // Minimize deltaR
    if(deltaRCandidate < deltaR)
    {
      deltaR = deltaRCandidate;
      muonProbeIdx = muon;
    } // End if deltaR minimization
  } // End for muons

  // Return the result of the deltaR cut
  return (accept(deltaR));
}

// ============================================================================

float TJPsiMuonProbeSelector ::
GetDeltaR( const D3PDReader::TrackParticleD3PDObjectElement& probe,
           const D3PDReader::MuonD3PDObjectElement& muon )
{
  // Construct four-vector of probe
  TLorentzVector probeVec = TNP::GetTrackVector( probe.pt(),
                                                 probe.eta(),
                                                 probe.phi_wrtPV() );
    
  // Construct four-vector of muon
  TLorentzVector muonVec = TNP::GetMuonVector( muon.pt(),
                                               muon.eta(),
                                               muon.phi(),
                                               muon.E());
    
  // Returns the delta R separation
  return (probeVec.DeltaR(muonVec));
}

// ============================================================================

int TJPsiMuonProbeSelector ::
accept( const float& deltaR )
{
  // Apply delta R cut
  if( deltaR > deltaRCut ) return (0);
  return (1);
}

// ============================================================================

int TJPsiMuonProbeSelector ::
finalize( void )
{
  return (1);
}

// ============================================================================


