#include "TnPFitter/FitResult.h"

FitResult::FitResult(const std::string& name, const size_t NPars)
 : name(name) {
}

FitResult::~FitResult() {
  name.clear();
  parameters.clear();
}


int FitResult::AddParameter(std::string name, double val, double error) {
  parameters[name] = std::make_pair (val, error);
    
  assert(!parameters.empty());
    
  return (1);
}

const std::size_t FitResult::GetNPars() const {
  return(parameters.size());
}

const FitResult::SimpleParameters& FitResult::GetParameters() const {
  return (parameters);
}

FitResult::SimpleParameter FitResult::GetParameter(const std::string& parName) {
  auto parameter = parameters.find(parName);
  if(parameter == parameters.end()) {
    throw(std::out_of_range(""));
  }

  return (parameter->second);
}

double FitResult::GetParValue(const std::string& name) const {
  auto parameter = parameters.find(name);
  if(parameter == parameters.end()) {
    throw(std::out_of_range(""));
  }

  auto value = parameter->second.first;
  return (value);
}

double FitResult::GetParError(const std::string& name) const {
  auto parameter = parameters.find(name);
  if(parameter == parameters.end()) {
    throw(std::out_of_range(""));
  }

  auto error = parameter->second.second;
  return (error);
}