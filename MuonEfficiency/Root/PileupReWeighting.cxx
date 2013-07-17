#include "MuonEfficiency/PileupReWeighting.h"


//______________________________________________________________________________
PileupReWeighting::PileupReWeighting( const std::string& name,
                                      const std::string& title,
                                      Root::TPileupReweighting* tool )
 : Weighting(name, title),
   pileupTool(tool)
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
    double weight = 1;

    // Check if tool is good
    if(pileupTool == NULL)
    {
        std::cerr << "Pileup tool not created correctly" << std::endl;
    } else
    {
        if(event->eventinfo.isSimulation())
        {
            float channelNumber = event->eventinfo.mc_channel_number();
            float runNumber = event->eventinfo.RunNumber();
            float averageIntPerXing = event->eventinfo.averageIntPerXing();

            weight = pileupTool->GetCombinedWeight(runNumber,
                                                   channelNumber,
                                                   averageIntPerXing);
        };
    };

    // Return weight
    return (weight);
};

ClassImp(PileupReWeighting)
