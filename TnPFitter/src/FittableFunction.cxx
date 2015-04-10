#include "TnPFitter/FittableFunction.h"

#include <TF1.h>
#include "RootAdapters/SmartFunction.h"

FittableFunction::FittableFunction(std::string name,
                                   std::string formula,
                                   double min,
                                   double max)
    : function(Smart::Formula(name, formula, min, max)) {
  if(min > max) {
    throw(std::runtime_error("Fitting range is invalid"));
  }
}

FittableFunction::FittableFunction(TF1* function) : function(function) {
}

TF1* FittableFunction::getFunction() const {
  return (function);
}

void FittableFunction::setFunction(TF1* func) {
  function = func;
}

Parameters FittableFunction::getParameters() const {
  auto result = Parameters{};
  for (auto index = 0; index < function->GetNpar(); index++) {
    auto name = function->GetParName(index);
    auto value = function->GetParameter(index);
    result.push_back({name, value});
  }
  return (result);
}

void FittableFunction::setupParametersFromConfig(const Parameters& pars) {
  if(pars.size() != (unsigned long)function->GetNpar()) {
    throw(std::runtime_error("Parameters list contains too few or too many parameters"));
  }

  for (auto index = 0ul; index < pars.size(); index++) {
    setParameterFromConfig(index, pars[index]);
  }
}

void FittableFunction::setParameterFromConfig(std::size_t index,
                                              const Parameter& parameter) {
  auto name = parameter.Name();
  auto value = parameter.Value();

  function->SetParName(index, name.c_str());
  function->SetParameter(index, value);

  if (parameter.HasLowerLimit()) {
    auto min = parameter.LowerLimit();
    auto max = parameter.UpperLimit();
    function->SetParLimits(index, min, max);
  }
}

void FittableFunction::fixParametersFromConfig(const Parameters& pars) {
  for (auto index = 0ul; index < pars.size(); index++) {
    fixParameterFromConfig(index, pars[index]);
  }
}

void FittableFunction::fixParameterFromConfig(std::size_t index,
                                              const Parameter& parameter) {
  auto name = parameter.Name();
  auto value = parameter.Value();

  function->SetParName(index, name.c_str());
  function->FixParameter(index, value);
}
