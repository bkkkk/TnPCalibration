#include "TnPFitter/FittableGroup.h"

#include <string>

#include "TH1F.h"

#include "TnPFitter/FitConfig.h"

FittableGroup::FittableGroup(std::string functionName,
                             std::string histogramName,
                             const FitConfig& fitConfig)
    : signal{functionName + "_signal_" + histogramName,
             fitConfig.GetSignalFitFunction(),
             fitConfig.GetFitMin(),
             fitConfig.GetFitMax()},
      background{functionName + "_" + histogramName,
                 fitConfig.GetBackgroundFitFunction(),
                 fitConfig.GetFitMin(),
                 fitConfig.GetFitMax()} {
}

FittableFunction FittableGroup::getSignal() const {
  return (signal);
}

FittableFunction FittableGroup::getBackground() const {
  return (background);
}

void FittableGroup::runFit(TH1F* histogram) {
  (void)histogram;
}

void FittableGroup::fillSignalFunction(const CompositeFunction& composite) {
  signal.fixParametersFromConfig(composite.getSignalParameters());
}
