#include "TnPFitter/FitConfig.h"

#include "TFitResult.h"

#include "TnPFitter/FitConfigurationHelpers.h"
#include "JacobUtils/LoggingUtility.h"

FitConfig::FitConfig(std::string function, unsigned npar, bool isLowBkg, double min, double max)
 : fitOptions("MERQB"), 
   fitMinimum(min),
   fitMaximum(max),
   fitFunction(std::move(function)),
   bkgFunction(""),
   sigFunction(""),
   parameters(npar),
   isLowBackground(false) {
  
  if(npar == 0) {
    throw(std::runtime_error("Number of parameters is zero"));
  }

  if(fitFunction.empty()) {
    throw(std::runtime_error("Function is empty"));
  }

  if(min == max) {
    throw(std::runtime_error("Fitting range is empty"));
  }
  if(max < min) {
    throw(std::runtime_error("Fitting range is negative (min > max)"));
  }
}


void FitConfig::SetFitLimits(double min, double max) {
  if(min == max) {
    throw(std::runtime_error("Fitting range is empty"));
  }

  if(max < min) {
    throw(std::runtime_error("Fitting range is negative (min > max)"));
  }

  fitMinimum = min;
  fitMaximum = max;
}

double FitConfig::GetFitMin() const {
  return (fitMinimum);
}

double FitConfig::GetFitMax() const {
  return (fitMaximum);
}

void FitConfig::SetFitFunction(const std::string& function) {
  if(function.empty()) {
    throw(std::runtime_error("Function must not be empty"));
  }
  fitFunction = function;
}

std::string FitConfig::GetFitFunction() const {
  return (fitFunction);
}

void FitConfig::SetBackgroundFitFunction(const std::string& function) {
  if(function.empty()) {
    throw(std::runtime_error("Background fit function is empty"));
  }
  bkgFunction = function;
}

std::string FitConfig::GetBackgroundFitFunction() const {
  return (bkgFunction);
}

void FitConfig::SetSignalFitFunction(const std::string& function) {
  if(function.empty()) {
    throw(std::runtime_error("Signal fit function is empty"));
  }
  sigFunction = function;
}

std::string FitConfig::GetSignalFitFunction() const {
  return (sigFunction);
}

void FitConfig::SetFitOptions(const std::string& options) {
  fitOptions = options;
}
std::string FitConfig::GetFitOptions() const {
  return (fitOptions);
}

bool FitConfig::GetMode() const {
  return (isLowBackground);
}

const Parameter& FitConfig::ParSettings(std::size_t i) const {
  return (parameters.at(i));
}

void FitConfig::SetParamsSettings(const Parameters& pars) {
  parameters = pars;
}

const Parameters& FitConfig::ParamsSettings() const {
  return (parameters);
}

std::size_t FitConfig::NPar() const {
  return (parameters.size());
}

void FitConfig::SetFromFitResult(const TFitResultPtr& rhs) {
  auto npar = rhs->NPar();
  auto pars = rhs->GetParams();

  for(auto parIdx = 0; parIdx != npar; parIdx++) {
    auto name = rhs->GetParameterName(parIdx);
    auto value = pars[parIdx];
    parameters.push_back({name, value});
  }
}

void FitConfig::Print() {
  for(const auto& par : parameters) {
    PrintParameter(par);
  }
}

void FitConfig::PrintParameter(const Parameter& par) {  
  auto name = par.Name();
  auto val = par.Value();
  auto lowLimit = par.LowerLimit();
  auto topLimit = par.UpperLimit();
  // LOG_INFO() << "| " << name << " | " << val << " | " << lowLimit << " | " << topLimit;
}

#ifdef __CINT__
ClassImp(FitConfig)
#endif
