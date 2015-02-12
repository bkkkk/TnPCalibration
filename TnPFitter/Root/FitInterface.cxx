#include "TnPFitter/FitInterface.h"
#include "TnPFitter/FitterDraw.h"

FitInterface::
FitInterface(std::string val_name, TH1F* val_histogram, const FitConfig& val_fitConfig)
  : name(std::move(val_name)),
    fitConfig(val_fitConfig),
    functionName("NotDefined"),
    histogram(val_histogram),
    histogramName(histogram->GetName()),
    compositeFunction(nullptr),
    signalFunction(nullptr),
    backgroundFunction(nullptr),
    compositeUpFunction(nullptr),
    compositeDownFunction(nullptr),
    backgroundUpFunction(nullptr),
    backgroundDownFunction(nullptr),
    bottomFitLimit(fitConfig.GetFitMin()),
    topFitLimit(fitConfig.GetFitMax()) {
  fitResult = new FitResult (name, fitConfig.NPar());
}

FitInterface::~FitInterface() {
  delete fitResult;
  delete compositeFunction;
  delete backgroundFunction;
  delete signalFunction;
  delete backgroundUpFunction;
  delete backgroundDownFunction;
  delete compositeDownFunction;
  delete compositeUpFunction;
}

void FitInterface::FitCompositeFunction() {
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

    fitResult->AddParameter(parName, parValue, parError);
  }
}

TF1* FitInterface::GetBackgroundDownFunction() {
  testCompositeFunction();
  return(backgroundDownFunction);
}

TF1* FitInterface::GetBackgroundUpFunction() {
  testCompositeFunction();
  return (backgroundUpFunction);
}

TF1* FitInterface::GetCompositeDownFunction() {
  testCompositeFunction();
  return (compositeDownFunction);
}

TF1* FitInterface::GetCompositeUpFunction() {
  testCompositeFunction();
  return (compositeUpFunction);
}

TF1* FitInterface::GetCompositeFunction() {
  testCompositeFunction();
  return (compositeFunction);
}

TF1* FitInterface::GetSignalFunction() {
  testSignalFunction();
  return (signalFunction);
}

TF1* FitInterface::GetBackgroundFunction() {
  testBackgroundFunction();
  return (backgroundFunction);
}

double FitInterface::GetSigmaLow(int nSigma) {
  testCompositeFunction();

  auto sigma_mu_pair = GetSigmaAndMu();
  auto lowEdge = sigma_mu_pair.first - nSigma * sigma_mu_pair.second;

  return(lowEdge);
}

double FitInterface::GetSigmaHigh(int nSigma) {
  testCompositeFunction();
  auto sigma_mu_pair = GetSigmaAndMu();

  auto highEdge = sigma_mu_pair.first + nSigma * sigma_mu_pair.second;

  return(highEdge);
}

void FitInterface::SetFitLimits(const double min, const double max) {
  bottomFitLimit = min;
  topFitLimit = max;
  return;
}

void FitInterface::testCompositeFunction() {
  if(compositeFunction == nullptr) {
    FitCompositeFunction();
  }
}

void FitInterface::testSignalFunction() {
  if(signalFunction == nullptr) {
    SetSignalFunction();
  }
}

void FitInterface::testBackgroundFunction() {
  if(backgroundFunction == nullptr) {
    SetBackgroundFunction();
  }
}

const void FitInterface::PrintVariable(const std::string& name, double var, double err) const {
}

void TNPFITTER::RunFit(FitInterface* fitter) {
  if(fitter == nullptr) {
    throw(std::runtime_error("Fitter function not setup correctly"));
  }

  fitter->FitCompositeFunction();
  fitter->SetSignalFunction();
  fitter->SetBackgroundFunction();
  fitter->SetCompositeDownFunction();
  fitter->SetCompositeUpFunction();
}

void TNPFITTER::DrawFit(FitInterface* fitter, int sigma, int window) {
  if(fitter == nullptr) {
    throw(std::runtime_error("Fitter function not setup correctly"));
  }

  FitterDraw* fitterDraw = new FitterDraw(fitter, sigma, window);
  fitterDraw->Draw();
}

bool TNPFITTER::IsLowBackground(TH1* histogram, double fittingEdge, double threshold) {
  if(histogram == nullptr) {
    throw std::string ("Can't check background mode, histogram is not valid");
  }

  // Check form of threshold variable
  if(threshold > 1) threshold *= (1/100);

  // Get comparison bin
  double testValue = histogram->GetBinContent(histogram->FindBin(fittingEdge));

  // Pick mode
  if(histogram->GetMaximum() * threshold > testValue) {
    return true;
  } else {
    return false;
  }
}

#ifdef __CINT__
ClassImp(FitInterface)
#endif
