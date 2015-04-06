#ifndef TNPFITTER_FITTABLEGROUP_H_
#define TNPFITTER_FITTABLEGROUP_H_ 1

#include "TnPFitter/FittableFunction.h"
#include "TnPFitter/CompositeFunction.h"

class TH1F;

class FittableGroup {
 public:
  FittableGroup(std::string functionName,
                std::string histogramName,
                const FitConfig& fitConfig);
  ~FittableGroup() = default;

  FittableFunction getSignal() const;
  FittableFunction getBackground() const;

  void runFit(TH1F* histogram);
  void fillSignalFunction(const CompositeFunction& composite);

 private:
  FittableFunction signal;
  FittableFunction background;
};

#endif