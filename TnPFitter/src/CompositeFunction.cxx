#include "TnPFitter/CompositeFunction.h"

#include <TF1.h>
#include "RootAdapters/SmartFunction.h"

CompositeFunction::CompositeFunction(std::string name, std::string theFormula,
                                     FittableFunction signalFunction,
                                     FittableFunction backgroundFunction)
    : formula{theFormula}, signal{signalFunction},
      background{backgroundFunction} {
  if (!functionsHaveSameRange()) {
    throw(std::runtime_error(
        "The range of the signal and background functions are different"));
  }

  if (formula.empty()) {
    throw(std::runtime_error("The combined function is empty"));
  }

  function = Smart::Formula(name, formula, signal.getFunction()->GetXmin(),
                            signal.getFunction()->GetXmax());

  setSignalParametersInComposite(signal.getParameters());
  setBackgroundParametersInComposite(background.getParameters());
}

bool CompositeFunction::functionsHaveSameRange() {
  TF1 *signalFunction = signal.getFunction();
  TF1 *backgroundFunction = background.getFunction();

  if (signalFunction->GetXmin() != backgroundFunction->GetXmin())
    return (false);
  return (signalFunction->GetXmax() == backgroundFunction->GetXmax());
}

Parameters CompositeFunction::getSignalParameters() const {
  return (signal.getParameters());
}

void CompositeFunction::setSignalParameters(const Parameters& pars) {
  signal.setupParametersFromConfig(pars);
  setSignalParametersInComposite(pars);
}

void CompositeFunction::setSignalParametersInComposite(const Parameters& pars) {
  for (auto index = 0ul; index < signal.getParameters().size(); index++) {
    auto par = pars.at(index);
    function->SetParameter((int) index, par.Value());
    function->SetParLimits((int) index, par.LowerLimit(), par.UpperLimit());
  }
}

void CompositeFunction::fixSignalParameters(const Parameters& pars) {
  signal.fixParametersFromConfig(pars);
  for (auto index = 0ul; index < signal.getParameters().size(); index++) {
    function->FixParameter((int) index, pars.at(index).Value());
  }
}

Parameters CompositeFunction::getBackgroundParameters() const {
  return (background.getParameters());
}

void CompositeFunction::setBackgroundParameters(const Parameters& pars) {
  background.setupParametersFromConfig(pars);
  setBackgroundParametersInComposite(pars);
}

void CompositeFunction::setBackgroundParametersInComposite(
    const Parameters& pars) {
  std::size_t signalIndexOffset = signal.getParameters().size();
  for (auto index = 0ul; index < background.getParameters().size(); index++) {
    auto par = pars.at(index);
    auto offsetIndex = index + signalIndexOffset;

    function->SetParameter((int) offsetIndex, par.Value());
    function->SetParLimits((int) offsetIndex, par.LowerLimit(),
                           par.UpperLimit());
  }
}

void CompositeFunction::fixBackgroundParameters(const Parameters& pars) {
  background.fixParametersFromConfig(pars);

  auto signalIndexOffset = signal.getParameters().size();
  for (auto index = 0ul; index < background.getParameters().size(); index++) {
    auto offsetIndex = index + signalIndexOffset;
    function->FixParameter((int) offsetIndex , pars.at(index).Value());
  }
}

TF1 *CompositeFunction::getFunction() const {
  return (function);
}
