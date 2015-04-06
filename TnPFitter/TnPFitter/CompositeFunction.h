#ifndef TNPFITTER_COMPOSITEFUNCTION_H_
#define TNPFITTER_COMPOSITEFUNCTION_H_ 1

#include "TnPFitter/FittableFunction.h"
#include "TnPFitter/FitConfig.h"
#include <string>

class TF1;

class CompositeFunction {
 public:
  CompositeFunction(std::string name,
                    FittableFunction signal,
                    FittableFunction background);
  ~CompositeFunction() = default;

  Parameters getSignalParameters() const;
  void setSignalParameters(const Parameters& pars);
  void fixSignalParameters(const Parameters& pars);

  Parameters getBackgroundParameters() const;
  void setBackgroundParameters(const Parameters& pars);
  void fixBackgroundParameters(const Parameters& pars);

  TF1* getFunction() const;

 private:
  FittableFunction signal;
  FittableFunction background;
  TF1* function;
};

#endif