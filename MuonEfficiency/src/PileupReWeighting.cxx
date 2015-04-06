#include "MuonEfficiency/PileupReWeighting.h"


//______________________________________________________________________________
PileupReWeighting::
PileupReWeighting( const std::string& name, const std::string& title,
                   Root::TPileupReweighting* tool,
                   double override )
  : Weighting(name, title),
    pileupTool(tool),
    channelOverride(override)
{

};

//______________________________________________________________________________
PileupReWeighting::~PileupReWeighting()
{
  pileupTool = NULL;
};

//______________________________________________________________________________
double PileupReWeighting::GetWeight(const D3PDReader::Event* event)
{
  double weight = 1.;

    // Check if tool is good
  if(pileupTool == NULL)
  {
    std::cerr << "Pileup tool not created correctly" << std::endl;
    return (1.);
  } else
  {
    if(event->eventinfo.isSimulation())
    {
      double channelNumber = 0;

      if(channelOverride != 0)
      {
        channelNumber = channelOverride;
      } else 
      {
        channelNumber = event->eventinfo.mc_channel_number();
      }

      double runNumber = event->eventinfo.RunNumber();
      double averageIntPerXing = event->eventinfo.averageIntPerXing();
      weight = pileupTool->GetCombinedWeight(runNumber, channelNumber,
                                             averageIntPerXing);
    };
  };

  // Return weight
  return (weight);
};

ClassImp(PileupReWeighting)
