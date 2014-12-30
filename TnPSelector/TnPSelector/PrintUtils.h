#ifndef PRINTUTILS_H_
#define PRINTUTILS_H_ 1

#include <D3PDReaderAdapter/ITrack.h>
#include <D3PDReaderAdapter/IMuon.h>

namespace PrintUtils {  
  void PrintInfoTrack(const ITrack& track);

  void PrintInfoMuon(const IMuon& muon);

  void PrintMuonTrackInfo(const IMuon& muon);

  void PrintMuonIsoInfo(const IMuon& muon);
};

#endif // PRINTUTILS_H_
