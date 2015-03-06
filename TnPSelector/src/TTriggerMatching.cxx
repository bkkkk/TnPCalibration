#ifndef TJPSITAGSELECTOR_CXX_
#define TJPSITAGSELECTOR_CXX_ 1

#include <TnPSelector/TTriggerMatching.h>
#include <JacobUtils/LoggingUtility.h>
#include <TnPSelector/KinematicUtils.h>

#ifdef __CINT__
ClassImp(TTriggerMatching);
#endif

TTriggerMatching::TTriggerMatching(const std::string& val_name)
 : name(val_name),
   dRCut(9999999) { }

TTriggerMatching::~TTriggerMatching() { }

int TTriggerMatching::initialize() {
	return 1;
}

int TTriggerMatching ::accept( const IMuon& muon, const ITrigMuons& trigMuonEF ) {
  float dR = 1000.;

  int trigMuonEFIdx = 0; int trackIdx = 0;
  int trigMuonEFSize = trigMuonEF.n();

  while(dR >= dRCut && trigMuonEFIdx < trigMuonEFSize) {
    if( trigMuonEF[trigMuonEFIdx].EF_mu6_Trk_Jpsi_loose() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu6() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu15() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu8() <= 0 &&
        trigMuonEF[trigMuonEFIdx].EF_mu4T() <= 0 ) {
      trigMuonEFIdx++;
      continue;
    }

    trackIdx = 0;
    int trackN = trigMuonEF[trigMuonEFIdx].track_CB_eta().size();

    while(dR >= dRCut && trackIdx < trackN) {
      // EF Muon
      float efMuonEta = trigMuonEF[trigMuonEFIdx].track_CB_eta().at(trackIdx);
      float efMuonPhi = trigMuonEF[trigMuonEFIdx].track_CB_phi().at(trackIdx);
        
      // Offline muon
      float muonEta = muon.eta();
      float muonPhi = muon.phi();
      dR = TNP::GetDeltaR(efMuonEta, efMuonPhi, muonEta, muonPhi);

      trackIdx++;
    }

    trigMuonEFIdx++;
  }

  if(dR >= dRCut) return(0);
  else return(1);
}

int TTriggerMatching::finalize() {
	return (1);
}

#endif
