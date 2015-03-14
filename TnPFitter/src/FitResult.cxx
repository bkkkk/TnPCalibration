#include "TnPFitter/FitResult.h"
#include <cassert>
#include <TF1.h>

void FitResult::fillFromFunction(TF1* function) {
  for (auto parIdx = 0; parIdx != function->GetNpar(); parIdx++) {
    auto parName = function->GetParName(parIdx);
    auto parValue = function->GetParameter(parIdx);
    auto parError = function->GetParError(parIdx);

    AddParameter(parName, parValue, parError);
  }
}

double FitResult::getParameterUpVariation(const std::string& name) {
  return (GetParValue(name) + GetParError(name));
}

double FitResult::getParameterDownVariation(const std::string& name) {
  return (GetParValue(name) - GetParError(name));
}

void FitResult::AddParameter(std::string name, double val, double error) {
  parameters[name] = std::make_pair (val, error);
  assert(!parameters.empty());
}

std::size_t FitResult::GetNPars() const {
  return(parameters.size());
}

const FitResult::SimpleParameters& FitResult::GetParameters() const {
  return (parameters);
}

FitResult::SimpleParameter FitResult::GetParameter(const std::string& name) const {
  auto parameter = parameters.find(name);
  if(parameter == parameters.end()) {
    throw(std::out_of_range("Parameter " + name + " not in collection"));
  }

  return (parameter->second);
}

double FitResult::GetParValue(const std::string& name) const {
  auto parameter = GetParameter(name);
  auto value = parameter.first;
  return (value);
}

double FitResult::GetParError(const std::string& name) const {
  auto parameter = GetParameter(name);
  auto error = parameter.second;
  return (error);
}