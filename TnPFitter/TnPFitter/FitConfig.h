#ifndef TNPFIT_FITCONFIG_H_
#define TNPFIT_FITCONFIG_H_ 1

#include "Fit/ParameterSettings.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"

#include "JacobUtils/LoggingUtility.h"

#include <vector>
#include <string>

class FitConfig
{
public:
  FitConfig(const std::string& function, unsigned int npar, bool isLowBkg);

public:
  ~FitConfig();

public:
  void SetFitFunction (const std::string& fitFunction) { fFunction = fitFunction; }

public:
  void SetFitOptions (const std::string& fitOptions) { fFitOptions = fitOptions; }

public:
  bool GetMode(void) { return fLowBackground; }

public:  
  const std::string GetFitFunction (void) const { return (fFunction); } 

public:
  std::string GetFitFunction (void) { return (fFunction); } 

public:
  const std::string GetFitOptions (void) const { return (fFitOptions); }

public:
  std::string GetFitOptions (void) { return (fFitOptions); }

public:
  const ROOT::Fit::ParameterSettings& ParSettings(unsigned int i) const { return fSettings.at(i); }

public:
  ROOT::Fit::ParameterSettings& ParSettings(unsigned int i) { return fSettings.at(i); }  

public:
  const std::vector<ROOT::Fit::ParameterSettings>& ParamsSettings() const { return fSettings; }

public:
  std::vector<ROOT::Fit::ParameterSettings>& ParamsSettings() { return fSettings; }

public:
  unsigned int NPar() const { return fSettings.size(); };

public:
  void SetParamsSettings(const std::vector<ROOT::Fit::ParameterSettings>& pars)
  {
    fSettings = pars;
  }

public:
  void SetFromFitResult (const TFitResultPtr& rhs);

public:
  void Print()
  {
    LOG_INFO() << "Printing variables";
    
    for(size_t parIdx = 0; parIdx != fSettings.size(); parIdx++)
    {
      std::string name = fSettings.at(parIdx).Name();
      double val = fSettings.at(parIdx).Value();
      double lowLimit = fSettings.at(parIdx).LowerLimit();
      double topLimit = fSettings.at(parIdx).UpperLimit();

      LOG_INFO() << "| " << name << " | " << val << " | " << lowLimit << " | " << topLimit;
    }
  }

protected:

private:
  std::string fFitOptions; // Fit Options
  std::string fFunction; // Fit function
  bool fLowBackground; // Background mode
  std::vector<ROOT::Fit::ParameterSettings> fSettings; // Vector with the parameter settings
};

#endif
