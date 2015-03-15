#include "TnPFitter/SignalFittedFunction.h"

#include <vector>
#include <cassert>

#include <TF1.h>

SignalFittedFunction::SignalFittedFunction(std::string fitterName,
                                           std::string histogramName,
                                           const FitConfig& configuration)
    : name{fitterName + "_signal_" + histogramName},
      signalFunction{new TF1(name.c_str(),
                             configuration.GetSignalFitFunction().c_str(),
                             configuration.GetFitMin(),
                             configuration.GetFitMax())} {
}

TF1* SignalFittedFunction::getFunction() {
  return (signalFunction);
}

void SignalFittedFunction::setParametersFromFunction(TF1* const another) {
  for (auto parIdx = 0ul; parIdx < parameterNames.size(); parIdx++) {
    auto paramaterName = parameterNames[parIdx].c_str();
    auto value = another->GetParameter(paramaterName);
    signalFunction->FixParameter(parIdx, value);
  }
}

void SignalFittedFunction::setParameterNames(std::vector<std::string> names) {
  assert(names.size() == (std::size_t)signalFunction->GetNpar());

  for (auto index = 0ul; index < names.size(); index++) {
    signalFunction->SetParName(index, names[index].c_str());
  }
}
