#include "TnPFitter/FitConfigurationHelpers.h"

#include <TH1.h>

bool TNPFITTER::IsLowBackground(TH1* histogram, double fittingEdge, double threshold) {
  if(histogram == nullptr) {
    throw (std::runtime_error("Can't check background mode, histogram is not valid"));
  }

  if(threshold > 1) threshold *= (1/100);

  auto testValue = histogram->GetBinContent(histogram->FindBin(fittingEdge));

  return((histogram->GetMaximum() * threshold > testValue));
}