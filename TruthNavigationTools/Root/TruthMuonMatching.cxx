#include "TruthNavigationTools/TruthMuonMatching.h"
#include "TruthNavigationTools/ChainNavigationTools.h"
#include "TnPSelector/KinematicUtils.h"
#include "JacobUtils/LoggingUtility.h"

// For max values of float
#include <limits>

//______________________________________________________________________________
TT::TruthMuonMatching::TruthMuonMatching(const D3PDReader::TruthParticleD3PDObject& mc)
 : sink(mc),
   navTools(new TT::ChainNavigationTools(mc)),
   deltaRCut(std::numeric_limits<float>::max())
{
  truthMuons = navTools->FindAllOfType(TT::MUON);
};

//______________________________________________________________________________
TT::TruthMuonMatching::~TruthMuonMatching()
{
  delete navTools;
};

//______________________________________________________________________________
int TT :: TruthMuonMatching ::
MatchMuonPair( const D3PDReader::MuonD3PDObjectElement& tag,
               const D3PDReader::MuonD3PDObjectElement& probe )
{
  int truthTagIndex = 0;
  int truthProbeIndex = 0;

  int probeMatched = MatchMuon(probe, truthProbeIndex);
  int tagMatched = MatchMuon(tag, truthTagIndex);

  if(probeMatched != 1 || tagMatched != 1) return (0);

  if(truthTagIndex == truthProbeIndex)
  {
    LOG_DEBUG() << "Tag and probe matched to the same truth muon";
    return (0);
  }

  return (1);
};

//______________________________________________________________________________
int TT :: TruthMuonMatching ::
MatchMuon( const D3PDReader::MuonD3PDObjectElement& muon, int& truthIndex )
{
  std::vector<int>::iterator goodMuon = truthMuons.begin();
  std::vector<int>::iterator lastItr = truthMuons.end();

  float minDeltaR = std::numeric_limits<float>::max();

  for(; goodMuon!=lastItr; goodMuon++)
  {
    float trEta = sink[*goodMuon].eta();
    float trPhi = sink[*goodMuon].phi();

    float recoEta = muon.eta();
    float recoPhi = muon.phi();

    LOG_DEBUG3() << "TruthMatchMuon: " << "Truth Eta: " << trEta
                 << " Truth Phi: " << trPhi
                 << " Reco Eta: " << recoEta
                 << " Reco Phi: " << recoPhi;

    // Get DeltaR
    float deltaR = TNP::GetDeltaR(trEta, trPhi, recoEta, recoPhi);
    LOG_DEBUG3() << "--> Delta R = " << deltaR << " cut is: " << deltaRCut;

    if(deltaR < minDeltaR)
    {
      minDeltaR = deltaR;
      truthIndex = *goodMuon;
    };
  };

  if(minDeltaR < deltaRCut) return (1);
  else return (0);
};

//______________________________________________________________________________
int TT::TruthMuonMatching ::
MatchTrack ( const D3PDReader::TrackParticleD3PDObjectElement& track,
             int& truthIndex )
{
  std::vector<int>::iterator goodMuon = truthMuons.begin();
  std::vector<int>::iterator lastItr = truthMuons.end();

  float minDeltaR = std::numeric_limits<float>::max();

  for(; goodMuon!=lastItr; goodMuon++)
  {
    float trEta = sink[*goodMuon].eta();
    float trPhi = sink[*goodMuon].phi();

    float recoEta = track.eta();
    float recoPhi = track.phi_wrtPV();

    LOG_DEBUG3() << "TruthMatchMuon: " << "Truth Eta: " << trEta
                 << " Truth Phi: " << trPhi
                 << " Track Eta: " << recoEta
                 << " Track Phi: " << recoPhi;

    // Get DeltaR
    float deltaR = TNP::GetDeltaR(trEta, trPhi, recoEta, recoPhi);
    LOG_DEBUG3() << "--> Delta R = " << deltaR << " cut is: " << deltaRCut;

    if(deltaR < minDeltaR)
    {
      minDeltaR = deltaR;
      truthIndex = *goodMuon;
    };
  };

  if(minDeltaR < deltaRCut) return (1);
  else return (0);
};
