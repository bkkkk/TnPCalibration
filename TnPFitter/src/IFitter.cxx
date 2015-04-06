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
      histogramName{},
      bottomFitLimit(fitConfig.GetFitMin()),
      topFitLimit(fitConfig.GetFitMax()),
      fittingGroup{functionName, histogramName, fitConfig},
      signal{functionName + "_Sig_" + histogramName,
             fitConfig.GetSignalFitFunction(),
             bottomFitLimit,
             topFitLimit},
      background{functionName + "_Bkg_" + histogramName,
                 fitConfig.GetBackgroundFitFunction(),
                 bottomFitLimit,
                 topFitLimit},
      composite{functionName, signal, background},
      compositeUp{functionName + "_Composite_Up_" + histogramName,
                  signal,
                  background},
      backgroundUp{functionName + "_Bkg_Up_" + histogramName,
                   fitConfig.GetBackgroundFitFunction(),
                   bottomFitLimit,
                   topFitLimit},
      compositeDown{functionName + "_Composite_Down_" + histogramName,
                    signal,
                    background},
      backgroundDown{functionName + "_Bkg_Down_" + histogramName,
                     fitConfig.GetBackgroundFitFunction(),
                     bottomFitLimit,
                     topFitLimit} {
  if (histogram == nullptr) {
    throw(std::runtime_error("Histogram is not setup properly"));
  }
  histogramName = histogram->GetName();
  composite.setSignalParameters(fitConfig.getSignalParameters());
  composite.setBackgroundParameters(fitConfig.getBkgParameters());
}

void IFitter::FitCompositeFunction() {
  histogram->Fit(GetCompositeFunction(), fitConfig.GetFitOptions().c_str());

  fitResult.fillFromFunction(GetCompositeFunction());
}

void IFitter::SetSignalFunction() {
  fittingGroup.fillSignalFunction(composite);
}

void IFitter::SetBackgroundFunction() {
  background.fixParametersFromConfig(composite.getBackgroundParameters());
}

void IFitter::SetCompositeUpFunction() {
  SetCompositeUpComponent();

  histogram->Fit(GetCompositeUpFunction(), fitConfig.GetFitOptions().c_str());

  SetBackgroundUpFunction();
}

void IFitter::SetBackgroundUpFunction() {
  backgroundUp.setupParametersFromConfig(compositeUp.getBackgroundParameters());
}

void IFitter::SetCompositeDownFunction() {
  SetCompositeDownComponent();

  histogram->Fit(GetCompositeDownFunction(), fitConfig.GetFitOptions().c_str());

  SetBackgroundDownFunction();
}

void IFitter::SetBackgroundDownFunction() {
  backgroundDown.setupParametersFromConfig(
      compositeDown.getBackgroundParameters());
}

void IFitter::SetCompositeUpComponent() {
  compositeUp.setSignalParameters(fitConfig.getSignalParameters());
  compositeUp.setBackgroundParameters(getVariationUp());
}

void IFitter::SetCompositeDownComponent() {
  compositeDown.setSignalParameters(fitConfig.getSignalParameters());
  compositeDown.setBackgroundParameters(getVariationDown());
}

TF1* IFitter::GetCompositeFunction() {
  return (composite.getFunction());
}

TF1* IFitter::GetSignalFunction() {
  return (fittingGroup.getSignal().getFunction());
}

TF1* IFitter::GetBackgroundFunction() {
  return (fittingGroup.getBackground().getFunction());
}

TF1* IFitter::GetBackgroundDownFunction() {
  return (backgroundDown.getFunction());
}

TF1* IFitter::GetBackgroundUpFunction() {
  return (backgroundUp.getFunction());
}

TF1* IFitter::GetCompositeDownFunction() {
  return (compositeDown.getFunction());
}

TF1* IFitter::GetCompositeUpFunction() {
  return (compositeUp.getFunction());
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
