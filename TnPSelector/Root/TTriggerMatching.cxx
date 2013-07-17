#ifndef TJPSITAGSELECTOR_CXX_
#define TJPSITAGSELECTOR_CXX_ 1

#include <TnPSelector/TTriggerMatching.h>
#include <JacobUtils/LoggingUtility.h>
#include <TnPSelector/KinematicUtils.h>

ClassImp(TTriggerMatching);

// ===========================================================================
 
TTriggerMatching:: 
TTriggerMatching(const std::string& val_name)
 : name(val_name),
   dRCut(9999999)
{

};

// ===========================================================================

TTriggerMatching ::
~TTriggerMatching()
{

};

// ===========================================================================

int TTriggerMatching ::
initialize()
{
	return 1;
};

// =============================================================================

int TTriggerMatching ::
accept( const D3PDReader::MuonD3PDObjectElement& muon, 
        const D3PDReader::TrigMuonEFInfoD3PDObject& trigMuonEF )
{
  float dR = 1000.;

  int trigMuonEFIdx = 0; int trackIdx = 0;
  int trigMuonEFSize = trigMuonEF.n();

  int trigPass = 0;

  while(dR >= dRCut && trigMuonEFIdx < trigMuonEFSize)
  {
    LOG_DEBUG3() << "Grabbing EF object: " << trigMuonEFIdx;
    if( trigMuonEF[trigMuonEFIdx].EF_mu6_Trk_Jpsi_loose() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu6() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu15() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu8() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu4T() <= 0 )
    {
      LOG_DEBUG3() << "No triggers matched";
      trigMuonEFIdx++;
      continue;
    };

    LOG_DEBUG3() << "EF Muon passed atleast one trigger";

    trackIdx = 0;
    int trackN = trigMuonEF[trigMuonEFIdx].track_CB_eta().size();

    while(dR >= dRCut && trackIdx < trackN)
    {
      // EF Muon
      float efMuonEta = trigMuonEF[trigMuonEFIdx].track_CB_eta().at(trackIdx);
      float efMuonPhi = trigMuonEF[trigMuonEFIdx].track_CB_phi().at(trackIdx);
        
      // Offline muon
      float muonEta = muon.eta();
      float muonPhi = muon.phi();
      dR = TNP::GetDeltaR(efMuonEta, efMuonPhi, muonEta, muonPhi);

      LOG_DEBUG3() << "Muon eta: " << muonEta << " phi: " << muonPhi;
      LOG_DEBUG3() << "EF Muon eta: " << efMuonEta << " phi: " << efMuonPhi;
      LOG_DEBUG3() << "Delta R(EF track and offline muon): " << dR;

      trackIdx++;
    }; // End for trackIdx
    trigMuonEFIdx++;
  }; // TrigMuonEFIdx

  if(dR >= dRCut) return(0);
  else return(1);
}; // End accept

// ===========================================================================

int TTriggerMatching ::
finalize()
{
	return (1);
};

// ===========================================================================

#endif
