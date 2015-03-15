#ifndef TNPFITTER_BACKGROUNDFITTEDFUNCTION_H_
#define TNPFITTER_BACKGROUNDFITTEDFUNCTION_H_ 1

#include <vector>
#include <string>
#include <cassert>

#include "TnPFitter/FitConfig.h"

class TF1;

class BackgroundFittedFunction {
 public:
  BackgroundFittedFunction(std::string fitterName,
                           std::string histogramName,
                           FitConfig& configuration);
  TF1* getFunction();
  void setParametersFromFunction(TF1* const another);
  void setParameterNames(std::vector<std::string> names);

 private:
  std::string name;
  TF1* backgroundFunction;
  std::vector<std::string> parameterNames;
};

#endif
