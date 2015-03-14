#include "TnPFitter/IFitter.h"
#include "TnPFitter/FitterDraw.h"

IFitter::IFitter(std::string name,
                 std::string functionName,
                 TH1F* val_histogram,
                 const FitConfig& val_fitConfig)
    : name(std::move(name)),
      fitConfig(val_fitConfig),
      functionName(std::move(functionName)),
      histogram(val_histogram),
      compositeFunction(nullptr),
      signalFunction(nullptr),
      backgroundFunction(nullptr),
      compositeUpFunction(nullptr),
      compositeDownFunction(nullptr),
      backgroundUpFunction(nullptr),
      backgroundDownFunction(nullptr),
      bottomFitLimit(fitConfig.GetFitMin()),
      topFitLimit(fitConfig.GetFitMax()) {
  if (val_histogram == nullptr) {
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
  compositeFunction = new TF1(functionName.c_str(),
                              fitConfig.GetFitFunction().c_str(),
                              bottomFitLimit,
                              topFitLimit);
  setupMainCompositeFunction();

  histogram->Fit(compositeFunction, fitConfig.GetFitOptions().c_str());

  fitResult.fillFromFunction(compositeFunction);
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
  testCompositeFunction();
  return (backgroundDownFunction);
}

TF1* IFitter::GetBackgroundUpFunction() {
  testCompositeFunction();
  return (backgroundUpFunction);
}

TF1* IFitter::GetCompositeDownFunction() {
  testCompositeFunction();
  return (compositeDownFunction);
}

TF1* IFitter::GetCompositeUpFunction() {
  testCompositeFunction();
  return (compositeUpFunction);
}

TF1* IFitter::GetCompositeFunction() {
  testCompositeFunction();
  return (compositeFunction);
}

TF1* IFitter::GetSignalFunction() {
  testSignalFunction();
  return (signalFunction);
}

TF1* IFitter::GetBackgroundFunction() {
  testBackgroundFunction();
  return (backgroundFunction);
}

double IFitter::GetSigmaLow(int nSigma) {
  testCompositeFunction();

  auto sigma_mu_pair = GetSigmaAndMu();
  auto lowEdge = sigma_mu_pair.first - nSigma * sigma_mu_pair.second;

  return (lowEdge);
}

double IFitter::GetSigmaHigh(int nSigma) {
  testCompositeFunction();
  auto sigma_mu_pair = GetSigmaAndMu();

  auto highEdge = sigma_mu_pair.first + nSigma * sigma_mu_pair.second;

  return (highEdge);
}

void IFitter::SetFitLimits(const double min, const double max) {
  bottomFitLimit = min;
  topFitLimit = max;
  return;
}

void IFitter::testCompositeFunction() {
  if (compositeFunction == nullptr) {
    FitCompositeFunction();
  }
}

void IFitter::testSignalFunction() {
  if (signalFunction == nullptr) {
    SetSignalFunction();
  }
}

void IFitter::testBackgroundFunction() {
  if (backgroundFunction == nullptr) {
    SetBackgroundFunction();
  }
}

void IFitter::PrintVariable(const std::string& name,
                            double var,
                            double err) const {
  (void)name;
  (void)var;
  (void)err;
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
