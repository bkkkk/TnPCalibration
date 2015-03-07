#ifndef TNPSELECTOR_FAKETRACKS_H_
#define TNPSELECTOR_FAKETRACKS_H_ 1

#include <vector>

#include "D3PDReaderAdapter/ITrack.h"
#include "D3PDReaderAdapter/ITracks.h"
#include "./FakeTrack.h"

class FakeTracks : public ITracks {
public:
  FakeTracks() = default;

  FakeTracks(std::initializer_list<FakeTrack> il) : tracks{ il } {}

  ~FakeTracks() { tracks.clear(); }

  std::size_t n() const { return (tracks.size()); }

  ITrack& operator[](std::size_t idx) { return (tracks[idx]); }

  const ITrack& operator[](std::size_t idx) const { return (tracks[idx]); }

  void push_back(const FakeTrack& Track) { tracks.push_back(Track); }

private:
  std::vector<FakeTrack> tracks;
};

#endif
