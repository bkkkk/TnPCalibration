#include <TnPSelector/TJPsiClassifier.h>
#include <JacobUtils/LoggingUtility.h>
#include <TnPSelector/KinematicUtils.h>

//______________________________________________________________________________
TJPsiClassifier :: 
TJPsiClassifier(const std::string& val_name)
 : name(val_name),
   pair(std::make_pair(-9999, -9999)),
   isMuonProbe(0),
   isSMT(0),
   muonProbeIdx(10000),
   smallestDZ0(1000),
   mcpSelector(NULL),
   tagSelector(NULL),
   pairSelector(NULL),
   probeSelector(NULL),
   muonProbeSelector(NULL),
   smtSelector(NULL)
{

};

//______________________________________________________________________________

TJPsiClassifier ::
~TJPsiClassifier()
{

};

//______________________________________________________________________________
int TJPsiClassifier ::
initialize(void)
{
  if(mcpSelector == NULL)
  {
    LOG_WARNING() << "MCP Selector not configured correctly";
    return (0);
  }
  if(tagSelector == NULL)
  {
    LOG_WARNING() << "Tag Selector not configured correctly";
    return (0);
  }
  if(pairSelector == NULL)
  {
    LOG_WARNING() << "Pair Selector not configured correctly";
    return (0);
  }
  if(probeSelector == NULL)
  {
    LOG_WARNING() << "Probe Selector not configured correctly";
    return (0);
  }
  if(muonProbeSelector == NULL)
  {
    LOG_WARNING() << "Probe Selector not configured correctly";
    return (0);
  }
  if(smtSelector == NULL)
  {
    LOG_WARNING() << "SMT Selector not configured correctly";
    return (0);
  };

  return (1);
};

//______________________________________________________________________________
int TJPsiClassifier ::
classify( const D3PDReader::MuonD3PDObject& muons,
          const D3PDReader::TrackParticleD3PDObject& tracks )
{
  // Clear all indexes, pairs and index datasets
  this->clear();

  int nMuons = muons.n();
  int nTracks = tracks.n();

  for (int muon = 0; muon != nMuons; muon++)
  {
    if(tagSelector->accept(muons[muon]) == 1 &&
       mcpSelector->accept(muons[muon]) == 1 )
    {
      LOG_DEBUG1() << "Muon " << muon + 1 << " is a tag";
      tagsIndexes.push_back(muon);
    };
  };

  LOG_DEBUG1() << "There are " << tagsIndexes.size() << " tag muons";   

  for(int track = 0; track != nTracks; track++)
  {
    if( probeSelector->accept(tracks[track]) == 1 &&
        mcpSelector->accept(tracks[track]) == 1 )
    {
      LOG_DEBUG1() << "Track " << track + 1 << " is a probe";
      probesIndexes.push_back(track);
    };
  };

  LOG_DEBUG1() << "There are " << probesIndexes.size() << " probe tracks";
  
  
  smallestDZ0 = 1000.;
  int chosenTag = -9999;
  int chosenProbe = -9999;

  // Loop over probes
  std::vector<int>::iterator probeIdx = probesIndexes.begin();
  std::vector<int>::iterator probeLast = probesIndexes.end();
  for(; probeIdx != probeLast; probeIdx++)
  {
    // Loop over tag
    std::vector<int>::iterator tagIdx = tagsIndexes.begin();
    std::vector<int>::iterator tagLast = tagsIndexes.end();
    for(;tagIdx != tagLast; tagIdx++)
    { 
      LOG_DEBUG1() << "Looping over tag: " << (*tagIdx) << " and probe " << (*probeIdx);

      if( pairSelector->accept( muons[*tagIdx], tracks[*probeIdx] ) != 1) continue;
      LOG_DEBUG1() << "Good Pair";

      float trk_z0_wrtPV = tracks[*probeIdx].z0_wrtPV();
      float tag_id_z0_wrtPV = muons[*tagIdx].id_z0_exPV();

      float dz0 = TNP::GetDeltaZ0(trk_z0_wrtPV, tag_id_z0_wrtPV);

      if(smallestDZ0 > dz0)
      {
        smallestDZ0 = dz0;
        chosenTag = *tagIdx;
        chosenProbe = *probeIdx;
      }; // Minimize z0
    }; // End for tag 
  }; // End for probes

  if(smallestDZ0 == 1000.)
  {
    LOG_DEBUG1() << "No good pair found in this event";
    return 0;
  };

  LOG_DEBUG1() << "Chosen pair has tag: " << chosenTag
               << " with probe " << chosenProbe
               << " with dz0" << smallestDZ0;

  pair = std::make_pair(chosenTag, chosenProbe);

  isMuonProbe = muonProbeSelector->accept(tracks[chosenProbe], muons, muonProbeIdx);
  if(isMuonProbe != 1)
  {
    return (1);
  }
  LOG_DEBUG() << "Good MuonProbe Pair";
  
  isSMT = smtSelector->accept(muons[muonProbeIdx]);
  if(isSMT == 1)
  {
    LOG_DEBUG() << "Good SMT Pair";
  }

  return (1);
};

//______________________________________________________________________________
int TJPsiClassifier ::
clear(void)
{
  isMuonProbe = 0;
  isSMT = 0;
  muonProbeIdx = -9999;
  tagsIndexes.clear();
  probesIndexes.clear();
  pair = std::make_pair(-9999,-9999);
  return (1);
};

//______________________________________________________________________________
const std::pair<int, int>& TJPsiClassifier ::
GetSelectedPair()
{
  return(pair);
};

//______________________________________________________________________________
int TJPsiClassifier ::
GetSelectedProbe ()
{
  return (pair.second);
};

int TJPsiClassifier ::
GetMatchedMuonProbe ()
{
  return (muonProbeIdx);
};

//______________________________________________________________________________
int TJPsiClassifier ::
GetSelectedTag ()
{
  return (pair.first);
};

//______________________________________________________________________________
int TJPsiClassifier ::
IsPairMuonProbe (void)
{
  return (isMuonProbe);
};

//______________________________________________________________________________
int TJPsiClassifier ::
IsPairSMT (void)
{
  return (isSMT);
};

ClassImp(TJPsiClassifier)
