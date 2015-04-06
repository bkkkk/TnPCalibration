#include "TnPFitter/FitConfig.h"

#include "TFitResult.h"

#include "JacobUtils/LoggingUtility.h"

FitConfig::FitConfig(std::string sigFormula,
                     std::string bkgFormula,
                     unsigned signalPars,
                     unsigned bkgPars,
                     double min,
                     double max)
    : fitOptions("MERQB"),
      fitMinimum(min),
      fitMaximum(max),
      sigFunction{std::move(sigFormula)},
      bkgFunction{std::move(bkgFormula)},
      signalParameters(signalPars),
      bkgParameters(bkgPars) {
  if (signalPars == 0) {
    throw(std::runtime_error("Number of signal parameters is zero"));
  }

  if (bkgPars == 0) {
    throw(std::runtime_error("Number of background parameters is zero"));
  }

  if (sigFunction.empty()) {
    throw(std::runtime_error("Signal function is empty"));
  }

  if (bkgFunction.empty()) {
    throw(std::runtime_error("Background function is empty"));
  }

  if (min == max) {
    throw(std::runtime_error("Fitting range is empty"));
  }
  if (max < min) {
    throw(std::runtime_error("Fitting range is negative (min > max)"));
  }
}

void FitConfig::SetFitLimits(double min, double max) {
  if (min == max) {
    throw(std::runtime_error("Fitting range is empty"));
  }

  if (max < min) {
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

void FitConfig::SetBackgroundFitFunction(const std::string& function) {
  if (function.empty()) {
    throw(std::runtime_error("Background fit function is empty"));
  }
  bkgFunction = function;
}

std::string FitConfig::GetBackgroundFitFunction() const {
  return (bkgFunction);
}

void FitConfig::SetSignalFitFunction(const std::string& function) {
  if (function.empty()) {
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

Parameters FitConfig::getSignalParameters() const {
  return (signalParameters);
}

void FitConfig::setSignalParameters(const Parameters& parameters) {
  signalParameters = parameters;
}

Parameter FitConfig::getSignalParameter(std::size_t index) const {
  return (signalParameters[index]);
}

std::size_t FitConfig::getNumberOfSignalParameters() {
  return (signalParameters.size());
}

Parameters FitConfig::getBkgParameters() const {
  return (bkgParameters);
}

void FitConfig::setBkgParameters(const Parameters& parameters) {
  bkgParameters = parameters;
}

Parameter FitConfig::getBkgParameter(std::size_t index) const {
  return (bkgParameters[index]);
}

std::size_t FitConfig::getNumberOfBkgParameters() {
  return (bkgParameters.size());
}

void FitConfig::SetFromFitResult(const TFitResultPtr& rhs) {
  auto pars = rhs->GetParams();

  for (auto index = 0ul; index < signalParameters.size(); index++) {
    auto name = rhs->GetParameterName(index);
    auto value = pars[index];
    signalParameters.push_back({name, value});
  }

  for (auto index = 0ul; index < bkgParameters.size(); index++) {
    auto indexInComposite = index + signalParameters.size();
    auto name = rhs->GetParameterName(indexInComposite);
    auto value = pars[indexInComposite];
    bkgParameters.push_back({name, value});
  }
}

void FitConfig::Print() {
  for (const auto& par : signalParameters) {
    PrintParameter(par);
  }

  for (const auto& par : bkgParameters) {
    PrintParameter(par);
  }
}

void FitConfig::PrintParameter(const Parameter& par) {
  (void)par;
}

#ifdef __CINT__
ClassImp(FitConfig)
#endif
