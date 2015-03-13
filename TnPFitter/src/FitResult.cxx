#include "TnPFitter/FitResult.h"
#include <cassert>

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