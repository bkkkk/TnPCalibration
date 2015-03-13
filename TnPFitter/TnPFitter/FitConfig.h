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
  FitConfig(std::string function,
            unsigned npar,
            bool isLowBkg,
            double min = 2.62f,
            double max = 3.5f);

  ~FitConfig() {}

  void SetFitLimits(double min, double max);
  double GetFitMin() const;
  double GetFitMax() const;

  void SetFitFunction(const std::string& fitFunction);
  std::string GetFitFunction() const;

  void SetBackgroundFitFunction(const std::string& function);
  std::string GetBackgroundFitFunction() const;

  void SetSignalFitFunction(const std::string& function);
  std::string GetSignalFitFunction() const;

  void SetFitOptions(const std::string& options);
  std::string GetFitOptions() const;

  bool GetMode() const;
  inline bool IsLowBackground() const { return (GetMode()); }

  const Parameter& ParSettings(std::size_t i) const;
  void SetParamsSettings(const Parameters& pars);
  const Parameters& ParamsSettings() const;
  std::size_t NPar() const;

 public:
  void SetFromFitResult(const TFitResultPtr& rhs);
  void Print();
  void PrintParameter(const Parameter& par);

 private:
  std::string fitOptions;
  double fitMinimum;
  double fitMaximum;
  std::string fitFunction;
  std::string bkgFunction;
  std::string sigFunction;
  Parameters parameters;
  bool isLowBackground;

#ifdef __CINT__
  ClassDef(FitConfig, 1)
#endif
};

#endif
