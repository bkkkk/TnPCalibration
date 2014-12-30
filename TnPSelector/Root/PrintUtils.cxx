#include <TnPSelector/PrintUtils.h>
#include <JacobUtils/LoggingUtility.h>

void PrintUtils::PrintInfoTrack(const ITrack& track) {
// LOG_DEBUG1() << "Track:" << " pT = " << track.pt() << " eta = " << track.eta() << " phi = " << track.phi_wrtPV();
}

void PrintUtils::PrintInfoMuon(const IMuon& muon) { }

void PrintUtils::PrintMuonTrackInfo(const IMuon& muon) { }

void PrintUtils::PrintMuonIsoInfo( const IMuon& muon ) {
#if 0
  float etcone20 = muon.etcone20();
  float etcone30 = muon.etcone30();
  float etcone40 = muon.etcone40();
  
  float nucone20 = muon.nucone20();
  float nucone30 = muon.nucone30();
  float nucone40 = muon.nucone40();
  
  float ptcone20 = muon.ptcone20();
  float ptcone30 = muon.ptcone30();
  float ptcone40 = muon.ptcone40();

  LOG_DEBUG1() << "Muon (Iso): " << std::endl;
  LOG_DEBUG1() << "| etcone20 | " << etcone20 << " | " << std::endl;
  LOG_DEBUG1() << "| etcone30 | " << etcone30 << " | " << std::endl;
  LOG_DEBUG1() << "| etcone40 | " << etcone40 << " | " << std::endl;
  LOG_DEBUG1() << "| nucone20 | " << nucone20 << " | " << std::endl;
  LOG_DEBUG1() << "| nucone30 | " << nucone30 << " | " << std::endl;
  LOG_DEBUG1() << "| nucone40 | " << nucone40 << " | " << std::endl;
  LOG_DEBUG1() << "| ptcone20 | " << ptcone20 << " | " << std::endl;
  LOG_DEBUG1() << "| ptcone30 | " << ptcone30 << " | " << std::endl;
  LOG_DEBUG1() << "| ptcone40 | " << ptcone40 << " | " << std::endl;
#endif
}
