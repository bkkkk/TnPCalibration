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
  // Set fit functions
  void SetFitFunction (const std::string& fitFunction) { fFunction = fitFunction; }
  void SetBackgroundFitFunction (const std::string& fitFunction) { fBkgFunction = fitFunction; }
  void SetSignalFitFunction (const std::string& fitFunction) { fSigFunction = fitFunction; }

public:
  void SetBackgroundIndex (const double index) { firstBkgIndx = index; }

public:
  void SetFitOptions (const std::string& fitOptions) { fFitOptions = fitOptions; }

public:
  bool GetMode(void) { return fLowBackground; }

public:  
  // Get fit functions
  const std::string GetFitFunction (void) const { return (fFunction); } 
  const std::string GetSignalFitFunction (void) const { return (fSigFunction); }
  const std::string GetBackgroundFitFunction (void) const { return (fBkgFunction); }
  std::string GetFitFunction (void) { return (fFunction); } 
  std::string GetSignalFitFunction (void) { return (fSigFunction); }
  std::string GetBackgroundFitFunction (void) { return (fBkgFunction); }

public:
  // Get fit options
  const std::string GetFitOptions (void) const { return (fFitOptions); }
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
    LOG_INFO() << "Configuring fit with the following parameters";
    
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
  std::string fBkgFunction; // Fit Bkg function
  std::string fSigFunction; // Fit Sig function
  bool fLowBackground; // Background mode
  std::vector<ROOT::Fit::ParameterSettings> fSettings; // Vector with the parameter settings
  // @todo - have this be made from strings rather then input manually
  int firstBkgIndx; // Holds the index of the first background parameter

  ClassDef(FitConfig, 1)
};

#endif
