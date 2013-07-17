#ifndef TRUTH_MUON_MATCHING_H_
#define TRUTH_MUON_MATCHING_H_ 1

#include "D3PDReader/TruthParticleD3PDObject.h"
#include "D3PDReader/MuonD3PDObject.h"
#include "D3PDReader/TrackParticleD3PDObject.h"

#include <vector>

namespace TT
{

class ChainNavigationTools;

class TruthMuonMatching
{
private:
  // Pointer to D3PDReader
  const D3PDReader::TruthParticleD3PDObject& sink;

private:
  // Chain Navigation Tool
  ChainNavigationTools* navTools;

public:
  // Delta R matching cut
  float deltaRCut;

private:
  // Vector of Found Good Muons
  std::vector<int> truthMuons;

public:
  // Ctor
  TruthMuonMatching(const D3PDReader::TruthParticleD3PDObject& mc);
  
public:
  // Dtor
  ~TruthMuonMatching();

public:
  // Returns true if a pair of reco muon is matched to a pair of truth muons
  int MatchMuonPair( const D3PDReader::MuonD3PDObjectElement& tag,
                     const D3PDReader::MuonD3PDObjectElement& probe );

public:
  // Returns true if a reco muon is matched to a truth muon
  int MatchMuon( const D3PDReader::MuonD3PDObjectElement& muon,
                 int& truthIndex );

public:
  // Returns 1 if a track is matched to a truth muon
  int MatchTrack ( const D3PDReader::TrackParticleD3PDObjectElement& track,
                   int& truthIndex );
};

}

#endif