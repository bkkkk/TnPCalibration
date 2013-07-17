#include <JacobUtils/ReaderTools.h>
#include <MuonEfficiency/TnPSlices.h>

#include <JacobUtils/LoggingUtility.h>

#include <iostream>
#include <algorithm>

ClassImp(TnPSlices)

TnPSlices::TnPSlices(const std::string& val_name)
 : name(val_name)
{

};

// =============================================================================

TnPSlices::~TnPSlices(void)
{

};

// =============================================================================

int TnPSlices::AddSlices(std::string varName, std::string path)
{
    std::vector<float> slices;
    RT::GetListFromFile(path, slices);
 
    return(this->AddSlices(varName, slices));
};

// =============================================================================

int TnPSlices::AddSlices(std::string varName, std::vector<float> slices)
{
    /// Store the flat slices
    flatSlices[varName] = slices;

    /// Store paired slices
    Slices bins;

    for(size_t edge = 1; edge != slices.size(); edge++)
    {
        bins.push_back(std::make_pair(slices[edge - 1], slices[edge]));
    };

    varMap[varName] = bins;
    varNames.push_back(varName);

    return(varMap.size() - 1);
};

// =============================================================================

int TnPSlices::Initialize()
{
    return (1);
};

// =============================================================================

void TnPSlices::PrintSlices(const std::string& var)
{
  size_t size = varMap[var].size();

  LOG_INFO() << "Slices of " << var << std::endl;

  for(size_t idx = 0; idx != size; idx++)
  {
    PrintSliceVector(varMap[var][idx]);
  };
};

// =============================================================================

void TnPSlices::PrintSliceVector(const Slice& slice)
{
  LOG_INFO() << "{ " << slice.first << ", " << slice.second << " }";
};

// =============================================================================

VariableName TnPSlices::GetListOfSlices(void)
{
    return( varNames );
};

// =============================================================================

size_t TnPSlices::GetNumberOfVariables(void)
{
    return( varNames.size() );
};

// =============================================================================

size_t TnPSlices::GetNumberOfSlices(const std::string& var)
{
    return( varMap[var].size() );
};

std::string TnPSlices::GetSliceLabel(const std::string& var, const float value)
{
  std::string name = "";

  std::vector<float>::iterator upperItr = std::upper_bound((flatSlices[var]).begin(),
                                                           (flatSlices[var]).end(),
                                                           value);

  float lowerBound = *(upperItr - 1);
  float upperBound = *upperItr;

  if (lowerBound == upperBound) return (name);

  if( upperItr == flatSlices[var].end())
  {
    lowerBound = *(upperItr - 2);
    upperBound = *(upperItr - 1);
  }

  name = Form("%s_%0.2f_%0.2f_", var.c_str(), lowerBound, upperBound);

  LOG_DEBUG2() << "Making slice label: " << name;

  return (name);
};
