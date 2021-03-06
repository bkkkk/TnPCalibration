#ifndef TNPFITTER_COMPOSITEFUNCTION_H_
#define TNPFITTER_COMPOSITEFUNCTION_H_ 1

#include "TnPFitter/FittableFunction.h"
#include "TnPFitter/FitConfig.h"
#include <string>

class TF1;

class CompositeFunction {
public:
  CompositeFunction(std::string name, std::string formula,
                    FittableFunction signal, FittableFunction background);

  ~CompositeFunction() = default;

  Parameters getSignalParameters() const;

  void setSignalParameters(const Parameters& pars);
  void setSignalParametersInComposite(const Parameters& pars);

  void fixSignalParameters(const Parameters &pars);

  Parameters getBackgroundParameters() const;

  void setBackgroundParameters(const Parameters &pars);
  void setBackgroundParametersInComposite(const Parameters& pars);

  void fixBackgroundParameters(const Parameters &pars);

  TF1 *getFunction() const;

private:
  std::string formula;
  FittableFunction signal;
  FittableFunction background;
  TF1 *function;

  bool functionsHaveSameRange();
};

#endif