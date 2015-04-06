#ifndef TNPFITTER_FITTABLEFUNCTION_H_
#define TNPFITTER_FITTABLEFUNCTION_H_ 1

class TF1;

#include "TnPFitter/FitConfig.h"

class FittableFunction {
 public:
  FittableFunction(std::string name, std::string formula, double min, double max);
  FittableFunction(TF1* function);
  ~FittableFunction() = default;

  TF1* getFunction() const;
  void setFunction(TF1* function);
  void setupParametersFromConfig(const Parameters& pars);
  void setParameterFromConfig(std::size_t index, const Parameter& parameter);
  void fixParametersFromConfig(const Parameters& pars);
  void fixParameterFromConfig(std::size_t index, const Parameter& parameter);

  Parameters getParameters() const;

 private:
  TF1* function;
};

#endif