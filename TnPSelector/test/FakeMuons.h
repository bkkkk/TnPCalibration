#ifndef TNPSELECTOR_FAKEMUONS_H_
#define TNPSELECTOR_FAKEMUONS_H_ 1

#include <vector>

#include "D3PDReaderAdapter/IMuons.h"

#include "./FakeMuon.h"

class FakeMuons : public IMuons {
public:
  FakeMuons() = default;

  FakeMuons(std::initializer_list<FakeMuon> il) : muons{ il } {}

  ~FakeMuons() { muons.clear(); }

  std::size_t n() const { return (muons.size()); }

  IMuon& operator[](std::size_t idx) { return (muons[idx]); }

  const IMuon& operator[](std::size_t idx) const { return (muons[idx]); }

  void push_back(const FakeMuon& muon) { muons.push_back(muon); }

private:
  std::vector<FakeMuon> muons;
};

#endif
