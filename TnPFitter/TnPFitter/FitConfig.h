#ifndef TNPFIT_FITCONFIG_H_
#define TNPFIT_FITCONFIG_H_ 1

#include "Fit/ParameterSettings.h"
#include "TFitResultPtr.h"

#include <vector>
#include <string>

using Parameter = ROOT::Fit::ParameterSettings;
using Parameters = std::vector<Parameter>;

class FitConfig {
 public:
  FitConfig(std::string sigFormula,
            std::string bkgFormula,
            unsigned signalPars,
            unsigned bkgPars,
            double min = 2.62f,
            double max = 3.5f);

  ~FitConfig() = default;

  void SetFitLimits(double min, double max);
  double GetFitMin() const;
  double GetFitMax() const;

  void SetBackgroundFitFunction(const std::string& function);
  std::string GetBackgroundFitFunction() const;

  void SetSignalFitFunction(const std::string& function);
  std::string GetSignalFitFunction() const;

  void SetFitOptions(const std::string& options);
  std::string GetFitOptions() const;

  Parameters getSignalParameters() const;
  void setSignalParameters(const Parameters& parameters);
  Parameter getSignalParameter(std::size_t index) const;
  std::size_t getNumberOfSignalParameters();

  Parameters getBkgParameters() const;
  void setBkgParameters(const Parameters& parameters);
  Parameter getBkgParameter(std::size_t index) const;
  std::size_t getNumberOfBkgParameters();

 public:
  void SetFromFitResult(const TFitResultPtr& rhs);
  void Print();
  void PrintParameter(const Parameter& par);

 private:
  std::string fitOptions;
  double fitMinimum;
  double fitMaximum;
  std::string sigFunction;
  std::string bkgFunction;
  Parameters signalParameters;
  Parameters bkgParameters;

#ifdef __CINT__
  ClassDef(FitConfig, 1)
#endif
};

#endif
