#include "TnPFitter/CompositeFunction.h"

#include <TF1.h>
#include "RootAdapters/SmartFunction.h"

CompositeFunction::CompositeFunction(std::string name,
                                     FittableFunction signal,
                                     FittableFunction background)
    : signal{signal}, background{background} {
  auto formula = std::string{signal.getFunction()->GetName()};
  formula.append("+");
  formula.append(background.getFunction()->GetName());

  function = Smart::Formula(name,
                            formula,
                            signal.getFunction()->GetMinimum(),
                            signal.getFunction()->GetMaximum());
}

Parameters CompositeFunction::getSignalParameters() const {
  return (signal.getParameters());
}

void CompositeFunction::setSignalParameters(const Parameters& pars) {
  signal.setupParametersFromConfig(pars);
}

void CompositeFunction::fixSignalParameters(const Parameters& pars) {
  signal.fixParametersFromConfig(pars);
}

Parameters CompositeFunction::getBackgroundParameters() const {
  return (background.getParameters());
}

void CompositeFunction::setBackgroundParameters(const Parameters& pars) {
  background.setupParametersFromConfig(pars);
}
void CompositeFunction::fixBackgroundParameters(const Parameters& pars) {
  background.fixParametersFromConfig(pars);
}

TF1* CompositeFunction::getFunction() const {
  return (function);
}