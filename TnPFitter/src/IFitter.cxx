#include "TnPFitter/IFitter.h"
#include "TnPFitter/FitterDraw.h"
#include "RootAdapters/SmartFunction.h"

IFitter::IFitter(std::string name,
                 std::string functionName,
                 TH1F* histogram,
                 const FitConfig& fitConfig)
    : name(std::move(name)),
      fitConfig(fitConfig),
      functionName(std::move(functionName)),
      histogram(histogram),
      bottomFitLimit(fitConfig.GetFitMin()),
      topFitLimit(fitConfig.GetFitMax()),
      composite{functionName,
                fitConfig.GetFitFunction(),
                bottomFitLimit,
                topFitLimit},
      signal{functionName + "_signal_" + histogramName,
             fitConfig.GetSignalFitFunction(),
             bottomFitLimit,
             topFitLimit},
      background{functionName + "_" + histogramName,
                 fitConfig.GetBackgroundFitFunction(),
                 bottomFitLimit,
                 topFitLimit},
      compositeUpFunction(
          Smart::Formula(functionName + "_Composite_Up_" + histogramName,
                         fitConfig.GetFitFunction(),
                         bottomFitLimit,
                         topFitLimit)),
      compositeDownFunction(
          Smart::Formula(functionName + "_Composite_Down_" + histogramName,
                         fitConfig.GetFitFunction(),
                         bottomFitLimit,
                         topFitLimit)),
      backgroundUpFunction(
          Smart::Formula(functionName + "_Bkg_Up_" + histogramName,
                         fitConfig.GetBackgroundFitFunction(),
                         bottomFitLimit,
                         topFitLimit)),
      backgroundDownFunction(
          Smart::Formula(functionName + "_Bkg_Down_" + histogramName,
                         fitConfig.GetBackgroundFitFunction(),
                         bottomFitLimit,
                         topFitLimit)) {
  if (histogram == nullptr) {
    throw(std::runtime_error("Histogram is not setup properly"));
  }

  composite.setupParametersFromConfig(fitConfig.ParamsSettings());

  histogramName = histogram->GetName();
}

IFitter::~IFitter() {
  delete backgroundFunction;
  delete backgroundUpFunction;
  delete backgroundDownFunction;
  delete compositeDownFunction;
  delete compositeUpFunction;
}

void IFitter::setCompositeSignalComponent(TF1* function) {
  for (auto index = 0ul; index < nSignalParameters; index++) {
    setParameterFromConfig(function, index);
  }
}

void IFitter::FitCompositeFunction() {
  histogram->Fit(GetCompositeFunction(), fitConfig.GetFitOptions().c_str());

  fitResult.fillFromFunction(GetCompositeFunction());
}

void IFitter::SetSignalFunction() {
  Parameters pars = getSignalParametersFromFunction(GetCompositeFunction());
  signal.fixParametersFromConfig(pars);
}

Parameters IFitter::getSignalParametersFromFunction(TF1* function) {
  Parameters result;
  for (auto index = 0u; index < nSignalParameters; index++) {
    auto name = function->GetParName(index);
    auto value = function->GetParameter(index);
    result.push_back({name, value});
  }
  return (result);
}

void IFitter::SetBackgroundFunction() {
  Parameters pars = getBackgroundParametersFromFunction(GetCompositeFunction());
  
  background.fixParametersFromConfig(pars);  
}

Parameters IFitter::getBackgroundParametersFromFunction(TF1* function) {
  Parameters result;

  for (auto index = 0u; index < nBackgroundParameters; index++) {
    auto inCompositeIndex = index + nSignalParameters;
    auto value = function->GetParameter(inCompositeIndex);
    auto name = function->GetParName(inCompositeIndex);
    result.push_back({name, value});
  }

  return (result);
}

void IFitter::SetCompositeUpFunction() {
  SetCompositeUpComponent();

  histogram->Fit(GetCompositeUpFunction(), fitConfig.GetFitOptions().c_str());

  SetBackgroundUpFunction();
}

void IFitter::SetBackgroundUpFunction() {
  for (auto index = 0ul; index < nBackgroundParameters; index++) {
    auto inCompositeIndex = index + nSignalParameters;
    auto value = GetCompositeUpFunction()->GetParameter(inCompositeIndex);
    GetBackgroundUpFunction()->SetParameter(index, value);
  }
}

void IFitter::SetCompositeDownFunction() {
  SetCompositeDownComponent();

  histogram->Fit(GetCompositeDownFunction(), fitConfig.GetFitOptions().c_str());

  SetBackgroundDownFunction();
}

void IFitter::SetBackgroundDownFunction() {
  for (auto index = 0ul; index < nBackgroundParameters; index++) {
    auto inCompositeIndex = index + nSignalParameters;
    auto value = GetCompositeDownFunction()->GetParameter(inCompositeIndex);
    GetBackgroundDownFunction()->SetParameter(index, value);
  }
}

void IFitter::setParameterFromConfig(TF1* function, std::size_t index) {
  auto parameter = fitConfig.ParSettings(index);
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

void IFitter::SetCompositeUpComponent() {
  setCompositeSignalComponent(GetCompositeUpFunction());

  Parameters parameters = getVariationUp();

  setCompositeBackgroundComponent(GetCompositeUpFunction(), parameters);
}

void IFitter::SetCompositeDownComponent() {
  setCompositeSignalComponent(GetCompositeDownFunction());

  Parameters parameters = getVariationDown();

  setCompositeBackgroundComponent(GetCompositeDownFunction(), parameters);
}

void IFitter::setCompositeBackgroundComponent(TF1* function, Parameters pars) {
  for (auto index = 0ul; index < nBackgroundParameters; index++) {
    auto value = pars[index].Value();
    auto indexInComposite = nSignalParameters + index;
    function->FixParameter(indexInComposite, value);
  }
}

TF1* IFitter::GetCompositeFunction() {
  return (composite.getFunction());
}

TF1* IFitter::GetSignalFunction() {
  return (signal.getFunction());
}

TF1* IFitter::GetBackgroundFunction() {
  return (background.getFunction());
}

TF1* IFitter::GetBackgroundDownFunction() {
  return (backgroundDownFunction);
}

TF1* IFitter::GetBackgroundUpFunction() {
  return (backgroundUpFunction);
}

TF1* IFitter::GetCompositeDownFunction() {
  return (compositeDownFunction);
}

TF1* IFitter::GetCompositeUpFunction() {
  return (compositeUpFunction);
}

double IFitter::GetSigmaLow(int nSigma) {
  auto sigma_mu_pair = GetSigmaAndMu();
  auto lowEdge = sigma_mu_pair.first - nSigma * sigma_mu_pair.second;

  return (lowEdge);
}

double IFitter::GetSigmaHigh(int nSigma) {
  auto sigma_mu_pair = GetSigmaAndMu();

  auto highEdge = sigma_mu_pair.first + nSigma * sigma_mu_pair.second;

  return (highEdge);
}

void IFitter::SetFitLimits(const double min, const double max) {
  bottomFitLimit = min;
  topFitLimit = max;
  return;
}

void TNPFITTER::RunFit(IFitter* fitter) {
  if (fitter == nullptr) {
    throw(std::runtime_error("Fitter function not setup correctly"));
  }

  fitter->FitCompositeFunction();
  fitter->SetSignalFunction();
  fitter->SetBackgroundFunction();
  fitter->SetCompositeDownFunction();
  fitter->SetCompositeUpFunction();
}

#ifdef __CINT__
ClassImp(IFitter)
#endif
