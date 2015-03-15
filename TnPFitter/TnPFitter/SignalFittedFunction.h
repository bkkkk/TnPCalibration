#ifndef TNPFITTER_SINGALFITTEDFUNCTION
#define TNPFITTER_SINGALFITTEDFUNCTION 1

#include <string>

#include "TnPFitter/FitConfig.h"

class TF1;

class SignalFittedFunction {
 public:
  SignalFittedFunction(std::string fitterName,
                       std::string histogramName,
                       const FitConfig& configuration);
  TF1* getFunction();
  void setFunction(TF1* const function);

  void setParametersFromFunction(TF1* const another);
  void setParameterNames(std::vector<std::string> names);

 private:
  std::string name;
  TF1* signalFunction;
  std::vector<std::string> parameterNames;
};

#endif
