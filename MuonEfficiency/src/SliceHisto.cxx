#include <MuonEfficiency/SliceHisto.h>
#include <JacobUtils/LoggingUtility.h>
#include <iostream>

// =============================================================================

SliceHisto::SliceHisto(HistoType type, int bins, float min, float max)
 : histo(NULL), nBins(bins), invMin(min), invMax(max), histType(type)
{

}

// =============================================================================

SliceHisto::~SliceHisto()
{

}

// =============================================================================

int SliceHisto::AddSliceVariable(const std::string variableName,
                                 const float bottom,
                                 const float top)
{
    slices[variableName] = std::make_pair(bottom, top);
    return (1);
}

// =============================================================================

int SliceHisto::Initialize(void)
{
    /// Forms the name and title of the histogram based on the slices
    MakeName();

    /// Initialize histogram
    histo = new TH1F(name.c_str(), title.c_str(), nBins, invMin, invMax);
    
    /// Check if all is well
    if(histo == NULL)
    {
        return (0);
    };

    /// Goody!
    return (1);
}

// =============================================================================

int SliceHisto::MakeName()
{
  /// Check if there are slices to append
  if(slices.size() == 0)
  {
    LOG_ERROR() << "Please add some slices before initializing";
    return (0);
  };

  Slices::iterator sliceItr = slices.begin();
  
  name = "InvMass_";
  title = "Invariant Mass ";

  /// iterate over slices and form name and title
  for(;sliceItr!=slices.end(); sliceItr++)
  {
    std::string varName = (*sliceItr).first;
    float bottomSlice = (*sliceItr).second.first;
    float topSlice = (*sliceItr).second.second;

    name.append(Form("%s_%0.2f_%0.2f_", varName.c_str(), bottomSlice, topSlice));
    title.append(Form("(%0.2f<%s<%0.2f)", bottomSlice, varName.c_str(), topSlice));
  };

  name.append(this->LevelName());
  title.append(this->LevelName());

  return (1);
};

// =============================================================================

std::string SliceHisto::LevelName()
{
    if(histType == PROBE)
    {
      return("Probe");
    } else if(histType == MUONPROBE)
    {
      return("MuonProbe");
    } else if(histType == SMT)
    {
      return("SMT");
    } else
    {
      std::cout << "WTF are you doing?!" << std::endl;
      return("");
    }

    return ("");
}
