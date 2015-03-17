#include "TnPFitter/IFitter.h"
#include "TnPFitter/FitterDraw.h"

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
      compositeFunction(Smart::Formula(functionName,
                                       fitConfig.GetFitFunction(),
                                       bottomFitLimit,
                                       topFitLimit)),
      signalFunction(Smart::Formula(functionName + "_signal_" + histogramName,
                                    fitConfig.GetSignalFitFunction(),
                                    bottomFitLimit,
                                    topFitLimit)),
      backgroundFunction(Smart::Formula(functionName + "_" + histogramName,
                                        fitConfig.GetBackgroundFitFunction(),
                                        bottomFitLimit,
                                        topFitLimit)),
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

  histogramName = histogram->GetName();
}

IFitter::~IFitter() {
  delete compositeFunction;
  delete backgroundFunction;
  delete signalFunction;
  delete backgroundUpFunction;
  delete backgroundDownFunction;
  delete compositeDownFunction;
  delete compositeUpFunction;
}

void IFitter::FitCompositeFunction() {
  setupMainCompositeFunction();

  histogram->Fit(compositeFunction, fitConfig.GetFitOptions().c_str());

  fitResult.fillFromFunction(compositeFunction);
}

void IFitter::SetCompositeUpFunction() {
  SetCompositeUpComponent();

  histogram->Fit(compositeUpFunction, fitConfig.GetFitOptions().c_str());

  SetBackgroundUpFunction();
}

void IFitter::SetCompositeDownFunction() {
  SetCompositeDownComponent();

  histogram->Fit(compositeDownFunction, fitConfig.GetFitOptions().c_str());

  SetBackgroundDownFunction();
}

void IFitter::setupMainCompositeFunction() {
  for (auto parIndex = 0; parIndex < compositeFunction->GetNpar(); parIndex++) {
    setupFunctionParameter(compositeFunction, parIndex);
  }
}

void IFitter::setupFunctionParameter(TF1* function, std::size_t index) {
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

TF1* IFitter::GetCompositeFunction() {
  return (compositeFunction);
}

TF1* IFitter::GetSignalFunction() {
  return (signalFunction);
}

TF1* IFitter::GetBackgroundFunction() {
  return (backgroundFunction);
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
