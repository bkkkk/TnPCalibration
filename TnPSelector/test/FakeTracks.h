#ifndef TNPSELECTOR_FAKETRACKS_H_
#define TNPSELECTOR_FAKETRACKS_H_ 1

#include <D3PDReaderAdapter/ITrack.h>
#include "FakeTrack.h"

class FakeTracks : public ITracks {
public:
  ~FakeTracks() {
    Tracks.clear();
  }

  std::size_t n() const {
    return (Tracks.size());
  }

  ITrack& operator[](std::size_t idx) {
    return (Tracks[idx]);
  }

  const ITrack& operator[](std::size_t idx) const {
    return (Tracks[idx]);
  }

  void push_back(const FakeTrack& Track) {
    Tracks.push_back(Track);
  }

private:
  std::vector<FakeTrack> Tracks;
};

#endif

