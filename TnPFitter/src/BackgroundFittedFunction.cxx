#include "TnPFitter/BackgroundFittedFunction.h"

#include <vector>
#include <cassert>

#include "TF1.h"

BackgroundFittedFunction::BackgroundFittedFunction(std::string fitterName,
                                                   std::string histogramName,
                                                   FitConfig& configuration)
    : name{fitterName + "_" + histogramName},
      backgroundFunction(
          new TF1(name.c_str(),
                  configuration.GetBackgroundFitFunction().c_str(),
                  configuration.GetFitMin(),
                  configuration.GetFitMax())) {
}

TF1* BackgroundFittedFunction::getFunction() {
  return (backgroundFunction);
}

void BackgroundFittedFunction::setParametersFromFunction(TF1* const another) {
  for (auto parIdx = 0ul; parIdx < parameterNames.size(); parIdx++) {
    auto paramaterName = parameterNames[parIdx].c_str();
    auto value = another->GetParameter(paramaterName);
    backgroundFunction->FixParameter(parIdx, value);
  }
}

void BackgroundFittedFunction::setParameterNames(
    std::vector<std::string> names) {
  assert(names.size() == (std::size_t)backgroundFunction->GetNpar());

  for (auto index = 0ul; index < names.size(); index++) {
    backgroundFunction->SetParName(index, names[index].c_str());
  }
}
