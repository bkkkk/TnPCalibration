#include "TnPFitter/IFitter.h"
#include "TnPFitter/FitterDraw.h"

IFitter::IFitter(std::string name, TH1F* val_histogram, const FitConfig& val_fitConfig)
  : name(std::move(name)),
    fitConfig(val_fitConfig),
    functionName("NotDefined"),
    histogram(val_histogram),
    compositeFunction(nullptr),
    signalFunction(nullptr),
    backgroundFunction(nullptr),
    compositeUpFunction(nullptr),
    compositeDownFunction(nullptr),
    backgroundUpFunction(nullptr),
    backgroundDownFunction(nullptr),
    bottomFitLimit(fitConfig.GetFitMin()),
    topFitLimit(fitConfig.GetFitMax()),
    fitResult{} {

  if(val_histogram == nullptr) {
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
  compositeFunction = new TF1(functionName.c_str(), fitConfig.GetFitFunction().c_str(), bottomFitLimit, topFitLimit);

  for(auto parIdx = 0; parIdx != compositeFunction->GetNpar(); parIdx++) {
    auto val = fitConfig.ParSettings(parIdx).Value();
    auto min = fitConfig.ParSettings(parIdx).LowerLimit();
    auto max = fitConfig.ParSettings(parIdx).UpperLimit();
    auto namePar = fitConfig.ParSettings(parIdx).Name();

    compositeFunction->SetParName(parIdx, namePar.c_str());
    compositeFunction->SetParameter(parIdx, val);

    if(fitConfig.ParSettings(parIdx).HasLowerLimit()) {
      compositeFunction->SetParLimits(parIdx, min, max);
    }
  }

  histogram->Fit(compositeFunction, fitConfig.GetFitOptions().c_str());

  for(auto parIdx = 0; parIdx != compositeFunction->GetNpar(); parIdx++) {
    auto parName = compositeFunction->GetParName(parIdx);
    auto parValue = compositeFunction->GetParameter(parIdx);
    auto parError = compositeFunction->GetParError(parIdx);

    PrintVariable(parName, parValue, parError);

    fitResult.AddParameter(parName, parValue, parError);
  }
}

TF1* IFitter::GetBackgroundDownFunction() {
  testCompositeFunction();
  return(backgroundDownFunction);
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

  return(lowEdge);
}

double IFitter::GetSigmaHigh(int nSigma) {
  testCompositeFunction();
  auto sigma_mu_pair = GetSigmaAndMu();

  auto highEdge = sigma_mu_pair.first + nSigma * sigma_mu_pair.second;

  return(highEdge);
}

void IFitter::SetFitLimits(const double min, const double max) {
  bottomFitLimit = min;
  topFitLimit = max;
  return;
}

void IFitter::testCompositeFunction() {
  if(compositeFunction == nullptr) {
    FitCompositeFunction();
  }
}

void IFitter::testSignalFunction() {
  if(signalFunction == nullptr) {
    SetSignalFunction();
  }
}

void IFitter::testBackgroundFunction() {
  if(backgroundFunction == nullptr) {
    SetBackgroundFunction();
  }
}

const void IFitter::PrintVariable(const std::string& name, double var, double err) const {
}

void TNPFITTER::RunFit(IFitter* fitter) {
  if(fitter == nullptr) {
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